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

typedef ocrGuid_t cncHandle_t;

typedef struct ItemCollectionEntry ItemCollectionEntry;

/* The structure to hold an item in the item collection */
struct ItemCollectionEntry {
  char * tag; /* Tags are NULL-terminated char arrays for now */
  ocrGuid_t event; /* The event representing the data item. Data will be put through the event when it is satisfied */
  ItemCollectionEntry * volatile nxt; /* The next bucket in the hashtable */
  char creator; /* Who created this entry (could be from a Put or a Get)*/
};

#define DEPS_BUCKET 3 /* must be >=3 */

int Put(cncHandle_t item, char * tag, ItemCollectionEntry ** hashmap);

int PutIfAbsent(cncHandle_t item, char * tag, ItemCollectionEntry ** hashmap);
void  __registerConsumer(char * tag, ItemCollectionEntry * volatile * hashmap, ocrGuid_t stepToRegister, u32 slot);

char* createTag(int no_args, ...);

/* warning for variadic macro support */
#if __GNUC__ < 3 && !defined(__clang__) && __STDC_VERSION__ < 199901L && !defined(NO_VARIADIC_MACROS)
#warning Your compiler might not support variadic macros, in which case the CREATE_TAG macro is not supported. You can instead use the createTag function with an explicit arg count. You can disable this warning by setting NO_VARIADIC_MACROS to 0, or disable the macro definitions by setting it to 1.
#endif

#if !NO_VARIADIC_MACROS
#define TAG_LENGTH(...) (sizeof((u64[]){__VA_ARGS__})/sizeof(u64))
#define CREATE_TAG(...) createTag(TAG_LENGTH(__VA_ARGS__), __VA_ARGS__)
#endif

int getTag(char* tag, int pos);

cncHandle_t cncGet(char* tag, ItemCollectionEntry ** hashmap);

#define CREATE_ITEM_INSTANCE(guid, ptr, size) DBCREATE(guid, ptr, size, DB_PROP_NONE, NULL_GUID, NO_ALLOC)

#endif /* _DATA_DRIVEN_H */

