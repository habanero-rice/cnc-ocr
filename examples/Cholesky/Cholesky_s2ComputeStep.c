#include "Cholesky.h"

/*
 * typeof Lkji is double *
 */
void s2ComputeStep(cncTag_t k, cncTag_t j, double *LkjiA1D, double *LkjiB1D, CholeskyCtx *ctx) {
    int t = ctx->tileSize;
    double (*LkjiA)[t] = (double(*)[t])LkjiA1D;
    double (*LkjiB)[t] = (double(*)[t])LkjiB1D;

    // Allocate new tile
    double *loBlock1D = cncCreateItemVector_Lkji(t*t);
    double (*loBlock)[t] = (double(*)[t])loBlock1D;

    int kB, iB, jB;
    for( kB = 0; kB < t ; kB++ ) {
        for( iB = 0; iB < t ; iB++ )
            loBlock[ iB ][ kB ] = LkjiA[ iB ][ kB ] / LkjiB[ kB ][ kB ];

        for( jB = kB + 1 ; jB < t ; jB++ )
            for( iB = 0; iB < t ; iB++ )
                LkjiA[ iB ][ jB ] -= LkjiB[ jB ][ kB ] * loBlock[ iB ][ kB ];
    }

    cncPut_Lkji(loBlock1D, j, k, k+1, ctx);

    int tagResult = (j)*(j+1)/2 + k;
    cncPut_results(loBlock1D, tagResult, ctx);
}
