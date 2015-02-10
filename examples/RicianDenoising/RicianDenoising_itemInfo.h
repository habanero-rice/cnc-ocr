#ifndef _CNCOCR_RICIANDENOISING_ITEM_INFO_H_
#define _CNCOCR_RICIANDENOISING_ITEM_INFO_H_

#include "RicianDenoising.h"

void *cncItemSanitizeFn_imageData(void *payload);
emxArray_real_T *createImageBlock(int sideDim, RicianDenoisingCtx *ctx);
static inline int cncItemSize_imageData(RicianDenoisingCtx *ctx) {
    size_t matrixSize = sizeof(double) * ctx->blockSize * ctx->blockSize;
    size_t dimSize = sizeof(u32) * 2;
    size_t structSize = sizeof(emxArray_real_T);
    return structSize + matrixSize + dimSize;
}

#define cncItemSanitizeFn_uDiffData cncItemSanitizeFn_imageData
#define cncItemSize_uDiffData cncItemSize_imageData

#define cncItemSanitizeFn_gData cncItemSanitizeFn_imageData
#define cncItemSize_gData cncItemSize_imageData

#define cncItemSanitizeFn_rData cncItemSanitizeFn_imageData
#define cncItemSize_rData cncItemSize_imageData

#define cncItemSanitizeFn_ugData cncItemSanitizeFn_imageData
#define cncItemSize_ugData cncItemSize_imageData

#define cncItemSanitizeFn_uData cncItemSanitizeFn_imageData
#define cncItemSize_uData cncItemSize_imageData

#define cncItemSanitizeFn_doneFlag NULL
static inline int cncItemSize_doneFlag(RicianDenoisingCtx *ctx) {
    return sizeof(int);
}

#endif /*_CNCOCR_RICIANDENOISING_ITEM_INFO_H_*/
