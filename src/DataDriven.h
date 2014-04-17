/**
 * This file is part of the CNC-C implementation and
 * distributed under the Modified BSD License.
 * See LICENSE for details.
 *
 * DataDriven.h
 * 
 * The purpose of this library is to provide a non-blocking implementation of the item collections in C for CnC
 *
 *  Created on: March 03, 2010
 *      Authors: zoran, alina
 */

#ifndef _DATA_DRIVEN_H
#define _DATA_DRIVEN_H
#include "ocr.h"

#define TABLE_SIZE 512 /* TODO: Table size should be set by the user when initializing the item collection */
#define _ROLLBACK_AND_REPLAY 0
#define _DATA_DRIVEN 1

#ifdef _DATA_DRIVEN
#define _CNC_POLICY _DATA_DRIVEN
#else
#define _CNC_POLICY _ROLLBACK_AND_REPLAY
#endif

#define LIST_REMOVED 1
#include "cnc.h"
#include <stdarg.h>

typedef struct ItemCollectionEntry ItemCollectionEntry;
//typedef struct Step Step;
//typedef struct WaitData WaitData;

/* The structure to hold an item in the item collection */
struct ItemCollectionEntry{
  char * tag; /* Tags are NULL-terminated char arrays for now */
  ocrGuid_t event; /* The event representing the data item. Data will be put through the event when it is satisfied */
  ItemCollectionEntry * volatile nxt; /* The next bucket in the hashtable */
  char creator; /* Who created this entry (could be from a Put or a Get)*/
};


/*

struct Step{
  int stepID;  a unique ID of the step that needs to be executed
  char * tag;  The tag of the step that needs to be executed
  void * context;  Context contains the info about the graph and the collections in the graph
  Step * volatile nxt;  the next Step in the list, this is used for linking the steps into lists when they are waiting for data
  WaitData * dependencies;
  WaitData * start_end;
  WaitData * failed;
};

struct WaitData{
  ItemCollectionEntry ** hashmap;
  char * tag;
  void * data;
  WaitData * volatile nxt;
};

*/

#define DEPS_BUCKET 3 /* must be >=3 */
//extern WaitData* big_thingie;

/*void CNC_ASSERT(int exp, char* message){
  if(!exp){
    fprintf(stderr, message);
    fprintf(stderr, "\n");
    assert(exp);
  }
}*/


int Put(ocrGuid_t item, char * tag, ItemCollectionEntry ** hashmap);

int PutIfAbsent(ocrGuid_t item, char * tag, ItemCollectionEntry ** hashmap);
void  __registerConsumer(char * tag, ItemCollectionEntry * volatile * hashmap, ocrGuid_t stepToRegister, u32 slot);

char* createTag(int no_args, ...);

#if __STDC_VERSION__ >= 199901L /* C99-only macros */
#define TAG_LENGTH(...) (sizeof((u64[]){__VA_ARGS__})/sizeof(u64))
#define CREATE_TAG(...) createTag(TAG_LENGTH(__VA_ARGS__), __VA_ARGS__)
#endif

int getTag(char* tag, int pos);

ocrGuid_t cncGet(char* tag, ItemCollectionEntry ** hashmap);

#endif /* _DATA_DRIVEN_H */

