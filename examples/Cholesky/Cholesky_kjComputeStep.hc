#include "Cholesky.h"

/*
 */
#pragma hc continuable
void kjComputeStep(cncTag_t k, CholeskyCtx *ctx) {
    int j;
    for(j = k+1; j < ctx->numTiles; j++){
        cncPrescribe_kjiComputeStep(k, j, ctx);
        cncPrescribe_s2ComputeStep(k, j, ctx);
    }
}
