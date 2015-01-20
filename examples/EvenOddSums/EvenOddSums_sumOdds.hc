#include "EvenOddSums.h"

/*
 * typeof odds is int 
 */
void sumOdds(cncTag_t n, oddsItem *odds, EvenOddSumsCtx *ctx) {

    //
    // INPUTS
    //

    int sum = 0;
    { // Access "odds" inputs
        s64 _i;
        for (_i = 0; _i < ((n)-(0)); _i++) {
            sum += odds[_i];
        }
    }


    //
    // OUTPUTS
    //

    // Put "oddsTotal" items
    int *oddsTotal;
    cncHandle_t oddsTotalHandle = cncCreateItem_oddsTotal(&oddsTotal);
    *oddsTotal = sum;
    cncPut_oddsTotal(oddsTotalHandle, ctx);


}
