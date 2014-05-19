
#include "Common.h"
void s2ComputeStep(int k, int j, tileSizeItem tileSize, LkjiItem LkjiA1D, LkjiItem LkjiB1D, Context *context) {
    int t = tileSize.item;
    double (*LkjiA)[t] = (double(*)[t])LkjiA1D.item;
    double (*LkjiB)[t] = (double(*)[t])LkjiB1D.item;

    // Allocate new tile
    double *loBlock1D;
    cncHandle_t loBlock_handle = cncCreateItem_Lkji(&loBlock1D, t*t);
    double (*loBlock)[t] = (double(*)[t])loBlock1D;

    int kB, iB, jB;
    for( kB = 0; kB < t ; kB++ ) {
        for( iB = 0; iB < t ; iB++ )
            loBlock[ iB ][ kB ] = LkjiA[ iB ][ kB ] / LkjiB[ kB ][ kB ];

        for( jB = kB + 1 ; jB < t ; jB++ )
            for( iB = 0; iB < t ; iB++ )
                LkjiA[ iB ][ jB ] -= LkjiB[ jB ][ kB ] * loBlock[ iB ][ kB ];
    }

    cncPut_Lkji(loBlock_handle, j, k, k+1, context);

    int tagResult = (j)*(j+1)/2 + k;
    cncPut_results(loBlock_handle, tagResult, context);
}

