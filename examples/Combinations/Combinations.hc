#include "Combinations.h"

#pragma hc continuable
void Combinations_init(CombinationsArgs *args, CombinationsCtx *ctx) {


    if (HCMPI_COMM_RANK == 0) {
        // Put "top" items
        u64 *top;
        cncHandle_t topHandle = cncCreateItem_cells(&top);
        *top = 1;
        cncPut_cells(topHandle, 0, 0, ctx);

        // Prescribe "addToLeftEdge" steps
        cncPrescribe_addToLeftEdge(1, 0, ctx);

        // Prescribe "addToRightEdge" steps
        cncPrescribe_addToRightEdge(1, 1, ctx);
    }

    // Set finalizer function's tag
    Combinations_await(ctx->n, ctx->k, ctx);

}


/*
 * typeof cells is u64 
 */
#pragma hc continuable
void Combinations_finalize(cncTag_t n, cncTag_t k, cellsItem totalChoices, CombinationsCtx *ctx) {
    PRINTF("%d choose %d = %lu\n", ctx->n, ctx->k, totalChoices);
}

