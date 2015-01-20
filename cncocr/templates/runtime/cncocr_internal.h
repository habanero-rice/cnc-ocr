{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

{% set defname = "_CNCOCR_INTERNAL_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#include "cncocr.h"

#if CNCOCR_x86
extern void *memcpy(void *dest, const void *src, size_t n);
#    ifndef HAL_X86_64
#    define hal_memCopy(dest, src, len, bg) memcpy(dest, src, len)
#    define hal_fence() __sync_synchronize()
#    endif
#elif CNCOCR_TG
// some HAL definitions (apps/lib/tg/include)
#    include "misc.h" 
#else
#    warning UNKNOWN PLATFORM (possibly unsupported)
#endif

#define CNC_TABLE_SIZE 512 /* TODO - Table size should be set by the user when initializing the item collection */

bool _cncPut(void *item, unsigned char *tag, int tagLength, cncItemCollection_t collection, bool isSingleAssignment);

DDF_t *_cncGet(unsigned char *tag, int tagLength, cncItemCollection_t collection);

ocrEdtDep_t _cncRangedInputAlloc(u32 n, u32 dims[], size_t itemSize);

#endif /*{{defname}}*/
