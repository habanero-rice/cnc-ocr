{% extends "runtime/cncocr.c" %}

{% block arch_itemcoll_defs %}
#include <string.h>
#define CNC_MEMCMP memcmp

#define DEPS_BUCKET 3 /* must be >=3 */

#define CNC_GETTER 1
#define CNC_PUTTER 2

#define SINGLE_ASSIGNMENT_ENFORCED 1
#define SKIP_SINGLE_ASSIGNMENT 0

/* The structure to hold an item in the item collection */
typedef struct ItemCollEntry {
    DDF_t ddf;
    struct ItemCollEntry * volatile nxt; /* The next bucket in the hashtable */
    char creator; /* Who created this entry (could be from a Put or a Get)*/
    unsigned char tag[]; /* Tags are byte arrays, with a known length for each item collection */
} ItemCollectionEntry;

{% endblock arch_itemcoll_defs %}

{% block arch_itemcoll_impl %}
/* get an entry from the item collection, or create and insert one 
 * (atomically) if it doesn't exist 
 * The creator parameter CNC_PUTTER/CNC_GETTER ensures that multiple 
 * puts are not allowed
 */
static ItemCollectionEntry * _allocateEntryIfAbsent(
        ItemCollectionEntry * volatile * hashmap, unsigned char * tag,
        int length, char creator, bool isSingleAssignment) {
    int index = (_hash_function(tag, length)) % CNC_TABLE_SIZE;
    hc_workerState * ws = current_ws();
    ItemCollectionEntry * volatile current = hashmap[index];
    ItemCollectionEntry * volatile * currentLocation = &hashmap[index];
    ItemCollectionEntry * volatile head = current;
    ItemCollectionEntry * volatile tail = NULL;

    ItemCollectionEntry * entry = NULL;

    while (1) {
        /* traverse the buckets in the table to get to the last one */
        while (current != tail) {
            if (_equals(current->tag, tag, length)) {
                /* deallocate the entry we eagerly allocated in a previous iteration of the outer while(1) loop */
                if (entry != NULL){
                    HC_FREE(ws, entry);
                }

                // XXX - PutIfAbsent is kind of broken here if creator is GET
                if ((current->creator == CNC_PUTTER) && (creator == CNC_PUTTER)) {
                    if (isSingleAssignment) {
                        ASSERT(!"Single assignment rule violated in item collection put");
                    }
                    return NULL;
                }
                return current; /* just return the table entry if it already has the tag */
            }
            current = current->nxt;
        }

        /* allocate a new entry if this is the first time we are going to try and insert a new entry to the end of the bucket list */
        if (entry == NULL) {
            entry = (ItemCollectionEntry *) HC_MALLOC(ws, sizeof(ItemCollectionEntry)+length);
            entry->creator = creator;
            memcpy(entry->tag, tag, length);
            entry->ddf.kind = DDF_KIND_UNKNOWN;
            entry->ddf.datum = UNINITIALIZED_DDF_DATA_PTR;
            entry->ddf.waitList = UNINITIALIZED_DDF_WAITLIST_PTR;
            #ifdef HC_COMM
            entry->ddf.remoteWaitList = NULL;
            entry->ddf.cancel = 0;
            #endif
        }
        entry->nxt=head;

        /* try to insert the new entry into the _first_ position in a bucket of the table */
        if (__sync_bool_compare_and_swap(currentLocation, head, entry)) {
            return entry;
        }

        /* CAS failed, which means that someone else inserted the new entry into the table while we were trying to do so, we need to try again */
        current = hashmap[index]; //do not update tail anymore if deletes are inserted.
        tail = head;
        head = current;
    }

    ASSERT(!"Arrived at the end of allocateEntryIfAbsent in DataDriven.c"); /* we should never get here */
    return NULL;
}

/* Putting an item into the hashmap */
bool _cncPut(void *item, unsigned char *tag, int tagLength, ItemCollectionEntry ** hashmap, bool isSingleAssignment, int srcRank) {
    
    ASSERT(tag != NULL && "Put - ERROR================\n");

    /* allocateEntryIfAbsent checks for multiple puts using the "CNC_PUTTER" parameter */
    ItemCollectionEntry *entry = _allocateEntryIfAbsent(hashmap, tag, tagLength, CNC_PUTTER, isSingleAssignment);

    /* the returned placeholder can be NULL only when isSingleAssignment is false. 
       in which case, the item was Put previously, so the current Put returns */
    if(entry == NULL && !isSingleAssignment)
        return false;
    /* Now, we have the correct placeholder (either inserted by us or by a Get function) */
#ifdef HC_COMM
    entry->ddf.srcRank = srcRank;
#endif
    CNC_DDF_PUT(&entry->ddf, item);
    LOG_INFO("Put into ddf=%p\n", &entry->ddf);

    return true;
}

/* Get GUID from an item tag */
DDF_t *_cncGet(unsigned char *tag, int tagLength, ItemCollectionEntry **hashmap) {
    ItemCollectionEntry *entry = _allocateEntryIfAbsent(hashmap, tag, tagLength, CNC_GETTER, SINGLE_ASSIGNMENT_ENFORCED);
    return &entry->ddf;
}
{% endblock arch_itemcoll_impl %}
