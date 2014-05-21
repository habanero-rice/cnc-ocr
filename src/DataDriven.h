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
#include <ocr.h>

#define TABLE_SIZE 512 /* TODO: Table size should be set by the user when initializing the item collection */

#include "cnc.h"

typedef ocrGuid_t cncHandle_t;

typedef struct ItemCollectionEntry ItemCollectionEntry;
typedef s32 CncTagComponent;

/* The structure to hold an item in the item collection */
struct ItemCollectionEntry {
  ocrGuid_t event; /* The event representing the data item. Data will be put through the event when it is satisfied */
  ItemCollectionEntry * volatile nxt; /* The next bucket in the hashtable */
  char creator; /* Who created this entry (could be from a Put or a Get)*/
  char tag[]; /* Tags are byte arrays, with a known length for each item collection */
};

#define DEPS_BUCKET 3 /* must be >=3 */

#define CNC_SUCCESS 0
#define CNC_ABORT 1

#define CNC_GET_ENTRY 1
#define CNC_PUT_ENTRY 2

#define PUT_FAIL 1
#define PUT_SUCCESS 0

#define SINGLE_ASSIGNMENT_ENFORCED 1
#define SKIP_SINGLE_ASSIGNMENT 0

int __cncPut(cncHandle_t item, char *tag, int tagLength, ItemCollectionEntry ** hashmap, bool isSingleAssignment);
void  __cncRegisterConsumer(char *tag, int tagLength, ItemCollectionEntry * volatile * hashmap, ocrGuid_t stepToRegister, u32 slot);

#endif /* _DATA_DRIVEN_H */

