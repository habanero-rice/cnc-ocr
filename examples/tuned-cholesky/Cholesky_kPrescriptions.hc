#include "Cholesky.h"

/*
 */
#pragma hc continuable
void kPrescriptions(CholeskyCtx *ctx) {
    int k;
    for(k = 0; k < ctx->numTiles; k++){
        cncPrescribe_kjPrescriptions(k, ctx);
        cncPrescribe_serialCholesky(k, ctx);
    }
}
