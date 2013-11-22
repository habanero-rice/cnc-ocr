
#include "Common.h"
void s3ComputeStep( int k, int j, int i, double** Lkji0, double** Lkji1, double** Lkji2, int tileSize3, Context* context){
	//printf("s3 [%d, %d, %d]\n", k, j, i);
	int ic;
	ocrGuid_t Lkji4_guid;
	double **L_copy;
	ocrDbCreate(&Lkji4_guid, (void **) &L_copy, tileSize3 * sizeof(double*), 0xdead, NULL_GUID, NO_ALLOC);
        for(ic = 0; ic < tileSize3; ic++)
		L_copy[ic] = Lkji0[ic]; //MAJOR HACK!!!
                //L_copy[ic] = (double*) malloc ( tileSize3 * sizeof(double) ); //HACK!!!
	//!!! How can I get the guid for Lkji0 ??? I do not want to have to do copy the data/reallocate.        


	double temp;
        int jB, kB, iB;
        for( jB = 0; jB < tileSize3 ; ++jB ) {
                for( kB = 0; kB < tileSize3 ; ++kB ) {
                        temp = 0 - Lkji2[ jB ][ kB ];
                        if( i != j ){
                                for( iB = 0; iB < tileSize3 ; ++iB )
                                        Lkji0[ iB ][ jB ] += temp * Lkji1[ iB ][ kB ];

                        } else {
                                for( iB = jB; iB < tileSize3; ++iB )
                                        Lkji0[ iB ][ jB ] += temp * Lkji2[ iB ][ kB ];
                        }
                }
        }
        /*for( jB = 0; jB < tileSize3 ; ++jB ) {
                for( kB = 0; kB < tileSize3 ; ++kB ) {
			L_copy[jB][kB] = Lkji0[jB][kB];
		}
	}*/

	char* tagLkji4 = createTag(3, j, i, k+1);
	Put(Lkji4_guid, tagLkji4, context->Lkji);
}


