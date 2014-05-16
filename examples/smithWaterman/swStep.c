
#include "Common.h"

static inline int max_score(int x, int y) {
    return (x > y) ? x : y;
}

void swStep(int i, int j, dataItem data, aboveItem above, leftItem left, Context *context) {
    int index, ii, jj;
    ASSERT(above.item[0] == left.item[0] && "Diagonal values should match");

    /* Allocate a haloed local matrix for calculating 'this' tile*/
    /* 2D-ify it for readability */
    int (*curr_tile)[data.item->tw+1] = MALLOC(sizeof(int)*(1+data.item->tw)*(1+data.item->th));

    /* Set local_tile[i+1][0] (left column) from the right column of the left tile */
    for (index = 0; index <= data.item->th; index++) {
        curr_tile[index][0] = left.item[index];
    }

    /* Set local_tile[0][j+1] (top row) from the bottom row of the above tile */
    for (index = 0; index <= data.item->tw; ++index) {
        curr_tile[0][index] = above.item[index];
    }

    /* Run a smith-waterman on the local tile */
    for (ii = 1; ii <= data.item->th; ii++) {
        for (jj = 1; jj <= data.item->tw; jj++) {
            char char_from_1 = TSEQ1(data.item)[j][jj-1];
            char char_from_2 = TSEQ2(data.item)[i][ii-1];

            /* Get score from northwest, north and west */
            int diag_score = curr_tile[ii-1][jj-1] + data.item->score_matrix[char_from_2][char_from_1];
            int left_score = curr_tile[ii  ][jj-1] + data.item->score_matrix[char_from_1][GAP];
            int  top_score = curr_tile[ii-1][jj  ] + data.item->score_matrix[GAP][char_from_2];

            /* Set the local tile[i][j] to the maximum value of northwest, north and west */
            curr_tile[ii][jj] = max_score(left_score, max_score(top_score, diag_score));
        }
    }

    int *below;
    cncHandle_t below_handle = cncCreateItem_above(&below, data.item->tw+1);
    for (index = 0; index <= data.item->tw; index++) {
        below[index] = curr_tile[data.item->th][index];
    }
    Put(below_handle, CREATE_TAG(i+1, j), context->above);
    ASSERT(left.item[data.item->th] == below[0]);

    int *right;
    cncHandle_t right_handle = cncCreateItem_left(&right, data.item->th+1);
    for (index = 0; index <= data.item->th; index++) {
        right[index] = curr_tile[index][data.item->tw];
    }
    Put(right_handle, CREATE_TAG(i, j+1), context->left);
    ASSERT(above.item[data.item->tw] == right[0]);

    /* Cleanup */
    FREE(curr_tile);
    CNC_DESTROY_ITEM(above.handle);
    CNC_DESTROY_ITEM(left.handle);
}

