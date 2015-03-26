#include "Combinations.h"

/*
 * typeof cells is u64 
 */
void addToInside(cncTag_t row, cncTag_t col, u64 a, u64 b, CombinationsCtx *ctx) {

    // Put "out" items
    u64 *out = cncCreateItem_cells();
    *out = a + b;
    cncPut_cells(out, row, col, ctx);

    if (row < ctx->n) {
        // Prescribe "addToInside" steps
        cncPrescribe_addToInside(row+1, col, ctx);
    }


}
