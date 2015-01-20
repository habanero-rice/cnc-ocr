#include "Combinations.h"

/*
 */
#pragma hc continuable
void addToLeftEdge(cncTag_t row, cncTag_t col, CombinationsCtx *ctx) {

    //
    // OUTPUTS
    //

    // Put "cells" items
    u64 *cells;
    cncHandle_t cellsHandle = cncCreateItem_cells(&cells);
    *cells = 1;
    cncPut_cells(cellsHandle, row, col, ctx);

    if (row < ctx->n) {
        // Prescribe "addToLeftEdge" steps
        cncPrescribe_addToLeftEdge(row+1, col, ctx);
    }
}
