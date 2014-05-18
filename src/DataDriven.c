/**
 * This file is part of the CNC-C implementation and
 * distributed under the Modified BSD License. 
 * See LICENSE for details.
 *
 * DataDriven.c
 * 
 * The purpose of this library is to provide a non-blocking implementation of the item collections in C for CnC
 *
 *  Created on: Feb 17, 2010
 *      Authors: zoran, alina
 */

#include "cnc.h"
#include "DataDriven.h"
#include <stdlib.h>
#include <string.h>

/* This is the pseudo-code for data-driven implementation of item gets and puts to enable the CnC implementation */

/*
 * Test if two tags are equal. Right now, we are only doing string comparisons since we only allow strings for tags
 */
static int equals(unsigned char * tag1, unsigned char * tag2, int length) {
    return memcmp(tag1, tag2, length) == 0;
}

/* Hash function implementation. Fast and pretty good */
static unsigned long hash_function(unsigned char *str, int length) {
    unsigned long hash = 5381;
    int c;
    while (length-- > 0) {
        c = *str++;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

/* get an entry from the item collection, or create and insert one 
 * (atomically) if it doesn't exist 
 * The creator parameter CNC_PUT_ENTRY/CNC_GET_ENTRY ensures that multiple 
 * puts are not allowed
 */
static ItemCollectionEntry * allocateEntryIfAbsent(
        ItemCollectionEntry * volatile * hashmap, unsigned char * tag,
        int length, char creator, char isSingleAssignment) {
    int index = (hash_function(tag, length)) % TABLE_SIZE;
    ItemCollectionEntry * volatile current = hashmap[index];

    /* ACHTUNG: pointer arithmetic! This SHOULD give the address of the i'th element of the hashmap array, but maybe there is a more elegant way to do that */
    ItemCollectionEntry * volatile * currentLocation = &hashmap[index];
    ItemCollectionEntry * volatile head = current;
    ItemCollectionEntry * volatile tail = NULL;

    ItemCollectionEntry * entry = NULL;

    while (1) {
        /* traverse the buckets in the table to get to the last one */
        while (current != tail) {
            if (equals(current->tag, tag, length)) {
                /* deallocate the entry we eagerly allocated in a previous iteration of the outer while(1) loop */
                if (entry != NULL){
                    ocrEventDestroy(entry->event);
                    cnc_free(entry);
                }
                    
                // XXX - PutIfAbsent is kind of broken here if creator is GET
                // but using IDEM events still gives the correct behavior
                if ((current->creator == CNC_PUT_ENTRY) && (creator == CNC_PUT_ENTRY)) {
                    if (isSingleAssignment)
                        CNC_ASSERT(0, "Single assignment rule violated in item collection put");
                    else
                        return NULL;
                }
                return current; /* just return the table entry if it already has the tag */
            }
            current = current->nxt;
        }

        // XXX Why is this commented out?
        /* current has to be NULL now */
/*        CNC_ASSERT(current == tail,
                "Current pointer is not NULL in the allocateEntryIfAbstent function\n");
*/
        /* allocate a new entry if this is the first time we are going to try and insert a new entry to the end of the bucket list */
        if (entry == NULL) {
            entry = (ItemCollectionEntry *) cnc_malloc(sizeof(ItemCollectionEntry)+length);
            entry->creator = creator;
            memcpy(entry->tag, tag, length);
            ocrEventCreate(&(entry->event), OCR_EVENT_IDEM_T, true);
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

    CNC_ASSERT(0, "Arrived at the end of allocateEntryIfAbsent in DataDriven.c"); /* we should never get here */
    return NULL;
}

/* Putting an item into the hashmap */
static int _Put(ocrGuid_t item, char * tag, int tagLength, ItemCollectionEntry ** hashmap, char isSingleAssignment) {
    
    CNC_ASSERT(tag != NULL, "Put - ERROR================%p\n");

    /* allocateEntryIfAbsent checks for multiple puts using the "CNC_PUT_ENTRY" parameter */
    ItemCollectionEntry * entry = allocateEntryIfAbsent(hashmap, tag, tagLength, CNC_PUT_ENTRY, isSingleAssignment);

    /* the returned placeholder can be NULL only when isSingleAssignment is false. 
       in which case, the item was Put previously, so the current Put returns */
    if(entry == NULL && !isSingleAssignment)
        return PUT_FAIL;
    /* Now, we have the correct placeholder (either inserted by us or by a Get function) */

    /* Inserting the item now boils down to just satisfying the event with a data block of the item. */
    ocrEventSatisfy(entry->event, item);

    return PUT_SUCCESS;
}

int cncPut(ocrGuid_t item, char * tag, int tagLength, ItemCollectionEntry ** hashmap){
    return _Put(item, tag, tagLength, hashmap, SINGLE_ASSIGNMENT_ENFORCED);
}

int cncPutIfAbsent(ocrGuid_t item, char * tag, int tagLength, ItemCollectionEntry ** hashmap){
    return _Put(item, tag, tagLength, hashmap, SKIP_SINGLE_ASSIGNMENT);
}

/* Register a step as a consumer of the item in the hasmap */
void __cncRegisterConsumer(char * tag, int tagLength,
        ItemCollectionEntry * volatile * hashmap, ocrGuid_t stepToRegister, u32 slot) {
    ItemCollectionEntry * entry = allocateEntryIfAbsent(hashmap, tag, tagLength, CNC_GET_ENTRY, SINGLE_ASSIGNMENT_ENFORCED);
    ocrAddDependence(entry->event, stepToRegister, slot, DB_DEFAULT_MODE);
}

