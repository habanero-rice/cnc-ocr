{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

{% set defname = "_CNCOCR_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#include "hc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

typedef uint8_t   u8;
typedef int8_t    s8;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint64_t u64;
typedef int64_t  s64;

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

{% block arch_includes %}{% endblock arch_includes %}
/********************************\
******** CNC TYPE ALIASES ********
\********************************/

typedef s32 cncTag_t; // tag components
typedef void *cncHandle_t; // handles // XXX - HC-MPI COMPAT

typedef struct {
    cncHandle_t guid;
    void *ptr;
} ocrEdtDep_t; // XXX - HC-MPI COMPAT

{% block arch_typedefs -%}
{% endblock arch_typedefs %}
/*************************************\
******** CNC HELPER FUNCTIONS ********
\*************************************/

// Users should not call this function directly,
// but instead use the CNC_SHUTDOWN_ON_FINISH macro.
void cncAutomaticShutdown(cncHandle_t doneEvent);

/*********************************\
******** CNC HELPER MACROS ********
\*********************************/

/* warning for variadic macro support */
#if __GNUC__ < 3 && !defined(__clang__) && __STDC_VERSION__ < 199901L && !defined(NO_VARIADIC_MACROS)
#warning Your compiler might not support variadic macros, in which case the CNC_REQUIRE macro is not supported. You can disable this warning by setting NO_VARIADIC_MACROS to 0, or disable the macro definitions by setting it to 1.
#endif

#if !NO_VARIADIC_MACROS
#define CNC_REQUIRE(cond, ...) do { if (!(cond)) { PRINTF(__VA_ARGS__); exit(-1); } } while (0)
#endif

#define CNC_DESTROY_ITEM(handle) HC_FREE(current_ws(), handle)

static __inline__ void CNC_CREATE_ITEM(cncHandle_t *handle, void **ptr, int ssize) {
    *ptr = hc_malloc(ssize);
    *handle = *ptr;
}

#define CNC_NULL_HANDLE NULL

/* squelch "unused variable" warnings */
#define MAYBE_UNUSED(x) ((void)x)

#define CNC_SHUTDOWN_ON_FINISH(ctx) cncAutomaticShutdown((ctx)->_guids.doneEvent)

#define ASSERT assert

/* helpers for accessing packed argc/argv in ocrMain */
#define OCR_MAIN_ARGC argc
#define OCR_MAIN_ARGV(i) argv[i]

// hc compat
#define PRINTF printf


/*****************************************\
********* CNC COMPATIBILITY MACROS ********
\*****************************************/
{% block arch_compat_macros %}
{% endblock arch_compat_macros %}

{% if logEnabled %}
/**********************************\
********* CNC DEBUG LOGGING ********
\**********************************/
extern FILE *cncDebugLog;
FILE *getCnCDebugLog();

{% endif -%}
#endif /*{{defname}}*/
