/* Tuning : Row grouping */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <hc.h>

#define TRACE_TOOL 0
#define STATS 0
#define DOWN 0

extern void sequential_cholesky (int k, int tileSize, DDF_t* in_lkji_kkk, DDF_t* out_lkji_kkkp1);
extern void trisolve (int k, int j, int tileSize, DDF_t* in_lkji_jkk, DDF_t* in_lkji_kkkp1, DDF_t* out_lkji_jkkp1);
extern void update_diagonal (int k, int j, int i, int tileSize, DDF_t* in_lkji_jjk, DDF_t* in_lkji_jkkp1, DDF_t* out_lkji_jjkp1);
extern void update_nondiagonal (int k, int j, int i, int tileSize, DDF_t* in_lkji_jik, DDF_t* in_lkji_ikkp1, DDF_t* in_lkji_jkkp1, DDF_t* out_lkji_jikp1);

void compute();
void groupC(void * args);
void groupC_down(void * args);
void groupTU(void * args);
void cholesky_down(void * args);
void cholesky_step(void * args);
void trisolve_step(void * args);
void update_step(void * args);

DDF_t **** lkji; 
int matrixSize;
int tileSize;
int numTiles;

struct timeval initial_time;

typedef struct cholesky_tag {
    int k, j, i;
} cholesky_tag;

cholesky_tag *** tags_TU;

#if STATS
FILE * stat_out;

typedef struct StatTag_t {
    int i, j, k;
    int size;
} StatTag;

typedef struct Stat_t {
    StatTag tag;
    StatTag get[2];
    long start_time, end_time;
    int cpu;
    const char * func;
} Stat_t;
Stat_t *** stats;

const char * str_cholesky;
const char * str_trisolve;
const char * str_update_d;
const char * str_update_nd;
#endif

cholesky_tag * cholesky_tag_create(int k, int j, int i) {
    cholesky_tag * args = (cholesky_tag*)hc_malloc(sizeof(cholesky_tag));
    args->k = k;
    args->j = j;
    args->i = i;
    return args;
}

