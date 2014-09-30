#include "EvenOddSums.h"

void EvenOddSums_init(EvenOddSumsArgs *args, EvenOddSumsCtx *ctx) {


    { // Put "naturals" items
        s64 _i;
        for (_i = 0; _i < ((args->n)-(0)); _i++) {
            int *naturals;
            cncHandle_t naturalsHandle = cncCreateItem_naturals(&naturals);
            *naturals = _i;
            cncPut_naturals(naturalsHandle, _i, ctx);
        }
    }

    // Prescribe "sumEvens" steps
    cncPrescribe_sumEvens(args->n/2 + args->n%2, ctx);

    // Prescribe "sumOdds" steps
    cncPrescribe_sumOdds(args->n/2, ctx);

    // Set finalizer function's tag
    EvenOddSums_await(ctx);

}


/*
 * typeof evensTotal is int 
 * typeof oddsTotal is int 
 */
void EvenOddSums_finalize(evensTotalItem evensTotal, oddsTotalItem oddsTotal, EvenOddSumsCtx *ctx) {
    PRINTF("Even total = %d\n", evensTotal.item);
    PRINTF("Odd total = %d\n", oddsTotal.item);
}


/* Mapping odds onto naturals */
naturalsItemKey oddsToNaturals(cncTag_t i, EvenOddSumsCtx *ctx) {
    naturalsItemKey _result;
    _result.i = i*2 + 1;
    return _result;
}

