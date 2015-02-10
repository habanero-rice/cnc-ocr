#include "RicianDenoising.h"
#include "RicianDenoising_itemInfo.h"

/*
 * typeof uData is void *
 * typeof uDiffData is void *
 */
#pragma hc continuable
void gCompute(cncTag_t iter, cncTag_t i, cncTag_t j, uDataItem U_last, uDiffDataItem U_top, uDiffDataItem U_rig, uDiffDataItem U_bot, uDiffDataItem U_lef, RicianDenoisingCtx *ctx) {

    int blockSize = ctx->blockSize;

    // allocate space for result
    emxArray_real_T *g = createImageBlock(blockSize, ctx);

    // call into matlab generated function
    gStep(
      (real_T) blockSize,
      U_last,
      U_top,
      U_rig,
      U_bot,
      U_lef,
      g);

    // store results into item collections
    cncPut_gData(g, iter, i, j, ctx);

}
