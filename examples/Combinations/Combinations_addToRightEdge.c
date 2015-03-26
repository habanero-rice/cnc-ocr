#include "Combinations.h"

/*
 */
void addToRightEdge(cncTag_t row, cncTag_t col, CombinationsCtx *ctx) {

    // Put "out" items
    u64 *out = cncCreateItem_cells();
    *out = 1;
    cncPut_cells(out, row, col, ctx);

    if (row < ctx->n) {
        // Prescribe "addToInside" steps
        cncPrescribe_addToInside(row+1, col, ctx);

        // Prescribe "addToRightEdge" steps
        cncPrescribe_addToRightEdge(row+1, col+1, ctx);
    }

}
