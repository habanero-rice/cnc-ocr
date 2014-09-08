#include "cncocr_internal.h"

// TODO:
// Instead of having a isSingleAssignment argument for each of the
// item put functions, we should have some sort of tuning parameter
// that lets us choose to use STICKY or IDEM events in the collection?
// Then satisfying the event would give the desired behavior.
// (We'd also have to check if it's an event or a data block guid.)

{% block arch_itemcoll_defs %}

// XXX - increase this (I just wanted to set it small so I can see if it's working)
#define CNC_ITEMS_PER_BLOCK 8
#define CNC_ITEM_BLOCK_FULL(block) ((block)->count == CNC_ITEMS_PER_BLOCK)
#define CNC_GETTER_GUID ((ocrGuid_t)-1)
#define CNC_GETTER_ROLE 'G'
#define CNC_PUTTER_ROLE 'P'

typedef struct {
    ocrGuid_t entry;
    ocrGuid_t collection;
    ocrGuid_t firstBlock;
    ocrGuid_t oldFirstBlock;
    u32 bucketIndex;
    u32 firstBlockCount;
    u32 tagLength;
    u32 slot;
    ocrDbAccessMode_t mode;
    u8 checkedFirst;
    u8 role;
    u8 tag[];
} ItemCollOpParams;

// XXX - emulating exclusive write mode using this lock
static void _lock(volatile u32 *lock) {
    while (__sync_lock_test_and_set(lock, 1)) {
        while (*lock);
    }
}

static void _unlock(volatile u32 *lock) {
    __sync_synchronize();
    *lock = 0;
}

static void _lockArray(ocrGuid_t *blockArray) {
    _lock((volatile u32*)&blockArray[CNC_TABLE_SIZE]);
}

static void _unlockArray(ocrGuid_t *blockArray) {
    _unlock((volatile u32*)&blockArray[CNC_TABLE_SIZE]);
}

typedef struct {
    bool isEvent;
    ocrGuid_t guid;
} ItemBlockEntry;

typedef struct {
    volatile u32 lock;
    u32 count;
    ocrGuid_t next;
    ItemBlockEntry entries[CNC_ITEMS_PER_BLOCK];
    u8 tags[];
} ItemBlock;

static ocrGuid_t _itemBlockCreate(u32 tagLength, ocrGuid_t next, ItemBlock **out) {
    ocrGuid_t blockGuid;
    ItemBlock *block;
    u64 size = sizeof(ItemBlock) + (tagLength * CNC_ITEMS_PER_BLOCK);
    CNC_CREATE_ITEM(&blockGuid, (void**)&block, size);
    // XXX - should we start from the back?
    block->lock = 0;
    block->count = 0;
    block->next = next;
    *out = block;
    return blockGuid;
}

static ocrGuid_t _itemBlockInsert(ItemBlock *block, u8 *tag, ocrGuid_t entry, u32 tagLength) {
    ASSERT(!CNC_ITEM_BLOCK_FULL(block));
    u32 i = block->count;
    block->count += 1;
    if (entry == CNC_GETTER_GUID) {
        block->entries[i].isEvent = true;
        ocrEventCreate(&block->entries[i].guid, OCR_EVENT_IDEM_T, true);
    }
    else {
        block->entries[i].isEvent = false;
        block->entries[i].guid = entry;
    }
    MEMCPY(&block->tags[i*tagLength], tag, tagLength);
    return block->entries[i].guid;
}

{% endblock arch_itemcoll_defs %}
/* Compare byte-by-byte for tag equality */
static bool _equals(u8 *tag1, u8 *tag2, u32 length) {
    return MEMCMP(tag1, tag2, length) == 0;
}

