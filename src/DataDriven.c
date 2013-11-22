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

#include "DataDriven.h"
#include <ocr.h>
#include <stdlib.h>
#include "cnc.h"
#include <string.h>


/* This is the pseudo-code for data-driven implementation of item gets and puts to enable the CnC implementation */

/*
 * Test if two tags are equal. Right now, we are only doing string comparisons since we only allow strings for tags
 */
int equals(unsigned char * tag1, unsigned char * tag2) {
	return (!strcmp(tag1, tag2));
}

/* Hash function implementation. Fast and pretty good */
unsigned long hash_function(unsigned char *str) {
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

/* get an entry from the item collection, or create and insert one 
 * (atomically) if it doesn't exist 
 * The creator parameter CNC_PUT_ENTRY/CNC_GET_ENTRY ensures that multiple 
 * puts are not allowed
 */
ItemCollectionEntry * allocateEntryIfAbsent(
		ItemCollectionEntry * volatile * hashmap, unsigned char * tag, char creator, char isSingleAssignment) {
	int index = (hash_function(tag)) % TABLE_SIZE;
	ItemCollectionEntry * volatile current = hashmap[index];

	/* ACHTUNG: pointer arithmetic! This SHOULD give the address of the i'th element of the hashmap array, but maybe there is a more elegant way to do that */
	ItemCollectionEntry * volatile * currentLocation = &hashmap[index];
	ItemCollectionEntry * volatile head = current;
	ItemCollectionEntry * volatile tail = NULL;

	ItemCollectionEntry * entry = NULL;

	while (1) {
		/* traverse the buckets in the table to get to the last one */
		while (current != tail) {
			if (equals(current->tag, tag)) {
				/* deallocate the entry we eagerly allocated in a previous iteration of the outer while(1) loop */
				if (entry != NULL){
					ocrEventDestroy(entry->event);
					cnc_free(entry);
				}
					
				if ((current->creator == CNC_PUT_ENTRY) && (creator == CNC_PUT_ENTRY)) {
					if (isSingleAssignment)
					{	
						CNC_ASSERT(0, "Single assignment rule violated in item collection put\n");
					}
					else
						return NULL;
				}
				return current; /* just return the table entry if it already has the tag */
			}
			current = current->nxt;
		}

		/* current has to be NULL now */
/*		CNC_ASSERT(current == tail,
				"Current pointer is not NULL in the allocateEntryIfAbstent function\n");
*/
		/* allocate a new entry if this is the first time we are going to try and insert a new entry to the end of the bucket list */
		if (entry == NULL) {
			entry = (ItemCollectionEntry *) cnc_malloc(
					sizeof(ItemCollectionEntry));
			entry->creator = creator;
			entry->tag = (char*) cnc_malloc(strlen(tag) + 1);
			strcpy(entry->tag, tag);
			ocrEventCreate(&(entry->event), OCR_EVENT_STICKY_T, true);
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
int _Put(ocrGuid_t item, char * tag, ItemCollectionEntry ** hashmap, char isSingleAssignment) {
	
	CNC_ASSERT(tag != NULL, "Put - ERROR================%p\n");

	/* allocateEntryIfAbsent checks for multiple puts using the "CNC_PUT_ENTRY" parameter */
	ItemCollectionEntry * entry = allocateEntryIfAbsent(hashmap, tag, CNC_PUT_ENTRY, isSingleAssignment);

	/* the returned placeholder can be NULL only when isSingleAssignment is false. 
	   in which case, the item was Put previously, so the current Put returns */
	if(entry == NULL && !isSingleAssignment)
		return PUT_FAIL;
	/* Now, we have the correct placeholder (either inserted by us or by a Get function) */

	/* Inserting the item now boils down to just satisfying the event with a data block of the item. */
	ocrEventSatisfy(entry->event, item);

	return PUT_SUCCESS;
}

int Put(ocrGuid_t item, char * tag, ItemCollectionEntry ** hashmap){
	int ret = 0;
	ret = _Put(item, tag, hashmap, SINGLE_ASSIGNMENT_ENFORCED);
	return ret;
}

int PutIfAbsent(ocrGuid_t item, char * tag, ItemCollectionEntry ** hashmap){
	int ret = 0;
	ret = _Put(item, tag, hashmap, SKIP_SINGLE_ASSIGNMENT);
	return ret;
}

/* Register a step as a consumer of the item in the hasmap */

void __registerConsumer(char * tag, ItemCollectionEntry * volatile * hashmap,
		ocrGuid_t stepToRegister, u32 slot) {
	ItemCollectionEntry * entry = allocateEntryIfAbsent(hashmap, tag, CNC_GET_ENTRY, SINGLE_ASSIGNMENT_ENFORCED);

	ocrAddDependence(entry->event, stepToRegister, slot, DB_DEFAULT_MODE);

}



char* createTag(int no_args, ...)
{
	va_list argp;
	va_start(argp, no_args);
	int count = 0;
	int n = no_args, i;
	for( ; n>=0; n--)
	{
		int k = va_arg(argp, int);
		if (k == 0) count++;
		else while(k>0){  k = k/10; count++; }
		count++;
	}
	va_end(argp);

	n = no_args;
	char* tag = (char*) cnc_malloc ( (count+1) *sizeof(char) );

	char pattern[3*n];
	for(i=0; i<n; i++){
		pattern[3*i] = '%';
		pattern[3*i+1] = 'd';
		pattern[3*i+2] = ' ';
	}
	pattern[3*n-1] = '\0';

	va_list argp2;
	va_start(argp2, no_args);
	vsprintf(tag, &(pattern[0]), argp2);
	va_end(argp2);
	return tag;
}

int getTag(char* tag, int pos)
{
        int i = -1;
        int ssize = strlen(tag) + 1;
        char copy [ssize];
        strcpy(copy, tag);
        char * p = &(copy[0]);
        char * r = p;
        char * prev = r;
        while(i < pos){
                if(p[0] == ' ' || p[0] == '\0'){
                        i++;
                        r = prev;
                        prev = p+1;
                        if(p[0] == '\0')
                                break;
                        p[0] = '\0';
                }
                p++;
        }
        if(i == pos){
                return atoi(r);
        }
        printf("Could not retrive position %d from tag (%s)\n", pos, tag);
        assert( 0 );
        return -1;
}


ocrGuid_t getEdt ( u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]) {

    void *** result = (void***)paramv;

    printf("In the GetEDT.\n");

    **result = (void*)depv[0].ptr;

    return NULL_GUID;
}

int cncGet(void** result, char* tag, ItemCollectionEntry ** hashmap)
{

    ocrGuid_t edt_guid;
    ocrGuid_t done_guid;

    ocrGuid_t tmp_guid;
    ocrEdtTemplateCreate(&tmp_guid, getEdt, 1, 1);

    ocrEdtCreate(&edt_guid, tmp_guid, /*paramc=*/1,
                  /*paramv=*/(u64*) & result, 
                  /*depc=*/1, /*depv=*/NULL, 
                  /*properties=*/EDT_PROP_FINISH, /*affinity*/NULL_GUID,
                  /*outEvent=*/&done_guid);
    __registerConsumer(tag, hashmap, edt_guid, 0);
    //ocrEdtExecute(edt_guid);

}



