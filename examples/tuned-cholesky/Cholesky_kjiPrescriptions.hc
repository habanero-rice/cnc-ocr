#include "Cholesky.h"

/*
 */
#pragma hc continuable
void kjiPrescriptions(cncTag_t k, cncTag_t j, CholeskyCtx *ctx) {
    int i;
    for(i = k+1; i < j+1; i++){
        cncPrescribe_update(k, j, i, ctx);
    }
}
