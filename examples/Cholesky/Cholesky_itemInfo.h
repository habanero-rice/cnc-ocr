#ifndef _CNCOCR_CHOLESKY_ITEM_INFO_H_
#define _CNCOCR_CHOLESKY_ITEM_INFO_H_

#include "Cholesky.h"

static inline int cncItemSize_Lkji(CholeskyCtx *ctx) {
    return sizeof(double) * ctx->tileSize * ctx->tileSize;
}
static inline int cncItemSize_results(CholeskyCtx *ctx) {
    return cncItemSize_Lkji(ctx);
}

#endif /*_CNCOCR_CHOLESKY_ITEM_INFO_H_*/
