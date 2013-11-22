
#include "Common.h"
void s2ComputeStep( int k, int j, double** Lkji0, double** Lkji1, int tileSize2, Context* context){
	//printf("s2 [%d, %d]\n", k, j);
        int i;
	ocrGuid_t Lkji3_guid;
	double **loBlock;
	ocrDbCreate(&Lkji3_guid, (void **) &loBlock, tileSize2*sizeof(double*), 0xdead, NULL_GUID, NO_ALLOC);
        for(i = 0; i < tileSize2; i++)
                loBlock[i] = (double*) malloc ( tileSize2 * sizeof(double) ); //HACK!!!

        int kB, iB, jB;
        for( kB = 0; kB < tileSize2 ; ++kB ) {
                for( iB = 0; iB < tileSize2 ; ++iB )
                        loBlock[ iB ][ kB ] = Lkji0[ iB ][ kB ] / Lkji1[ kB ][ kB ];

                for( jB = kB + 1 ; jB < tileSize2 ; ++jB )
                        for( iB = 0; iB < tileSize2 ; ++iB )
                                Lkji0[ iB ][ jB ] -= Lkji1[ jB ][ kB ] * loBlock[ iB ][ kB ];

        }

	char* tagLkji3 = createTag(3, j, k, k+1);
	Put(Lkji3_guid, tagLkji3, context->Lkji);
}


