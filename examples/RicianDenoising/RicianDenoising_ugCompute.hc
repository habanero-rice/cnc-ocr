#include "RicianDenoising.h"
#include "RicianDenoising_itemInfo.h"

/*
 * typeof gData is void *
 * typeof uData is void *
 */
#pragma hc continuable
void ugCompute(cncTag_t iter, cncTag_t i, cncTag_t j, gDataItem gData, uDataItem U_last, RicianDenoisingCtx *ctx) {

    int blockSize = ctx->blockSize;
    double sigma2 = ctx->sigma2;

    // allocate space for results
    emxArray_real_T *ug = createImageBlock(blockSize, ctx);

    // call into matlab generated function
    ugStep(
      (real_T) blockSize,
      U_last,
      gData,
      ug);

    // store results into item collections
    cncPut_ugData(ug, iter, i, j, ctx);

}
