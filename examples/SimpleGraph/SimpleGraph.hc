#include "SimpleGraph.h"

void SimpleGraph_init(SimpleGraphArgs *args, SimpleGraphCtx *ctx) {
    printf("IN init\n");

    // Prescribe "SX" steps
    cncPrescribe_SX(1, ctx);

    // Prescribe "SY" steps
    cncPrescribe_SY(2, ctx);

    // Set finalizer function's tag
    SimpleGraph_await(ctx);

}

/*
 * typeof X is int 
 * typeof Y is int 
 */
#pragma hc continuable
void SimpleGraph_finalize(XItem X, YItem Y, SimpleGraphCtx *ctx) {
    printf("IN finalize\n");
    // Print results
    printf("X = %d\n", X);
    printf("Y = %d\n", Y);
}
