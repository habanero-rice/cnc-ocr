#include "SmithWaterman.h"
#include <stdlib.h>

static inline int max_score(int x, int y) {
    return (x > y) ? x : y;
}

/**
 * Step function defintion for "swStep"
 */
void swStep(cncTag_t i, cncTag_t j, SeqData *data, int *above, int *left, SmithWatermanCtx *ctx) {
    int index, ii, jj;
    ASSERT(above[0] == left[0] && "Diagonal values should match");

    /* Allocate a haloed local matrix for calculating 'this' tile*/
    /* 2D-ify it for readability */
    size_t entryCount = (1+data->tw)*(1+data->th);
    int (*curr_tile)[data->tw+1] = malloc(sizeof(int)*entryCount);

    /* Set local_tile[i+1][0] (left column) from the right column of the left tile */
    for (index = 0; index <= data->th; index++) {
        curr_tile[index][0] = left[index];
    }

    /* Set local_tile[0][j+1] (top row) from the bottom row of the above tile */
    for (index = 0; index <= data->tw; ++index) {
        curr_tile[0][index] = above[index];
    }

    /* Run a smith-waterman on the local tile */
    for (ii = 1; ii <= data->th; ii++) {
        for (jj = 1; jj <= data->tw; jj++) {
            int char_from_1 = TSEQ1(data)[j][jj-1];
            int char_from_2 = TSEQ2(data)[i][ii-1];

            /* Get score from northwest, north and west */
            int diag_score = curr_tile[ii-1][jj-1] + data->score_matrix[char_from_2][char_from_1];
            int left_score = curr_tile[ii  ][jj-1] + data->score_matrix[char_from_1][GAP];
            int  top_score = curr_tile[ii-1][jj  ] + data->score_matrix[GAP][char_from_2];

            /* Set the local tile[i][j] to the maximum value of northwest, north and west */
            curr_tile[ii][jj] = max_score(left_score, max_score(top_score, diag_score));
        }
    }

    int *right = cncCreateItemVector_left(data->th+1);
    for (index = 0; index <= data->th; index++) {
        right[index] = curr_tile[index][data->tw];
    }
    cncPut_left(right, i, j+1, ctx);
    ASSERT(above[data->tw] == right[0]);

    int *below = cncCreateItemVector_above(data->tw+1);
    for (index = 0; index <= data->tw; index++) {
        below[index] = curr_tile[data->th][index];
    }
    cncPut_above(below, i+1, j, ctx);
    ASSERT(left[data->th] == below[0]);

    /* Cleanup */
    free(curr_tile);
    cncFree(above);
    cncFree(left);
}
