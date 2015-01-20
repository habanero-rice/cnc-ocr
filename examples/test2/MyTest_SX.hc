#include "MyTest.h"

/*
 */
#pragma hc continuable
void SX(cncTag_t x, MyTestCtx *ctx) {

    //
    // OUTPUTS
    //

    // Put "X" items
    int *X;
    cncHandle_t XHandle = cncCreateItem_X(&X);
    *X = 10;
    cncPut_X(XHandle, 0, ctx);


}
