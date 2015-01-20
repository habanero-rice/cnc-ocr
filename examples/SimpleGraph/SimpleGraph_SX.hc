#include "SimpleGraph.h"

/*
 */
#pragma hc continuable
void SX(cncTag_t x, SimpleGraphCtx *ctx) {
    printf("IN SX\n");

    //
    // OUTPUTS
    //

    // Put "X" items
    int *X;
    cncHandle_t XHandle = cncCreateItem_X(&X);
    *X = x;
    cncPut_X(XHandle, 0, ctx);


}
