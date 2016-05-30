#include "SmithWaterman.h"
#include <stdlib.h>

static inline int max_score(int x, int y) {
    return (x > y) ? x : y;
}

extern SeqData *data;

/*
 * typeof data is SeqData *
 * typeof above is int *
 * typeof left is int *
 */
#pragma hc continuable
void swStep(cncTag_t i, cncTag_t j, aboveItem above, leftItem left, SmithWatermanCtx *ctx) {
    LOG_INFO("SW: assert above=%p, left=%p\n", above, left);
    int index, ii, jj;
    ASSERT(above[0] == left[0] && "Diagonal values should match");

    LOG_INFO("SW: malloc\n");
    /* Allocate a haloed local matrix for calculating 'this' tile*/
    /* 2D-ify it for readability */
    int (*curr_tile)[data->tw+1] = malloc(sizeof(int)*(1+data->tw)*(1+data->th));

    LOG_INFO("SW: left\n");
    /* Set local_tile[i+1][0] (left column) from the right column of the left tile */
    for (index = 0; index <= data->th; index++) {
        curr_tile[index][0] = left[index];
    }

    LOG_INFO("SW: top\n");
    /* Set local_tile[0][j+1] (top row) from the bottom row of the above tile */
    for (index = 0; index <= data->tw; ++index) {
        curr_tile[0][index] = above[index];
    }

    /* Run a smith-waterman on the local tile */
    for (ii = 1; ii <= data->th; ii++) {
        LOG_INFO("SW: ii=%d\n", ii);
        for (jj = 1; jj <= data->tw; jj++) {
            LOG_INFO("SW: jj=%d\n", jj);
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

    int *right;
    cncHandle_t right_handle = cncCreateItem_left(&right, data->th+1);
    for (index = 0; index <= data->th; index++) {
        right[index] = curr_tile[index][data->tw];
    }
    cncPut_left(right_handle, i, j+1, ctx);
    ASSERT(above[data->tw] == right[0]);

    int *below;
    cncHandle_t below_handle = cncCreateItem_above(&below, data->tw+1);
    for (index = 0; index <= data->tw; index++) {
        below[index] = curr_tile[data->th][index];
    }
    cncPut_above(below_handle, i+1, j, ctx);
    ASSERT(left[data->th] == below[0]);

    LOG_INFO("SW: free\n");
    free(curr_tile);
    CNC_DESTROY_ITEM(above);
    CNC_DESTROY_ITEM(left);
}
