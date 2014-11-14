#include "Cholesky.h"

/*
 * typeof Lkji is double *
 */
void s3ComputeStep(cncTag_t k, cncTag_t j, cncTag_t i, LkjiItem LkjiA1D, LkjiItem LkjiB1D, LkjiItem LkjiC1D, CholeskyCtx *ctx) {
    int t = ctx->tileSize;
    double (*LkjiA)[t] = (double(*)[t])LkjiA1D.item;
    double (*LkjiB)[t] = (double(*)[t])LkjiB1D.item;
    double (*LkjiC)[t] = (double(*)[t])LkjiC1D.item;

    double temp;
    int jB, kB, iB;
    for (jB = 0; jB < t ; jB++ ) {
        for (kB = 0; kB < t ; kB++) {
            temp = 0 - LkjiC[ jB ][ kB ];
            if (i != j)
                for (iB = 0; iB < t ; iB++)
                    LkjiA[ iB ][ jB ] += temp * LkjiB[ iB ][ kB ];
            else
                for (iB = jB; iB < t; iB++)
                    LkjiA[ iB ][ jB ] += temp * LkjiC[ iB ][ kB ];
        }
    }

    cncPut_Lkji(LkjiA1D.handle, j, i, k+1, ctx);
}
