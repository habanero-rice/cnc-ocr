#include "Cholesky.h"
#include <sys/time.h>

struct timeval startTime;

#pragma hc continuable
void Cholesky_init(CholeskyArgs *args, CholeskyCtx *ctx) {
    int nt = ctx->numTiles;
    int t = ctx->tileSize;
    int n = nt * t;
    int matrixElementCount = n * n;

    // Open input matrix file
    FILE *f = fopen(args->inFile, "r");
    CNC_REQUIRE(f != NULL, "Cannot find file: %s\n", args->inFile);

    {
        int i, j;
        // Allocate memory for reading the whole temporary matrix
        double *A1D = hc_malloc(matrixElementCount * sizeof(double)) ;

        // Read the matrix
        for (i=0; i<matrixElementCount; i++) {
            fscanf(f, "%lf", &A1D[i]);
        }
        fclose(f);

        // The 1D array of matrix entries maps to a
        // 2D array corresponding to an n-by-n matrix
        double (*A)[n] = (void*)A1D;

        // Create tiles from source matrix
        for (i = 0; i < nt; i++){
            for (j = 0 ; j <= i ; j++ ) {
                int A_i, A_j, T_i, T_j;
                double *temp1D;
                cncHandle_t tile_handle = cncCreateItem_Lkji(&temp1D, t*t);
                // The 1D array of tile entries maps to a
                // 2D array corresponding to a t-by-t matrix tile
                double (*temp)[t] = (double(*)[t])temp1D;
                // Copy this tile's data from the input matrix
                for (A_i = i * t, T_i = 0 ; T_i < t ; A_i++, T_i++) {
                    for (A_j = j * t, T_j = 0 ; T_j < t ; A_j++, T_j++) {
                        temp[ T_i ][ T_j ] = A[ A_i ][ A_j ];
                    }
                }
                // Put the initialized tile
                cncPut_Lkji(tile_handle, i, j, 0, ctx);
            }
        }
        // Free temporary matrix (no longer needed)
        hc_free(A1D);
    }

    // Record starting time
#if CNCOCR_x86
    gettimeofday(&startTime, 0);
#endif

    // Prescribe "kComputeStep" steps
    cncPrescribe_kComputeStep(ctx);

    // Set finalizer function's tag
    int tileCount = ctx->numTiles * (ctx->numTiles + 1) / 2;
    Cholesky_await(tileCount, ctx);
}


/*
 * typeof startTime is struct timeval *
 * typeof results is double *
 */
#pragma hc continuable
void Cholesky_finalize(cncTag_t tileCount, resultsItem *results, CholeskyCtx *ctx) {
#if CNCOCR_x86
    // Report the total running time
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double secondsRun = endTime.tv_sec - startTime.tv_sec;
    secondsRun += (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    PRINTF("The computation took %f seconds\n", secondsRun);
#endif
    // Print the result matrix row-by-row (requires visiting each tile t times)
    int nt = ctx->numTiles;
    int t = ctx->tileSize;
    FILE *f = fopen("Cholesky.out", "w");
    int tileRow, tileCol, entryRow, entryCol;
    int tileIndexRowBase = 0;
    for (tileRow = 0; tileRow < nt; tileRow++) {
        for (entryRow = 0; entryRow < t; entryRow++) {
            for (tileCol = 0; tileCol <= tileRow; tileCol++) {
                int tileIndex = tileIndexRowBase + tileCol;
                // the item is actually an array of dim t-by-t
                double (*local_tile)[t] = (double(*)[t])results[tileIndex];
                // check for tiles on the diagonal (which are half empty)
                int bound = (tileRow == tileCol) ? entryRow+1 : t;
                // print current row of current tile
                for (entryCol = 0; entryCol < bound; entryCol++) {
                    fprintf(f, "%lf ", local_tile[entryRow][entryCol]);
                }
            }
        }
        // Increment by the number of tiles in this row
        tileIndexRowBase += tileRow + 1;
    }
    fclose(f);
}

