#include "SmithWaterman.h"

/**
 * Step function defintion for "initAboveStep"
 */
void initAboveStep(cncTag_t tw, cncTag_t ntw, SmithWatermanCtx *ctx) {
    s64 j, jj;
    for (j = 0; j < ntw; j++) {
        int *above = cncCreateItem_above(tw+1);
        for (jj=0; jj <= tw; jj++) {
            // XXX - Why isn't this just 0?
            above[jj] = GAP_PENALTY*(j*tw+jj);
        }
        cncPut_above(above, 0, j, ctx);
    }
}
