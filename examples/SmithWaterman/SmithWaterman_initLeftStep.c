#include "SmithWaterman.h"

/**
 * Step function defintion for "initLeftStep"
 */
void initLeftStep(cncTag_t th, cncTag_t nth, SmithWatermanCtx *ctx) {
    s64 i, ii;
    for (i = 0; i < nth; i++) {
        int *left = cncCreateItem_left(th+1);
        for (ii=0; ii <= th; ii++) {
            // XXX - Why isn't this just 0?
            left[ii] = GAP_PENALTY*(i*th+ii);
        }
        cncPut_left(left, i, 0, ctx);
    }
}
