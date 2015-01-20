#include "SimpleGraph.h"

/*
 */
#pragma hc continuable
void SY(cncTag_t y, SimpleGraphCtx *ctx) {
    printf("IN SY\n");

    //
    // OUTPUTS
    //

    // Put "Y" items
    int *Y;
    cncHandle_t YHandle = cncCreateItem_Y(&Y);
    *Y = y;
    cncPut_Y(YHandle, 0, ctx);


}
