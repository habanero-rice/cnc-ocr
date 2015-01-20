#include "EvenOddSums.h"

/*
 * typeof evens is int 
 */
void sumEvens(cncTag_t n, evensItem *evens, EvenOddSumsCtx *ctx) {

    //
    // INPUTS
    //

    int sum = 0;
    { // Access "evens" inputs
        s64 _i;
        for (_i = 0; _i < ((n)-(0)); _i++) {
            sum += evens[_i];
        }
    }


    //
    // OUTPUTS
    //

    // Put "evensTotal" items
    int *evensTotal;
    cncHandle_t evensTotalHandle = cncCreateItem_evensTotal(&evensTotal);
    *evensTotal = sum;
    cncPut_evensTotal(evensTotalHandle, ctx);


}
