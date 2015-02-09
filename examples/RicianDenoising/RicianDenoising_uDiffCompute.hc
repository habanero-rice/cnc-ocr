#include "RicianDenoising.h"

/*
 * typeof uData is void *
 */
#pragma hc continuable
void uDiffCompute(cncTag_t iter, cncTag_t i, cncTag_t j, uDataItem U_cen, uDataItem U_top, uDataItem U_lef, uDataItem U_bot, uDataItem U_rig, RicianDenoisingCtx *ctx) {

    int blockSize = ctx->blockSize;
    int tileRows = ctx->numTileRows;
    int tileCols = ctx->numTileCols;

    // handle conditional inputs
    if (!(i > 1)) { U_top = U_cen; }
    if (!(j > 1)) { U_lef = U_cen; }
    if (!(i < tileRows)) { U_bot = U_cen; }
    if (!(j < tileCols)) { U_rig = U_cen; }

    //
    // OUTPUTS
    //

    // allocate space for results
    emxArray_real_T *ut = emxCreate_real_T(blockSize, blockSize);
    emxArray_real_T *ur = emxCreate_real_T(blockSize, blockSize);
    emxArray_real_T *ud = emxCreate_real_T(blockSize, blockSize);
    emxArray_real_T *ul = emxCreate_real_T(blockSize, blockSize);

#if 0
    fprintf(stderr, "iter=%d, i=%d, j=%d\nbsz=%d, r=%d, c=%d\n",
      iter, i, j, blockSize, tileRows, tileCols);
    fprintf(stderr, "u = %p\nut = %p %p\nur = %p %p\nud = %p %p\nul = %p %p\n",
      U_cen, U_top, ut, U_rig, ur, U_bot, ud, U_lef, ul);
#endif

    // call into matlab generated function
    uDiffStep(
        (real_T) i,
        (real_T) j,
        (real_T) blockSize,
        (real_T) tileRows,
        (real_T) tileCols,
        U_cen,
        U_top,
        U_rig,
        U_bot,
        U_lef,
        ut,
        ur,
        ud,
        ul
    );

    // Put outputs
    cncPut_uDiffData(ut, iter, TAG_TOP, i, j, ctx);
    cncPut_uDiffData(ur, iter, TAG_RIG, i, j, ctx);
    cncPut_uDiffData(ud, iter, TAG_BOT, i, j, ctx);
    cncPut_uDiffData(ul, iter, TAG_LEF, i, j, ctx);

}
