#include "MyTest.h"

#pragma hc continuable
void MyTest_init(MyTestArgs *args, MyTestCtx *ctx) {
    int *Y;
    cncHandle_t YHandle = cncCreateItem_Y(&Y);
    *Y = 500;
    cncPut_Y(YHandle, 1, ctx);

    // Prescribe "SX" steps
    cncPrescribe_SX(1, ctx);

    // Prescribe "SY" steps
    cncPrescribe_SY(2, ctx);

    // Set finalizer function's tag
    MyTest_await(ctx);
}


/*
 * typeof X is int 
 * typeof Y is int 
 */
#pragma hc continuable
void MyTest_finalize(XItem X, YItem Y, MyTestCtx *ctx) {


    fprintf(stderr, "\n\nX = %d, Y = %d\n\n", X, Y);
    /* TODO: Do something with X.item */

    /* TODO: Do something with Y.item */

}

