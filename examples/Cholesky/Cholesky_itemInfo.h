#ifndef _CNCOCR_CHOLESKY_ITEM_INFO_H_
#define _CNCOCR_CHOLESKY_ITEM_INFO_H_

#include "Cholesky.h"

#define cncItemSanitizeFn_Lkji NULL
static inline int cncItemSize_Lkji(CholeskyCtx *ctx) {
    return sizeof(double) * ctx->tileSize * ctx->tileSize;
}
#define cncItemSanitizeFn_results NULL
static inline int cncItemSize_results(CholeskyCtx *ctx) {
    return cncItemSize_Lkji(ctx);
}

#endif /*_CNCOCR_CHOLESKY_ITEM_INFO_H_*/
