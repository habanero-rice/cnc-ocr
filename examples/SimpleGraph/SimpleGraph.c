#include "SimpleGraph.h"

void SimpleGraph_init(SimpleGraphArgs *args, SimpleGraphCtx *ctx) {

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
void SimpleGraph_finalize(int X, int Y, SimpleGraphCtx *ctx) {
    // Print results
    PRINTF("X = %d\n", X);
    PRINTF("Y = %d\n", Y);
}
