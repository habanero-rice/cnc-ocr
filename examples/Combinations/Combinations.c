#include "Combinations.h"

void Combinations_init(CombinationsArgs *args, CombinationsCtx *ctx) {


    // Put "top" items
    u64 *top;
    cncHandle_t topHandle = cncCreateItem_cells(&top);
    *top = 1;
    cncPut_cells(topHandle, 0, 0, ctx);

    // Prescribe "addToLeftEdge" steps
    cncPrescribe_addToLeftEdge(1, 0, ctx);

    // Prescribe "addToRightEdge" steps
    cncPrescribe_addToRightEdge(1, 1, ctx);

    // Set finalizer function's tag
    Combinations_await(ctx->n, ctx->k, ctx);

}


/*
 * typeof cells is u64 
 */
void Combinations_finalize(cncTag_t n, cncTag_t k, cellsItem totalChoices, CombinationsCtx *ctx) {
    PRINTF("%lu choose %lu = %lu\n", n, k, totalChoices.item);
}