#pragma hc continuable
int main(int argc, char** argv) {
    int i, j, k, ii;
    double **A, ** temp;
    int A_i, A_j, T_i, T_j;
    FILE *in, *out;
    int i_b, j_b;

    matrixSize = -1;
    tileSize = -1;
    numTiles = -1;

    if ( argc !=  4 ) {
        printf("Usage: ./Cholesky matrixSize tileSize fileName (found %d args)\n", argc);
        return 1;
    }

    matrixSize = atoi(argv[1]);
    tileSize = atoi(argv[2]);
    if ( matrixSize % tileSize != 0) {
        printf("Incorrect tile size %d for the matrix of size %d \n", tileSize, matrixSize);
        return 1;
    }

    numTiles = matrixSize/tileSize;


    lkji = (DDF_t ****) hc_mm_malloc(current_ws(),sizeof(DDF_t***)*numTiles);
    for( i = 0 ; i < numTiles ; ++i ) {
        lkji[i] = (DDF_t***) hc_mm_malloc(current_ws(),sizeof(DDF_t**)*(i+1));;
        for( j = 0 ; j <= i ; ++j ) {
            lkji[i][j] = (DDF_t**) hc_mm_malloc(current_ws(),sizeof(DDF_t*)*(numTiles+1));
            for( k = 0 ; k <= numTiles ; ++k )
                lkji[i][j][k] = DDF_CREATE();
        }
    }

    in = fopen(argv[3], "r");
    if( !in ) {
        printf("Cannot find file: %s\n", argv[3]);
        return 1;
    }
    A = (double**) hc_mm_malloc (current_ws(),sizeof(double*)*matrixSize);
    for( i = 0; i < matrixSize; ++i)
        A[i] = (double*) hc_mm_malloc(current_ws(),sizeof(double)*matrixSize);

    for( i = 0; i < matrixSize; ++i ) {
        for( j = 0; j < matrixSize-1; ++j )
            fscanf(in, "%lf ", &A[i][j]);
        fscanf(in, "%lf\n", &A[i][j]);
    }

    for( i = 0 ; i < numTiles ; ++i ) {
        for( j = 0 ; j <= i ; ++j ) {
            // Allocate memory for the tiles.
            temp = (double**) hc_mm_malloc (current_ws(),sizeof(double*)*tileSize);
            for( ii = 0; ii < tileSize; ++ii )
                temp[ii] = (double*) hc_mm_malloc (current_ws(),sizeof(double)*tileSize);
            // Split the matrix into tiles and write it into the item space at time 0.
            // The tiles are indexed by tile indices (which are tag values).
            for( A_i = i*tileSize, T_i = 0 ; T_i < tileSize; ++A_i, ++T_i ) {
                for( A_j = j*tileSize, T_j = 0 ; T_j < tileSize; ++A_j, ++T_j ) {
                    temp[ T_i ][ T_j ] = A[ A_i ][ A_j ];
                }
            }

            DDF_PUT(lkji[i][j][0], temp);
        }
    }

#if STATS
    str_cholesky = "Cholesky";
    str_trisolve = "Trisolve";
    str_update_d = "Update_D";
    str_update_nd = "Update_ND";

    stats = (Stat_t ***) hc_mm_malloc(current_ws(),sizeof(Stat_t**)*numTiles);
    for( i = 0 ; i < numTiles ; ++i ) {
        stats[i] = (Stat_t**) hc_mm_malloc(current_ws(),sizeof(Stat_t*)*(i+1));;
        for( j = 0 ; j <= i ; ++j ) {
            stats[i][j] = (Stat_t*) hc_mm_malloc(current_ws(),sizeof(Stat_t)*(numTiles+1));
            for( k = 0 ; k < numTiles ; ++k ) {
                stats[i][j][k].tag.i = i;
                stats[i][j][k].tag.j = j;
                stats[i][j][k].tag.k = k;
                stats[i][j][k].tag.size = -1;
                stats[i][j][k].get[0].i = -1;
                stats[i][j][k].get[0].j = -1;
                stats[i][j][k].get[0].k = -1;
                stats[i][j][k].get[0].size = -1;
                stats[i][j][k].get[1] = stats[i][j][k].get[0];
                stats[i][j][k].start_time = -1;
                stats[i][j][k].end_time = -1;
                stats[i][j][k].cpu = -1;
            }
        }
    }

    for ( k = 0; k < numTiles; ++k ) {
        stats[k][k][k].func = str_cholesky;
        for( j = k + 1 ; j < numTiles ; ++j ) {
            stats[j][k][k].func = str_trisolve;
            stats[j][k][k].get[0] = stats[k][k][k+1].tag;
            for( i = k + 1 ; i < j ; ++i ) {
                stats[j][i][k].func = str_update_nd;
                stats[j][i][k].get[0] = stats[j][k][k+1].tag;
                stats[j][i][k].get[1] = stats[i][k][k+1].tag;
            }
            stats[j][j][k].func = str_update_d;
            stats[j][j][k].get[0] = stats[j][k][k+1].tag;
        }
    }

    stat_out = fopen("stat.txt", "w");
#endif

    tags_TU = (cholesky_tag***)hc_malloc(sizeof(cholesky_tag**) * numTiles);
    for ( k = 0; k < numTiles; k++) {
        int numTU = numTiles - (k + 1);
        tags_TU[k] = (cholesky_tag**)hc_malloc(sizeof(cholesky_tag*)*numTU);
        for( j = 0 ; j < numTU ; ++j ) {
            tags_TU[k][j] = cholesky_tag_create(k, j + k + 1, 0);
        }
    }

    struct timeval a;
    struct timeval b;
    gettimeofday(&a, 0);
    initial_time = a;

    compute();

    gettimeofday(&b, 0);
    printf("The computation took %f seconds\r\n",((b.tv_sec - a.tv_sec)*1000000+(b.tv_usec - a.tv_usec))*1.0/1000000);


    //PROBLEM: GC!!!!!
    out = fopen("cholesky.out", "w");
    for ( i = 0; i < numTiles; ++i ) {
        for( i_b = 0; i_b < tileSize; ++i_b) {
            int k = 1;
            for ( j = 0; j <= i; ++j ) {
                temp = (double**) DDF_GET(lkji[i][j][k]);
                if(i != j) {
                    for(j_b = 0; j_b < tileSize; ++j_b) {
                        fprintf( out, "%lf ", temp[i_b][j_b]);
                    }
                } else {
                    for(j_b = 0; j_b <= i_b; ++j_b) {
                        fprintf( out, "%lf ", temp[i_b][j_b]);
                    }
                }
                ++k;
            }
        }
    }

#if STATS
#if TRACE_TOOL
    for ( k = 0; k < numTiles; ++k ) {
        for( j = k ; j < numTiles ; ++j ) {
            for( i = k; i <= j ; ++i ) {
                fprintf(stat_out, "%p get %ld %d\n", lkji[stats[j][i][k].tag.i][stats[j][i][k].tag.j][stats[j][i][k].tag.k], stats[j][i][k].start_time, stats[j][i][k].cpu);
                if (stats[j][i][k].get[0].i >= 0)
                    fprintf(stat_out, "%p get %ld %d\n", lkji[stats[j][i][k].get[0].i][stats[j][i][k].get[0].j][stats[j][i][k].get[0].k], stats[j][i][k].start_time, stats[j][i][k].cpu);
                if (stats[j][i][k].get[1].i >= 0)
                    fprintf(stat_out, "%p get %ld %d\n", lkji[stats[j][i][k].get[1].i][stats[j][i][k].get[1].j][stats[j][i][k].get[1].k], stats[j][i][k].start_time, stats[j][i][k].cpu);
                fprintf(stat_out, "%p put %ld %d\n", lkji[stats[j][i][k].tag.i][stats[j][i][k].tag.j][(stats[j][i][k].tag.k + 1)], stats[j][i][k].end_time, stats[j][i][k].cpu);
            }
        }
    }
#else
    for ( k = 0; k < numTiles; ++k ) {
        for( j = k ; j < numTiles ; ++j ) {
            for( i = k; i <= j ; ++i ) {
                fprintf(stat_out, "%s [%d_%d_%d] get [%d_%d_%d] %ld %d\n", stats[j][i][k].func, stats[j][i][k].tag.i, stats[j][i][k].tag.j, stats[j][i][k].tag.k,  stats[j][i][k].tag.i, stats[j][i][k].tag.j, stats[j][i][k].tag.k, stats[j][i][k].start_time, stats[j][i][k].cpu);
                if (stats[j][i][k].get[0].i >= 0)
                    fprintf(stat_out, "%s [%d_%d_%d] get [%d_%d_%d] %ld %d\n", stats[j][i][k].func, stats[j][i][k].tag.i, stats[j][i][k].tag.j, stats[j][i][k].tag.k, stats[j][i][k].get[0].i, stats[j][i][k].get[0].j, stats[j][i][k].get[0].k, stats[j][i][k].start_time, stats[j][i][k].cpu);
                if (stats[j][i][k].get[1].i >= 0)
                    fprintf(stat_out, "%s [%d_%d_%d] get [%d_%d_%d] %ld %d\n", stats[j][i][k].func, stats[j][i][k].tag.i, stats[j][i][k].tag.j, stats[j][i][k].tag.k, stats[j][i][k].get[1].i, stats[j][i][k].get[1].j, stats[j][i][k].get[1].k, stats[j][i][k].start_time, stats[j][i][k].cpu);
                fprintf(stat_out, "%s [%d_%d_%d] put [%d_%d_%d] %ld %d\n", stats[j][i][k].func, stats[j][i][k].tag.i, stats[j][i][k].tag.j, stats[j][i][k].tag.k, stats[j][i][k].tag.i, stats[j][i][k].tag.j, (stats[j][i][k].tag.k + 1), stats[j][i][k].end_time, stats[j][i][k].cpu);
            }
        }
    }
#endif
#endif

    for( i = 0; i < matrixSize; ++i )
        hc_free(A[i]);
    hc_free(A);
    return 0;
}

