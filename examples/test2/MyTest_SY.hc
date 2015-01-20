#include "MyTest.h"

/*
 */
#pragma hc continuable
void SY(cncTag_t y, MyTestCtx *ctx) {

    //
    // OUTPUTS
    //

    // Put "Y" items
    int *Y;
    cncHandle_t YHandle = cncCreateItem_Y(&Y);
    *Y = 200;
    cncPut_Y(YHandle, 0, ctx);


}
