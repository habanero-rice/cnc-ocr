#include "SmithWaterman.h"

/*
 */
#pragma hc continuable
void initAboveStep(cncTag_t tw, cncTag_t ntw, SmithWatermanCtx *ctx) {
    s64 j, jj;
    for (j = 0; j < ntw; j++) {
        int *above;
        cncHandle_t aboveHandle = cncCreateItem_above(&above, tw+1);
        for (jj=0; jj <= tw; jj++) {
            // TODO - Why isn't this just 0?
            above[jj] = GAP_PENALTY*(j*tw+jj);
        }
        cncPut_above(aboveHandle, 0, j, ctx);
    }
}