#pragma hc continuable
void compute() {
    int k;
    finish {
        for ( k = 0; k < numTiles; ++k ) {
            TUNING_PUT_AT_ROOT(groupC, (long)k);
        }
    }
}

#if DOWN
#pragma hc continuable
void groupC(void * args) {
    TUNING_MOVE_DOWN(groupC_down, args);
}

#pragma hc continuable
void groupC_down(void * args) {
    int k = (int)(long)args;
    TUNING_RELEASE_STEP(cholesky_step, (long)k);
    int numTU = numTiles - (k + 1);
    TUNING_DISTRIBUTE_AMONG_CHILDREN(numTU, groupTU, tags_TU[k]);
}
#else
#pragma hc continuable
void groupC(void * args) {
    int k = (int)(long)args;
    TUNING_RELEASE_STEP(cholesky_step, (long)k);
    int numTU = numTiles - (k + 1);
    TUNING_DISTRIBUTE_AMONG_CHILDREN(numTU, groupTU, tags_TU[k]);
}
#endif

#pragma hc continuable
void groupTU(void * args) {
    /*TUNING_RELEASE_STEP(trisolve_step, args);
    TUNING_RELEASE_STEP(update_step, args);*/
    TUNING_RELEASE_STEP_AT_LEAF(trisolve_step, args);
    TUNING_RELEASE_STEP_AT_LEAF(update_step, args);
}

