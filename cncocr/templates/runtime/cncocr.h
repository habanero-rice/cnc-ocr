{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

{% set defname = "_CNCOCR_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#include <ocr.h>
#include <stdio.h>
#include <stdlib.h>

{% block arch_includes %}{% endblock arch_includes %}
/********************************\
******** CNC TYPE ALIASES ********
\********************************/

typedef s64 cncTag_t; // tag components
typedef ocrGuid_t cncHandle_t; // handles
{% block arch_typedefs -%}
typedef ocrGuid_t cncItemCollection_t; // item collections
{% endblock arch_typedefs %}
/*************************************\
******** CNC HELPER FUNCTIONS ********
\*************************************/

// Users should not call this function directly,
// but instead use the CNC_SHUTDOWN_ON_FINISH macro.
void cncAutomaticShutdown(ocrGuid_t doneEvent);

/*********************************\
******** CNC HELPER MACROS ********
\*********************************/

/* warning for variadic macro support */
#if __GNUC__ < 3 && !defined(__clang__) && __STDC_VERSION__ < 199901L && !defined(NO_VARIADIC_MACROS)
#warning Your compiler might not support variadic macros, in which case the CNC_REQUIRE macro is not supported. You can disable this warning by setting NO_VARIADIC_MACROS to 0, or disable the macro definitions by setting it to 1.
#endif

#if !NO_VARIADIC_MACROS
#define CNC_REQUIRE(cond, ...) do { if (!(cond)) { PRINTF(__VA_ARGS__); ocrAbort(1); } } while (0)
#endif

#define CNC_DESTROY_ITEM(handle) ocrDbDestroy(handle) /* free datablock backing an item */

#define CNC_CREATE_ITEM(handle, ptr, size) ocrDbCreate(handle, ptr, size, DB_PROP_NONE, NULL_GUID, NO_ALLOC)

#define CNC_NULL_HANDLE NULL_GUID

/* squelch "unused variable" warnings */
#define MAYBE_UNUSED(x) ((void)x)

/* helpers for accessing packed argc/argv in ocrMain */
#define OCR_MAIN_ARGC OCR_ARGC(depv[0])
#define OCR_ARGC(dep) (((u64*)(dep).ptr)[0])
#define OCR_MAIN_ARGV(i) OCR_ARGV(depv[0], i)
#define OCR_ARGV(dep, i) (((char*)(dep).ptr)+((u64*)(dep).ptr)[(i)+1])

#define CNC_SHUTDOWN_ON_FINISH(ctx) cncAutomaticShutdown((ctx)->_guids.doneEvent)

/*****************************************\
********* CNC COMPATIBILITY MACROS ********
\*****************************************/
{% block arch_compat_macros %}
// XXX - how do we access pdMalloc / pdFree in OCR?
//#warning MALLOC undefined for current platform (falling back to stdlib.h)
extern void *malloc(size_t);
#define MALLOC malloc

//#warning FREE undefined for current platform (falling back to stdlib.h)
extern void free(void*);
#define FREE free

// XXX - do we need to implement these ourselves?
//#warning MEMCPY undefined for current platform (falling back to string.h)
extern void *memcpy(void *dest, const void *src, size_t n);
#define MEMCPY memcpy

//#warning MEMCMP undefined for current platform (falling back to string.h)
extern int memcmp(const void *s1, const void *s2, size_t n);
#define MEMCMP memcmp
{% endblock arch_compat_macros %}

#endif /*{{defname}}*/
