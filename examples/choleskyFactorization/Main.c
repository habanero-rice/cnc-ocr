
   /***** AUTO-GENERATED FILE from file Cholesky.cnc - only generated if file does not exist (on running cncocr_t the first time) - feel free to edit *****/

#include "Dispatch.h"

void cncEnvIn(int argc, char **argv, Context *context) {
    CNC_REQUIRE(argc==4, "Usage: ./Cholesky matrixSize tileSize fileName (found %d args)\n", argc);

    // Parse matrix dim info
    int n, t, nt;
    n = atoi(argv[1]);
    t = atoi(argv[2]);
    nt = n/t;
    CNC_REQUIRE(n % t == 0, "Incorrect tile size %d for the matrix of size %d\n", t, n);

    // Read source matrix
    FILE *f = fopen(argv[3], "r");
    CNC_REQUIRE(f != NULL, "Cannot find file: %s\n", argv[3]);
    int i, j;
    int matrixElementCount = n * n;
    double *A1D = MALLOC(matrixElementCount * sizeof(double)) ;
    double (*A)[n] = (double(*)[n])A1D;
    for (i=0; i<matrixElementCount; i++) {
        fscanf(f, "%lf", &A1D[i]);
    }

    // Create tiles from source matrix
    for (i = 0; i < nt; i++){
        for (j = 0 ; j <= i ; j++ ) {
            int A_i, A_j, T_i, T_j;
            double *temp1D;
            cncHandle_t tile_handle = cncCreateItem_Lkji(&temp1D, t*t);
            double (*temp)[t] = (double(*)[t])temp1D;
            for (A_i = i * t, T_i = 0 ; T_i < t ; A_i++, T_i++) {
                for (A_j = j * t, T_j = 0 ; T_j < t ; A_j++, T_j++) {
                    temp[ T_i ][ T_j ] = A[ A_i ][ A_j ];
                }
            }
            char * tempTag = CREATE_TAG(i, j, 0);
            Put(tile_handle, tempTag, context->Lkji);
        }
    }
    // Deallocate source matrix
    FREE(A1D);
    
    // Put matrix dim info
    char *tag = CREATE_TAG(0);
    int *ntPtr, *tPtr;
    cncHandle_t nt_handle = cncCreateItem_tileSize(&ntPtr);
    *ntPtr = nt;
    Put(nt_handle, tag, context->numTiles);
    cncHandle_t t_handle = cncCreateItem_numTiles(&tPtr);
    *tPtr = t;
    Put(t_handle, tag, context->tileSize);

    // Record starting time
    struct timeval *startTime;
    cncHandle_t time_handle = cncCreateItem_startTime(&startTime, 1);
    gettimeofday(startTime, 0);
    Put(time_handle, tag, context->startTime);

    // Start computation
    prescribeStep("kComputeStep", tag, context);

    // Set tag for output step
    int totalTileCount = nt * (nt + 1) / 2;
    char *envOutTag = CREATE_TAG(totalTileCount);
    setEnvOutTag(envOutTag, context);
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
                // the item is actually a  array of dim t-by-t
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
