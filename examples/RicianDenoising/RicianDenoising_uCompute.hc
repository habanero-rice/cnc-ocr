#include "RicianDenoising.h"

/*
 * typeof imageData is void *
 * typeof ugData is void *
 * typeof gData is void *
 * typeof rData is void *
 * typeof uData is void *
 */
#pragma hc continuable
void uCompute(cncTag_t iter, cncTag_t i, cncTag_t j, imageDataItem img_ij, ugDataItem ug_cur, ugDataItem ug_top, ugDataItem ug_lef, ugDataItem ug_dow, ugDataItem ug_rig, gDataItem gc, gDataItem gt, gDataItem gl, gDataItem gd, gDataItem gr, rDataItem r_ij, uDataItem u_ij, RicianDenoisingCtx *ctx) {


    int blockSize = ctx->blockSize;
    int tileRows = ctx->numTileRows;
    int tileCols = ctx->numTileCols;
    double gamma = ctx->gamma;

    // handle conditional inputs
    if (!(i > 1)) { ug_top = ug_cur; gt = gc; }
    if (!(j > 1)) { ug_lef = ug_cur; gl = gc; }
    if (!(i < tileRows)) { ug_dow = ug_cur; gd = gc; }
    if (!(j < tileCols)) { ug_rig = ug_cur; gr = gc; }

    // allocate space for results
    emxArray_real_T *u = emxCreate_real_T(blockSize, blockSize);

    uStep(
      (real_T) i,
      (real_T) j,
      (real_T) blockSize,
      (real_T) tileRows,
      (real_T) tileCols,
      ug_cur,
      ug_top,
      ug_rig,
      ug_dow,
      ug_lef,
      gt,
      gr,
      gd,
      gl,
      u_ij,
      img_ij,
      r_ij,
      (real_T) gamma,
      u);

    // store results into item collections
    cncPut_uData(u, iter, i, j, ctx);

    // Put "doneFlag" on last iteration
    if (iter == ctx->iters) {
        int *doneFlag;
        cncHandle_t doneFlagHandle = cncCreateItem_doneFlag(&doneFlag);
        *doneFlag = 1;
        cncPut_doneFlag(doneFlagHandle, (i-1)*tileCols+(j-1), ctx);
    }
}
