
#include "Common.h"

void s1ComputeStep(int k, tileSizeItem tileSize, LkjiItem Lkji1D, Context *context){
    int t = tileSize.item;
    double (*Lkji)[t] = (double(*)[t])Lkji1D.item;

    // Allocate new tile
    double *lBlock1D;
    cncHandle_t lBlock_handle = cncCreateItem_Lkji(&lBlock1D, t*t);
    double (*lBlock)[t] = (double(*)[t])lBlock1D;

    // Calculate tile values
    int kB, jB, jBB, iB;
    for (kB = 0 ; kB < t ; kB++) {
        CNC_REQUIRE(Lkji[ kB ][ kB ] > 0.0,
                    "[%d,%d][%d,%d] Error: Not a symmetric positive definite (SPD) matrix (%f) t=%d\n",
                    k, k, kB, kB, Lkji1D.item[ kB*t + kB ], t);
        lBlock[ kB ][ kB ] = sqrt( Lkji[ kB ][ kB ] );

        for (jB = kB + 1; jB < t ; jB++)
            lBlock[ jB ][ kB ] = Lkji[ jB ][ kB ] / lBlock[ kB ][ kB ];

        for (jBB= kB + 1; jBB < t ; jBB++)
            for (iB = jBB ; iB < t ; iB++)
                Lkji[ iB ][ jBB ] = Lkji[ iB ][ jBB ] - ( lBlock[ iB ][ kB ] * lBlock[ jBB ][ kB ] );
    }

    char *tagLkji = CREATE_TAG(k, k, k+1);
    Put(lBlock_handle, tagLkji, context->Lkji);

    char *tagResult = CREATE_TAG((k)*(k+1)/2 + k);
    Put(lBlock_handle, tagResult, context->results);
}