/* Hash function implementation. Fast and pretty good */
static u64 _hash_function(u8 *str, u32 length) {
    u64 hash = 5381;
    u32 c;
    while (length-- > 0) {
        c = *str++;
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}
{% block arch_itemcoll_impl %}
static u32 _itemBlockFind(ItemBlock *block, u8 *tag, u32 tagLength, u32 startAt) {
    u32 i = startAt;
    for (; i<block->count; i++) {
        if (_equals(&block->tags[i*tagLength], tag, tagLength)) {
            return i;
        }
    }
    return CNC_ITEMS_PER_BLOCK; // not found
}

static ocrGuid_t _searchBucketEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]);

static ocrGuid_t _addToBucketEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    // unpack
    ocrGuid_t *blockArray = depv[0].ptr;
    ItemCollOpParams *params = depv[1].ptr;
    ocrGuid_t paramsGuid = depv[1].guid;
    // XXX - we don't REALLY get exclusive write, so we have to do a lock
    _lockArray(blockArray);
    // look up the first block the bucket
    ocrGuid_t firstBlock = blockArray[params->bucketIndex];
    // is our first block still first?
    if (firstBlock == params->firstBlock) {
        ItemBlock *newFirst;
        blockArray[params->bucketIndex] = _itemBlockCreate(params->tagLength, firstBlock, &newFirst);
        // XXX - repeated code, also in addToBlock
        bool isGetter = (params->role == CNC_GETTER_ROLE);
        ocrGuid_t src = isGetter ? CNC_GETTER_GUID : params->entry;
        ocrGuid_t res = _itemBlockInsert(newFirst, params->tag, src, params->tagLength);
        if (isGetter) {
            ocrAddDependence(res, params->entry, params->slot, params->mode);
        }
    }
    else { // someone added a new block...
        // try searching again
        params->oldFirstBlock = params->firstBlock;
        params->firstBlock = firstBlock;
        params->checkedFirst = 0;
        ocrGuid_t deps[] = { firstBlock, paramsGuid };
        ocrGuid_t searchEdtGuid, templGuid;
        ocrEdtTemplateCreate(&templGuid, _searchBucketEdt, 0, 2);
        ocrEdtCreate(&searchEdtGuid, templGuid,
            /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
            /*depc=*/EDT_PARAM_DEF, /*depv=*/deps,
            /*properties=*/EDT_PROP_NONE,
            /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
        ocrEdtTemplateDestroy(templGuid);
    }
    // XXX - we don't REALLY get exclusive write, so we have to do an unlock
    _unlockArray(blockArray);
    return NULL_GUID;
}

static ocrGuid_t _addToBlockEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    // unpack
    ItemBlock *block = depv[0].ptr;
    ItemCollOpParams *params = depv[1].ptr;
    ocrGuid_t paramsGuid = depv[1].guid;
    // XXX - we don't REALLY get exclusive write, so we have to do a lock
    _lock(&block->lock);
    // is it in this block?
    // XXX - repeated code (also in the searchEdt)
    u32 i = _itemBlockFind(block, params->tag, params->tagLength, 0);
    if (i < CNC_ITEMS_PER_BLOCK) { // found!
        ocrGuid_t foundEntry = block->entries[i].guid;
        if (params->role == CNC_GETTER_ROLE) { // Get
            ocrAddDependence(foundEntry, params->entry, params->slot, params->mode);
        }
        else if (block->entries[i].isEvent) { // Put
            ocrAddDependence(params->entry, foundEntry, 0, DB_DEFAULT_MODE);
        }
        // XXX - currently ignoring single assignment checks
    }
    // add the entry if there's still room
    else if (!CNC_ITEM_BLOCK_FULL(block)) {
        bool isGetter = (params->role == CNC_GETTER_ROLE);
        ocrGuid_t src = isGetter ? CNC_GETTER_GUID : params->entry;
        ocrGuid_t res = _itemBlockInsert(block, params->tag, src, params->tagLength);
        if (isGetter) {
            ocrAddDependence(res, params->entry, params->slot, params->mode);
        }
    }
    else { // the block filled up while we were searching
        // might need to add a new block to the bucket
        ocrGuid_t addEdtGuid, templGuid;
        ocrEdtTemplateCreate(&templGuid, _addToBucketEdt, 0, 2);
        ocrEdtCreate(&addEdtGuid, templGuid,
            /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
            /*depc=*/EDT_PARAM_DEF, /*depv=*/NULL,
            /*properties=*/EDT_PROP_NONE,
            /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
        ocrAddDependence(params->collection, addEdtGuid, 0, DB_MODE_EW);
        ocrAddDependence(paramsGuid, addEdtGuid, 1, DB_DEFAULT_MODE);
        ocrEdtTemplateDestroy(templGuid);
    }
    // XXX - we don't REALLY get exclusive write, so we have to do an unlock
    _unlock(&block->lock);
    return NULL_GUID;
}

