/**
 * This file is part of the CNC-C implementation and
 * distributed under the Modified BSD License.
 * See LICENSE for details.
 *
 * Memory management for cnc
 * 
 * Created on: April 1st, 2010
 * Author: zoran
 */

#ifndef _CNC_MM_H
#define _CNC_MM_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ocr.h>

//#define USE_HC_MEMORY_ALLOCATION

/* For now, we are only calling malloc directly. This can be linked to hoard or some other scalable allocator. */
static __inline__ void*  cnc_malloc(size_t msize){

#ifdef USE_HC_MEMORY_ALLOCATION
  void* val = hc_malloc(msize);
#else
  void* val = malloc(msize);
#endif
  if (val==NULL) {
  	printf("Out of memory in cnc_malloc!\n");
	assert(0); 
	return NULL;
  }
  return val;
}

static __inline__ void cnc_free(void* object){

#ifdef USE_HC_MEMORY_ALLOCATION
  hc_free(object);
#else
  free(object);
#endif
}

#endif /* _CNC_MM_H */
