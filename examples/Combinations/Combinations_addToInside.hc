#include "Combinations.h"

/*
 * typeof cells is u64 
 */
#pragma hc continuable
void addToInside(cncTag_t row, cncTag_t col, cellsItem a, cellsItem b, CombinationsCtx *ctx) {

    //
    // OUTPUTS
    //

    // Put "cells" items
    u64 *cells;
    cncHandle_t cellsHandle = cncCreateItem_cells(&cells);
    *cells = a + b;
    cncPut_cells(cellsHandle, row, col, ctx);

    if (row < ctx->n) {
        // Prescribe "addToInside" steps
        cncPrescribe_addToInside(row+1, col, ctx);
    }
}