static ocrGuid_t _searchBucketEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    // unpack
    ItemBlock *block = depv[0].ptr;
    ocrGuid_t blockGuid = depv[0].guid;
    ItemCollOpParams *params = depv[1].ptr;
    ocrGuid_t paramsGuid = depv[1].guid;
    // record first block size (if applicable)
    if (!params->checkedFirst) {
        params->checkedFirst = 1;
        params->firstBlockCount = block->count;
    }
    // is it in this block?
    u32 i = _itemBlockFind(block, params->tag, params->tagLength, 0);
    if (i < CNC_ITEMS_PER_BLOCK) { // found!
        ocrGuid_t foundEntry = block->entries[i].guid;
        if (params->role == CNC_GETTER_ROLE) { // Get
            ocrAddDependence(foundEntry, params->entry, params->slot, params->mode);
        }
        else if (block->entries[i].isEvent) { // Put
            ocrAddDependence(params->entry, foundEntry, 0, DB_DEFAULT_MODE);
        }
        // XXX - currently ignoring single assignment checks
    }
    // did we reach the end of the search?
    else if (block->next == NULL_GUID || blockGuid == params->oldFirstBlock) {
        // try to go back and add it to the first block
        // XXX - should check if it was full
        ocrGuid_t addEdtGuid, templGuid;
        ocrEdtTemplateCreate(&templGuid, _addToBlockEdt, 0, 2);
        ocrEdtCreate(&addEdtGuid, templGuid,
            /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
            /*depc=*/EDT_PARAM_DEF, /*depv=*/NULL,
            /*properties=*/EDT_PROP_NONE,
            /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
        ocrAddDependence(params->firstBlock, addEdtGuid, 0, DB_MODE_EW);
        ocrAddDependence(paramsGuid, addEdtGuid, 1, DB_DEFAULT_MODE);
        ocrEdtTemplateDestroy(templGuid);
    }
    else { // keep looking...
        // search next
        ocrGuid_t deps[] = { block->next, paramsGuid };
        ocrGuid_t searchEdtGuid, templGuid;
        ocrEdtTemplateCreate(&templGuid, _searchBucketEdt, 0, 2);
        ocrEdtCreate(&searchEdtGuid, templGuid,
            /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
            /*depc=*/EDT_PARAM_DEF, /*depv=*/deps,
            /*properties=*/EDT_PROP_NONE,
            /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
        ocrEdtTemplateDestroy(templGuid);
    }
    return NULL_GUID;
}

static ocrGuid_t _doHashEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    // unpack
    ocrGuid_t *blockArray = depv[0].ptr;
    ItemCollOpParams *params = depv[1].ptr;
    ocrGuid_t paramsGuid = depv[1].guid;
    // find the the bucket index
    u64 hash = _hash_function(params->tag, params->tagLength);
    u32 index = hash % CNC_TABLE_SIZE;
    // save bucket info
    params->bucketIndex = index;
    params->firstBlock = blockArray[index];
    params->oldFirstBlock = NULL_GUID;
    params->checkedFirst = 0;
    if (params->firstBlock == NULL_GUID) { // empty bucket
        // might need to add a new block to the bucket
        ocrGuid_t addEdtGuid, templGuid;
        ocrEdtTemplateCreate(&templGuid, _addToBucketEdt, 0, 2);
        ocrEdtCreate(&addEdtGuid, templGuid,
            /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
            /*depc=*/EDT_PARAM_DEF, /*depv=*/NULL,
            /*properties=*/EDT_PROP_NONE,
            /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
        ocrAddDependence(params->collection, addEdtGuid, 0, DB_MODE_EW);
        ocrAddDependence(paramsGuid, addEdtGuid, 1, DB_DEFAULT_MODE);
        ocrEdtTemplateDestroy(templGuid);
    }
    else { // search the bucket
        ocrGuid_t deps[] = { params->firstBlock, paramsGuid };
        ocrGuid_t searchEdtGuid, templGuid;
        ocrEdtTemplateCreate(&templGuid, _searchBucketEdt, 0, 2);
        ocrEdtCreate(&searchEdtGuid, templGuid,
            /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
            /*depc=*/EDT_PARAM_DEF, /*depv=*/deps,
            /*properties=*/EDT_PROP_NONE,
            /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
        ocrEdtTemplateDestroy(templGuid);
    }
    return NULL_GUID;
}

static void _itemCollUpdate(ocrGuid_t coll, u8 *tag, u32 tagLength, u8 role, ocrGuid_t entry, u32 slot, ocrDbAccessMode_t mode) {
    // Build datablock to hold search parameters
    ocrGuid_t paramsGuid;
    ItemCollOpParams *params;
    CNC_CREATE_ITEM(&paramsGuid, (void**)&params, sizeof(ItemCollOpParams)+tagLength);
    params->collection = coll;
    params->entry = entry;
    params->tagLength = tagLength;
    params->role = role;
    params->slot = slot;
    params->mode = mode;
    MEMCPY(params->tag, tag, tagLength);
    // edt
    ocrGuid_t deps[] = { coll, paramsGuid };
    ocrGuid_t shutdownEdtGuid, templGuid;
    ocrEdtTemplateCreate(&templGuid, _doHashEdt, 0, 2);
    ocrEdtCreate(&shutdownEdtGuid, templGuid,
        /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
        /*depc=*/EDT_PARAM_DEF, /*depv=*/deps,
        /*properties=*/EDT_PROP_NONE,
        /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
    ocrEdtTemplateDestroy(templGuid);
}

/* Putting an item into the hashmap */
bool _cncPut(ocrGuid_t item, unsigned char *tag, int tagLength, cncItemCollection_t collection, bool isSingleAssignment) {
    _itemCollUpdate(collection, tag, tagLength, CNC_PUTTER_ROLE, item, 0, DB_DEFAULT_MODE);
    return true;
}

/* Get GUID from an item tag */
void _cncGet(unsigned char *tag, int tagLength, ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, cncItemCollection_t collection) {
    _itemCollUpdate(collection, tag, tagLength, CNC_GETTER_ROLE, destination, slot, mode);
}
{% endblock arch_itemcoll_impl %}
/* Put a singleton item */
bool _cncPutSingleton(ocrGuid_t item, ocrGuid_t collection, bool isSingleAssignment) {
    ocrEventSatisfy(collection, item);
    return true;
}

/* Get GUID for singleton item */
void _cncGetSingleton(ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, ocrGuid_t collection) {
    ocrAddDependence(collection, destination, slot, mode);
}

static ocrGuid_t _shutdownEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    ocrShutdown();
    return NULL_GUID;
}

void cncAutomaticShutdown(ocrGuid_t doneEvent) {
    ocrGuid_t shutdownEdtGuid, templGuid;
    ocrEdtTemplateCreate(&templGuid, _shutdownEdt, 0, 1);
    ocrEdtCreate(&shutdownEdtGuid, templGuid,
        /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
        /*depc=*/EDT_PARAM_DEF, /*depv=*/&doneEvent,
        /*properties=*/EDT_PROP_NONE,
        /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
    ocrEdtTemplateDestroy(templGuid);
}
