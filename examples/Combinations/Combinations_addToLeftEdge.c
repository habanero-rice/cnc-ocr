#include "Combinations.h"

/*
 */
void addToLeftEdge(cncTag_t row, cncTag_t col, CombinationsCtx *ctx) {

    //
    // OUTPUTS
    //

    // Put "out" items
    u64 *out = cncCreateItem_cells();
    /* TODO: Initialize out */
    *out = 1;
    cncPut_cells(out, row, col, ctx);

    if (row < ctx->n) {
        // Prescribe "addToLeftEdge" steps
        cncPrescribe_addToLeftEdge(row+1, col, ctx);
    }


}
