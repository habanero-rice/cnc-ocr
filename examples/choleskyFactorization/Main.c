#include "Context.h"

void cncEnvIn(int argc, char **argv, Context *context) {
    CNC_REQUIRE(argc==4, "Usage: ./Cholesky matrixSize tileSize fileName (found %d args)\n", argc);

    // Parse matrix dim info
    int n, t, nt;
    n = atoi(argv[1]);
    t = atoi(argv[2]);
    nt = n/t;
    CNC_REQUIRE(n % t == 0, "Incompatible tile size %d for the matrix of size %d\n", t, n);

    // Read source matrix
    FILE *f = fopen(argv[3], "r");
    CNC_REQUIRE(f != NULL, "Cannot find file: %s\n", argv[3]);
    int i, j;
    int matrixElementCount = n * n;
    double *A1D = MALLOC(matrixElementCount * sizeof(double)) ;
    for (i=0; i<matrixElementCount; i++) {
        fscanf(f, "%lf", &A1D[i]);
    }

    // The 1D array of matrix entries maps to a
    // 2D array corresponding to an n-by-n matrix
    double (*A)[n] = (double(*)[n])A1D;

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
            cncPut_Lkji(tile_handle, i, j, 0, context);
        }
    }
    // Clean up source matrix (no longer needed)
    FREE(A1D);
    
    // Put matrix and tile dimension info
    int *ntPtr, *tPtr;
    cncHandle_t nt_handle = cncCreateItem_tileSize(&ntPtr);
    *ntPtr = nt;
    cncPut_numTiles(nt_handle, 0, context);
    cncHandle_t t_handle = cncCreateItem_numTiles(&tPtr);
    *tPtr = t;
    cncPut_tileSize(t_handle, 0, context);

    // Record the starting time of the computation
    struct timeval *startTime;
    cncHandle_t time_handle = cncCreateItem_startTime(&startTime, 1);
    gettimeofday(startTime, 0);
    cncPut_startTime(time_handle, 0, context);

    // Start the computation
    cncPrescribe_kComputeStep(0, context);

    // Set tag for the output step
    int totalTileCount = nt * (nt + 1) / 2;
    cncPrescribe_cncEnvOut(totalTileCount, context);
}

void cncEnvOut(int tileCount, startTimeItem startTime, numTilesItem numTiles, tileSizeItem tileSize,
        resultsItem *results, Context *context) {
    // Report the total running time
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double secondsRun = endTime.tv_sec - startTime.item->tv_sec;
    secondsRun += (endTime.tv_usec - startTime.item->tv_usec) / 1000000.0;
    PRINTF("The computation took Q%fQ seconds\n", secondsRun);
    // Print the result matrix row-by-row (requires visiting each tile t times)
    int nt = numTiles.item;
    int t = tileSize.item;
    FILE *ff = fopen("Cholesky.out", "w");
    int tileRow, tileCol, entryRow, entryCol;
    int tileIndexRowBase = 0;
    for (tileRow = 0; tileRow < nt; tileRow++) {
        for (entryRow = 0; entryRow < t; entryRow++) {
            for (tileCol = 0; tileCol <= tileRow; tileCol++) {
                int tileIndex = tileIndexRowBase + tileCol;
                // the item is actually an array of dim t-by-t
                double (*local_tile)[t] = (double(*)[t])results[tileIndex].item;
                // check for tiles on the diagonal (which are half empty)
                int bound = (tileRow == tileCol) ? entryRow+1 : t;
                // print current row of current tile
                for (entryCol = 0; entryCol < bound; entryCol++) {
                    fprintf(ff, "%lf ", local_tile[entryRow][entryCol]);
                }
            }
        }
        // Increment by the number of tiles in this row
        tileIndexRowBase += tileRow + 1;
    }
    fclose(ff);
}
