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

#define CNC_ASSERT(check, msg) do { ASSERT((check) && msg); } while (0)

struct Context;

/* warning for variadic macro support */
#if __GNUC__ < 3 && !defined(__clang__) && __STDC_VERSION__ < 199901L && !defined(NO_VARIADIC_MACROS)
#warning Your compiler might not support variadic macros, in which case the CNC_REQUIRE macro is not supported. You can disable this warning by setting NO_VARIADIC_MACROS to 0, or disable the macro definitions by setting it to 1.
#endif

#if !NO_VARIADIC_MACROS
#define CNC_REQUIRE(cond, ...) do { if (!(cond)) { PRINTF(__VA_ARGS__); ocrShutdown(); exit(1); } } while (0)
#endif

#define CNC_DESTROY_ITEM(handle) ocrDbDestroy(handle); // free datablock backing an item
#define CNC_CREATE_ITEM(handle, ptr, size) DBCREATE(handle, ptr, size, DB_PROP_NONE, NULL_GUID, NO_ALLOC)
#define CNC_NULL_HANDLE NULL_GUID

#endif /* _CNC_H */




