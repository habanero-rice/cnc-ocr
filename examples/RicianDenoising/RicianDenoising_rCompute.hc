#include "RicianDenoising.h"

/*
 * typeof imageData is void *
 * typeof uData is void *
 */
#pragma hc continuable
void rCompute(cncTag_t iter, cncTag_t i, cncTag_t j, imageDataItem imgData, uDataItem U_last, RicianDenoisingCtx *ctx) {

    int blockSize = ctx->blockSize;
    double sigma2 = ctx->sigma2;

    // allocate space for results
    emxArray_real_T *r = emxCreate_real_T(blockSize, blockSize);

    // call into matlab generated function
    rStep(
      (real_T) blockSize,
      U_last,
      imgData,
      (real_T) sigma2,
      r);

    // store results into item collections
    cncPut_rData(r, iter, i, j, ctx);
}