#pragma hc continuable
void cholesky_step(void * args) {
    int k = (int)(long)args;

    DDF_t *prevPivotTile = lkji[k][k][k];
    DDF_t *currPivotTile = lkji[k][k][k+1];

    async IN(k, tileSize, prevPivotTile, currPivotTile) AWAIT ( prevPivotTile ) {

#if STATS
        stats[k][k][k].cpu = (current_ws())->id;
        struct timeval a;
        gettimeofday(&a, 0);
        stats[k][k][k].start_time = (a.tv_sec - initial_time.tv_sec)*1000000+(a.tv_usec - initial_time.tv_usec);
#endif

        sequential_cholesky (k, tileSize, prevPivotTile, currPivotTile );

#if STATS
        gettimeofday(&a, 0);
        stats[k][k][k].end_time = (a.tv_sec - initial_time.tv_sec)*1000000+(a.tv_usec - initial_time.tv_usec);
#endif
    }
}

#pragma hc continuable
void trisolve_step(void * args) {
    int k = ((cholesky_tag*)args)->k;
    int j = ((cholesky_tag*)args)->j;

    DDF_t *currPivotTile = lkji[k][k][k+1];
    DDF_t *prevPivotColumnTile = lkji[j][k][k];
    DDF_t *currPivotColumnTile = lkji[j][k][k+1];

    async IN(k, j, tileSize, prevPivotColumnTile, currPivotColumnTile, currPivotTile ) AWAIT ( prevPivotColumnTile, currPivotTile ) {
#if STATS
        stats[j][k][k].cpu = (current_ws())->id;
        struct timeval a;
        gettimeofday(&a, 0);
        stats[j][k][k].start_time = (a.tv_sec - initial_time.tv_sec)*1000000+(a.tv_usec - initial_time.tv_usec);
#endif

        trisolve (k, j, tileSize , prevPivotColumnTile, currPivotTile, currPivotColumnTile);

#if STATS
        gettimeofday(&a, 0);
        stats[j][k][k].end_time = (a.tv_sec - initial_time.tv_sec)*1000000+(a.tv_usec - initial_time.tv_usec);
#endif
    }

}

#pragma hc continuable
void update_step(void * args) {
    int k = ((cholesky_tag*)args)->k;
    int j = ((cholesky_tag*)args)->j;
    int i;

    DDF_t *currPivotColumnTile = lkji[j][k][k+1];

    for( i = k + 1 ; i < j ; ++i ) {
        DDF_t *prevTileForUpdate = lkji[j][i][k];
        DDF_t *currTileForUpdate = lkji[j][i][k+1];
        DDF_t *currPivotColumnOtherTile = lkji[i][k][k+1];

        async IN(k,j,i,tileSize,prevTileForUpdate, currPivotColumnOtherTile, currPivotColumnTile, currTileForUpdate ) AWAIT ( prevTileForUpdate, currPivotColumnOtherTile, currPivotColumnTile) {
#if STATS
            stats[j][i][k].cpu = (current_ws())->id;
            struct timeval a;
            gettimeofday(&a, 0);
            stats[j][i][k].start_time = (a.tv_sec - initial_time.tv_sec)*1000000+(a.tv_usec - initial_time.tv_usec);
#endif

            update_nondiagonal ( k, j, i, tileSize, prevTileForUpdate, currPivotColumnOtherTile, currPivotColumnTile, currTileForUpdate);

#if STATS
            gettimeofday(&a, 0);
            stats[j][i][k].end_time = (a.tv_sec - initial_time.tv_sec)*1000000+(a.tv_usec - initial_time.tv_usec);
#endif
        }
    }

    DDF_t *prevDiagonalTileForUpdate = lkji[j][j][k];
    DDF_t *currDiagonalTileForUpdate = lkji[j][j][k+1];

    async IN(k,j,tileSize, prevDiagonalTileForUpdate, currDiagonalTileForUpdate, currPivotColumnTile) AWAIT( prevDiagonalTileForUpdate, currPivotColumnTile) {
#if STATS
        stats[j][j][k].cpu = (current_ws())->id;
        struct timeval a;
        gettimeofday(&a, 0);
        stats[j][j][k].start_time = (a.tv_sec - initial_time.tv_sec)*1000000+(a.tv_usec - initial_time.tv_usec);
#endif

        update_diagonal ( k, j, j, tileSize , prevDiagonalTileForUpdate, currPivotColumnTile, currDiagonalTileForUpdate);

#if STATS
        gettimeofday(&a, 0);
        stats[j][j][k].end_time = (a.tv_sec - initial_time.tv_sec)*1000000+(a.tv_usec - initial_time.tv_usec);
#endif
    }
}

