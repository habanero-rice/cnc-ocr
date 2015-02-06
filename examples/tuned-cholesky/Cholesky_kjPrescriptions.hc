#include "Cholesky.h"

/*
 */
#pragma hc continuable
void kjPrescriptions(cncTag_t k, CholeskyCtx *ctx) {
    int j;
    for(j = k+1; j < ctx->numTiles; j++){
        cncPrescribe_kjiPrescriptions(k, j, ctx);
        cncPrescribe_trisolve(k, j, ctx);
    }
}
