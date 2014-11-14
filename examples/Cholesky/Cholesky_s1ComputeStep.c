#include "Cholesky.h"
#include <math.h>

/*
 * typeof Lkji is double *
 */
void s1ComputeStep(cncTag_t k, LkjiItem Lkji1D, CholeskyCtx *ctx) {

    int t = ctx->tileSize;
    double (*Lkji)[t] = (double(*)[t])Lkji1D.item;

    // Allocate new tile
    double *lBlock1D;
    cncHandle_t lBlock_handle = cncCreateItem_Lkji(&lBlock1D, t*t);
    double (*lBlock)[t] = (double(*)[t])lBlock1D;

    // Calculate tile values
    int kB, jB, jBB, iB;
    for (kB = 0 ; kB < t ; kB++) {
        CNC_REQUIRE(Lkji[ kB ][ kB ] > 0.0,
                    "[%d][%d] Error: Not a symmetric positive definite (SPD) matrix\n", k, kB);
        lBlock[ kB ][ kB ] = sqrt( Lkji[ kB ][ kB ] );

        for (jB = kB + 1; jB < t ; jB++)
            lBlock[ jB ][ kB ] = Lkji[ jB ][ kB ] / lBlock[ kB ][ kB ];

        for (jBB= kB + 1; jBB < t ; jBB++)
            for (iB = jBB ; iB < t ; iB++)
                Lkji[ iB ][ jBB ] = Lkji[ iB ][ jBB ] - ( lBlock[ iB ][ kB ] * lBlock[ jBB ][ kB ] );
    }

    cncPut_Lkji(lBlock_handle, k, k, k+1, ctx);

    int tagResult = (k)*(k+1)/2 + k;
    cncPut_results(lBlock_handle, tagResult, ctx);

}
