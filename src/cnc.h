/**
 * This file is part of the CNC-C implementation and
 * distributed under the Modified BSD License.
 * See LICENSE for details.
 *
 * The standard include file for cnc
 * 
 * Created on: April 1st, 2010
 * Author: zoran
 */

#ifndef _CNC_H
#define _CNC_H

#include "cnc_mm.h"
#include <ocr.h>

#define CNC_SUCCESS 0
#define CNC_ABORT 1

#define CNC_GET_ENTRY 1
#define CNC_PUT_ENTRY 2

#define PUT_FAIL 1
#define PUT_SUCCESS 0

#define SINGLE_ASSIGNMENT_ENFORCED 1
#define SKIP_SINGLE_ASSIGNMENT 0

 /* A macro for CnC Get function. We need to use a macro in order to simulate exceptional behaviour,  
  * if a step does a Get that returns the special value CNC_ABORT, we need to abort the step instead of continuing 
  * the execution 
  */
#define CNC_GET(result,tag,collection,whoscalling)\
   do { \
      int code = __Get(result,tag,collection,whoscalling); \
      cnc_free(tag);\
      if(code == CNC_ABORT) return 0;\
   } while(0);

#define CNC_ASSERT(check, msg) do { ASSERT((check) && msg); } while (0)

/* squelch unused variable warnings */
#define MAYBE_UNUSED(x) ((void)x)

struct Context;

#endif /* _CNC_H */




