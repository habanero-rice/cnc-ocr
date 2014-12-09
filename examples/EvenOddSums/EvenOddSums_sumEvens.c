#include "EvenOddSums.h"

/**
 * Step function defintion for "sumEvens"
 */
void sumEvens(cncTag_t n, int *evens, EvenOddSumsCtx *ctx) {

    //
    // INPUTS
    //

    int sum = 0;
    { // Access "evens" inputs
        s64 _i;
        for (_i = 0; _i < n; _i++) {
            sum += evens[_i];
        }
    }


    //
    // OUTPUTS
    //

    // Put "evensTotal" items
    int *evensTotal = cncCreateItem_evensTotal();
    *evensTotal = sum;
    cncPut_evensTotal(evensTotal, ctx);


}
