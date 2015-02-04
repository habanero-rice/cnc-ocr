#include "Cholesky.h"

/*
 */
#pragma hc continuable
void rootComputeStep(CholeskyCtx *ctx) {
    s32 k;
    for(k = 0; k < ctx->numTiles; k++){
        // "cncPrescribeR_*" automatically puts things at root now.
        cncPrescribeR_kComputeStep(k, ctx);
    }
}
