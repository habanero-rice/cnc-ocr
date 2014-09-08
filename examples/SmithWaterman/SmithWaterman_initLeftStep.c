#include "SmithWaterman.h"

/*
 */
void initLeftStep(cncTag_t th, cncTag_t nth, SmithWatermanCtx *ctx) {
    s64 i, ii;
    for (i = 0; i < nth; i++) {
        int *left;
        cncHandle_t leftHandle = cncCreateItem_left(&left, th+1);
        for (ii=0; ii <= th; ii++) {
            // TODO - Why isn't this just 0?
            left[ii] = GAP_PENALTY*(i*th+ii);
        }
        cncPut_left(leftHandle, i, 0, ctx);
    }
}
