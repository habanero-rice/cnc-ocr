#include "Combinations.h"


void Combinations_init(CombinationsArgs *args, CombinationsCtx *ctx) {

    // Put "out" items
    u64 *out = cncCreateItem_cells();
    *out = 1;
    cncPut_cells(out, 0, 0, ctx);

    // Prescribe "addToLeftEdge" steps
    cncPrescribe_addToLeftEdge(1, 0, ctx);

    // Prescribe "addToRightEdge" steps
    cncPrescribe_addToRightEdge(1, 1, ctx);

    // Set finalizer function's tag
    Combinations_await(ctx);

}


/*
 * typeof cells is u64 
 */
void Combinations_finalize(u64 totalChoices, CombinationsCtx *ctx) {
    // Print final result
    PRINTF("%u choose %u = %lu\n", ctx->n, ctx->k, totalChoices);
}

