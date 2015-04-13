#ifndef _CNCOCR_SMITHWATERMAN_ITEM_INFO_H_
#define _CNCOCR_SMITHWATERMAN_ITEM_INFO_H_

#include "SmithWaterman.h"

#define cncItemSanitizeFn_above NULL
static inline int cncItemSize_above(SmithWatermanCtx *ctx) {
    return sizeof(int) * (ctx->tw+1);
}
#define cncItemSanitizeFn_left NULL
static inline int cncItemSize_left(SmithWatermanCtx *ctx) {
    return sizeof(int) * (ctx->th+1);
}

#endif /*_CNCOCR_SMITHWATERMAN_ITEM_INFO_H_*/
