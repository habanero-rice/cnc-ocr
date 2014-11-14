#include "Cholesky.h"

/*
 */
void kjiComputeStep(cncTag_t k, cncTag_t j, CholeskyCtx *ctx) {
    int i;
    for(i = k+1; i < j+1; i++){
        cncPrescribe_s3ComputeStep(k, j, i, ctx);
    }
}
