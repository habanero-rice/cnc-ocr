{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

{% set defname = "_CNCOCR_INTERNAL_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#include "cncocr.h"

#define CNC_TABLE_SIZE 512 /* TODO - Table size should be set by the user when initializing the item collection */

bool _cncPut(ocrGuid_t item, unsigned char *tag, int tagLength, cncItemCollection_t collection, bool isSingleAssignment);
bool _cncPutSingleton(ocrGuid_t item, ocrGuid_t collection, bool isSingleAssignment);

void _cncGet(unsigned char *tag, int tagLength, ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, cncItemCollection_t collection);
void _cncGetSingleton(ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, ocrGuid_t collection);

#endif /*{{defname}}*/
