#include "Cholesky.h"

/*
 */
#pragma hc continuable
void kjComputeStep(cncTag_t k, cncTag_t j, CholeskyCtx *ctx) {
    cncTag_t *childTag = malloc(sizeof(cncTag_t*) * 2);
    childTag[0] = k;
    childTag[1] = j;
    TUNING_RELEASE_STEP_AT_LEAF(cncPrescribeT_s2ComputeStep, childTag);
    TUNING_RELEASE_STEP_AT_LEAF(cncPrescribeT_kjiComputeStep, childTag);
}
