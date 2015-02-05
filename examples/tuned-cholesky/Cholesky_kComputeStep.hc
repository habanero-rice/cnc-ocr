#include "Cholesky.h"

/*
 */
#pragma hc continuable
void kComputeStep(cncTag_t k, CholeskyCtx *ctx) {
    cncTag_t *kp = malloc(sizeof(k));
    *kp = k;
    TUNING_RELEASE_STEP(cncPrescribeT_s1ComputeStep, kp);
    int j;
    int numTU = ctx->numTiles - (k + 1);
#if ROW_GROUPS
    for (j=0; j<numTU; j++) {
        cncPrescribeR_kjComputeStep(k, j+k+1, ctx);
    }
#else
    cncTag_t **childTags = malloc(sizeof(cncTag_t*) * numTU);
    for (j=0; j<numTU; j++) {
        childTags[j] = malloc(sizeof(cncTag_t)*2);
        childTags[j][0] = k;
        childTags[j][1] = j+k+1;
    }
    //fprintf(stderr, "k=%d, n=%d\n", k, numTU);
    TUNING_DISTRIBUTE_AMONG_CHILDREN(numTU, cncPrescribeT_kjComputeStep, childTags);
#endif
}
