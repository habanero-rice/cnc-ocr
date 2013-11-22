
#include "Common.h"
#include <math.h> 

void s1ComputeStep( int k, double** Lkji0, int tileSize1, Context* context){
	//printf("s1 [%d]\n", k);
        int i;
	ocrGuid_t Lkji2_guid;
        double ** lBlock;
	ocrDbCreate(&Lkji2_guid, (void **) &lBlock, tileSize1*sizeof(double*), 0xdead, NULL_GUID, NO_ALLOC);
        for(i = 0; i < tileSize1; i++)
                lBlock[i] = (double*) malloc ( (i+1) * sizeof(double) ); //HACK!!!

        int kB, jB, jBB, iB;
        for( kB = 0 ; kB < tileSize1 ; ++kB ) {
                if( Lkji0[ kB ][ kB ] <= 0 )
                        { printf("[%d] [%d]Error: Not a symmetric positive definite (SPD) matrix\n", -1, k); fflush(NULL);
                          exit(1);
                        }

                lBlock[ kB ][ kB ] = sqrt( Lkji0[ kB ][ kB ] );

                for( jB = kB + 1; jB < tileSize1 ; ++jB )
                        lBlock[ jB ][ kB ] = Lkji0[ jB ][ kB ] / lBlock[ kB ][ kB ];

                for( jBB= kB + 1; jBB < tileSize1 ; ++jBB )
                        for( iB = jBB ; iB < tileSize1 ; ++iB )
                                Lkji0[ iB ][ jBB ] = Lkji0[ iB ][ jBB ] - ( lBlock[ iB ][ kB ] * lBlock[ jBB ][ kB ] );
        }

	char* tagLkji2 = createTag(3, k, k, k+1);
	Put(Lkji2_guid, tagLkji2, context->Lkji);
}


