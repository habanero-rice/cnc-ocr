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

/* The structure to hold an item in the item collection */
struct ItemCollectionEntry {
  ocrGuid_t event; /* The event representing the data item. Data will be put through the event when it is satisfied */
  ItemCollectionEntry * volatile nxt; /* The next bucket in the hashtable */
  char creator; /* Who created this entry (could be from a Put or a Get)*/
  char tag[]; /* Tags are byte arrays, with a known length for each item collection */
};

#define DEPS_BUCKET 3 /* must be >=3 */

int cncPut(ocrGuid_t item, char * tag, int tagLength, ItemCollectionEntry ** hashmap);

int cncPutIfAbsent(ocrGuid_t item, char * tag, int tagLength, ItemCollectionEntry ** hashmap);
void  __cncRegisterConsumer(char * tag, int tagLength, ItemCollectionEntry * volatile * hashmap, ocrGuid_t stepToRegister, u32 slot);

/* warning for variadic macro support */
#if __GNUC__ < 3 && !defined(__clang__) && __STDC_VERSION__ < 199901L && !defined(NO_VARIADIC_MACROS)
#warning Your compiler might not support variadic macros, in which case the CNC_REQUIRE macro is not supported. You can disable this warning by setting NO_VARIADIC_MACROS to 0, or disable the macro definitions by setting it to 1.
#endif

#if !NO_VARIADIC_MACROS
#define CNC_REQUIRE(cond, ...) do { if (!(cond)) { PRINTF(__VA_ARGS__); ocrShutdown(); exit(1); } } while (0)
#endif

#define CNC_GET_FROM_TAG(tag, pos) (((int*)(tag))[(pos)]);
#define CNC_DESTROY_ITEM(handle) ocrDbDestroy(handle); // free datablock backing an item
#define CNC_CREATE_ITEM(handle, ptr, size) DBCREATE(handle, ptr, size, DB_PROP_NONE, NULL_GUID, NO_ALLOC)
#define CNC_NULL_HANDLE NULL_GUID

#endif /* _DATA_DRIVEN_H */

