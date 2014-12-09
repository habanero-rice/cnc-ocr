{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

{% set defname = "_CNCOCR_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#ifdef CNC_DEBUG
#define OCR_ASSERT
#endif

#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(__i386__) || defined(__x86_64__)
#    define CNCOCR_x86 1
#elif defined(TG_ARCH)
{% if logEnabled %}
#    error "CnC logging is not supported on FSim."
{% endif -%}
#    define CNCOCR_TG 1
#else
#    warning UNKNOWN PLATFORM (possibly unsupported)
#endif

// XXX - OCR assert bug workaround
#if defined(CNC_DEBUG) && CNCOCR_x86
#undef ASSERT
#define ASSERT(x) assert(x)
#include <assert.h>
#endif

{% block arch_includes %}{% endblock arch_includes %}
/********************************\
******** CNC TYPE ALIASES ********
\********************************/

typedef s64 cncTag_t; // tag components
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
#define CNC_REQUIRE(cond, ...) do { if (!(cond)) { PRINTF(__VA_ARGS__); ocrShutdown(); } } while (0)
#endif

/* squelch "unused variable" warnings */
#define MAYBE_UNUSED(x) ((void)x)

/* helpers for accessing packed argc/argv in ocrMain */
#define OCR_MAIN_ARGC OCR_ARGC(depv[0])
#define OCR_ARGC(dep) getArgc(dep.ptr)
#define OCR_MAIN_ARGV(i) OCR_ARGV(depv[0], i)
#define OCR_ARGV(dep, i) getArgv(dep.ptr, i)

#define CNC_SHUTDOWN_ON_FINISH(ctx) cncAutomaticShutdown((ctx)->_guids.doneEvent)

/************************************************\
********* CNC ITEM MANAGEMENT FUNCTIONS *********
\************************************************/
// Cookie value for sanity-checking CnC items
// (before trying to extract the GUID)
static const u64 _CNC_ITEM_COOKIE = 0xC17C0C12;

// How much space do we need to store meta-data for CnC items?
#ifdef CNC_DEBUG
static const u64 _CNC_ITEM_META_SIZE = sizeof(ocrGuid_t) + sizeof(u64);
#else
static const u64 _CNC_ITEM_META_SIZE = sizeof(ocrGuid_t);
#endif

static inline void _cncItemCheckCookie(void *item) {
    #ifdef CNC_DEBUG
    if (item) {
        u64 *data = item;
        ASSERT(data[-1] == _CNC_ITEM_COOKIE && "Not a valid CnC item");
    }
    #endif
}

static inline ocrGuid_t _cncItemGuid(void *item) {
    if (!item) return NULL_GUID;
    u8 *data = item;
    return *(ocrGuid_t*)&data[-_CNC_ITEM_META_SIZE];
}

static inline void *_cncItemDataPtr(void *item) {
    if (!item) return NULL;
    u8 *data = item;
    return &data[_CNC_ITEM_META_SIZE];
}


/********************************************\
********* CNC COMPATIBILITY FUNCTIONS ********
\********************************************/
{% block arch_compat_macros %}
// XXX - re-enalbe these when we get pdMalloc from OCR
//#define MALLOC pdMalloc
//#define FREE   pdFree
{% endblock arch_compat_macros %}
void *cncMalloc(size_t count);
void cncFree(void *itemPtr);

{% if logEnabled %}
/**********************************\
********* CNC DEBUG LOGGING ********
\**********************************/
extern FILE *cncDebugLog;

{% endif -%}
#endif /*{{defname}}*/
