#ifndef _CNCOCR_RICIANDENOISING_ITEM_INFO_H_
#define _CNCOCR_RICIANDENOISING_ITEM_INFO_H_

#include "RicianDenoising.h"

static inline int cncItemSize_imageData(RicianDenoisingCtx *ctx) {
    return sizeof(void);
}
static inline int cncItemSize_uDiffData(RicianDenoisingCtx *ctx) {
    return sizeof(void);
}
static inline int cncItemSize_gData(RicianDenoisingCtx *ctx) {
    return sizeof(void);
}
static inline int cncItemSize_rData(RicianDenoisingCtx *ctx) {
    return sizeof(void);
}
static inline int cncItemSize_ugData(RicianDenoisingCtx *ctx) {
    return sizeof(void);
}
static inline int cncItemSize_uData(RicianDenoisingCtx *ctx) {
    return sizeof(void);
}
static inline int cncItemSize_doneFlag(RicianDenoisingCtx *ctx) {
    return sizeof(int);
}

#endif /*_CNCOCR_RICIANDENOISING_ITEM_INFO_H_*/
