#include "Cholesky.h"

/*
 */
void kComputeStep(CholeskyCtx *ctx) {
    int k;
    for(k = 0; k < ctx->numTiles; k++){
        cncPrescribe_kjComputeStep(k, ctx);
        cncPrescribe_s1ComputeStep(k, ctx);
    }
}
