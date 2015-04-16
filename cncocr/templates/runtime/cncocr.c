#include "cncocr_internal.h"
{#
// TODO:
// Instead of having a isSingleAssignment argument for each of the
// item put functions, we should have some sort of tuning parameter
// that lets us choose to use STICKY or IDEM events in the collection?
// Then satisfying the event would give the desired behavior.
// (We'd also have to check if it's an event or a data block guid.)
#}
{% if logEnabled %}
FILE *cncDebugLog;

FILE *getCnCDebugLog() { return cncDebugLog; }

{% endif -%}
{% block arch_itemcoll_defs %}
{% endblock arch_itemcoll_defs %}

/* Compare byte-by-byte for tag equality */
static bool _equals(u8 *tag1, u8 *tag2, u32 length) {
    return CNC_MEMCMP(tag1, tag2, length) == 0;
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
{% endblock arch_itemcoll_impl %}

void cncAutomaticShutdown(cncHandle_t doneEvent) {
    // hc_comm_terminate(current_ws());
}

ocrEdtDep_t _cncRangedInputAlloc(u32 n, u32 dims[], size_t itemSize) {
    u32 i, j, k;
    ///////////////////////////////////////
    // Figure out how much memory we need
    ///////////////////////////////////////
    u32 sum = 0, product = 1;
    for (i=0; i<n-1; i++) {
        product *= dims[i];
        sum += sizeof(void*) * product;
    }
    product *= dims[i];
    sum += itemSize * product;
    ///////////////////////////////////////
    // Allocate a datablock
    ///////////////////////////////////////
    ocrEdtDep_t block;
    CNC_CREATE_ITEM(&block.guid, &block.ptr, sum);
    ///////////////////////////////////////
    // Set up the internal pointers
    ///////////////////////////////////////
    if (n > 1) {
        u32 prevDim = 1, currDim = 1, nextDim = dims[0];
        void **ptrs = block.ptr;
        void **current = ptrs;
        void **tail = ptrs + nextDim; // make room for first array
        for (i=1; i<n-1; i++) {
            // Slide the window
            prevDim = currDim;
            currDim = nextDim;
            nextDim = dims[i];
            // One array for each parent
            for (j=0; j<prevDim; j++) {
                // Initialize each current pointer
                for (k=0; k<currDim; k++) {
                    *current = (void*)tail;
                    tail += nextDim; // Make room for new array
                    ++current;
                }
            }
        }
        u8 **itemCurrent = (u8**)current;
        u8 *itemTail = (u8*)tail;
        // Slide the window
        prevDim = currDim;
        currDim = nextDim;
        nextDim = dims[i];
        // One array for each last-level parent
        for (j=0; j<prevDim; j++) {
            // Initialize each current pointer
            for (k=0; k<currDim; k++) {
                *itemCurrent = itemTail;
                itemTail += itemSize * nextDim; // Make room for new items
                ++itemCurrent;
            }
        }
        ASSERT(itemTail == ((u8*)ptrs + sum));
    }
    ///////////////////////////////////////
    // Return the initialized datablock
    ///////////////////////////////////////
    return block;
}

