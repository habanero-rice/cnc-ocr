#include "SmithWaterman.h"

void SmithWaterman_init(SmithWatermanArgs *args, SmithWatermanCtx *ctx) {

    // Unpack arguments
    s32 tw = args->tw;
    s32 th = args->th;
    s32 ntw = args->ntw;
    s32 nth = args->nth;
    cncPut_data(args->dataHandle, ctx);

    // Record starting time
    struct timeval *startTime;
    cncHandle_t startTime_handle = cncCreateItem_startTime(&startTime, 1);
    gettimeofday(startTime, 0);
    cncPut_startTime(startTime_handle, ctx);

    // Seed edges
    cncPrescribe_initAboveStep(tw, ntw, ctx);
    cncPrescribe_initLeftStep(th, nth, ctx);

    { // Prescribe "swStep" steps
        s64 _i, _j;
        for (_i = 0; _i < ((nth)-(0)); _i++) {
            for (_j = 0; _j < ((ntw)-(0)); _j++) {
                cncPrescribe_swStep(_i, _j, ctx);
            }
        }
    }

    // Set finalizer function's tag
    SmithWaterman_await(ntw, nth, tw, ctx);
}


/*
 * typeof startTime is struct timeval *
 * typeof above is int *
 */
void SmithWaterman_finalize(cncTag_t ntw, cncTag_t nth, cncTag_t tw, startTimeItem startTime, aboveItem above, SmithWatermanCtx *ctx) {
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double secondsRun = endTime.tv_sec - startTime.item->tv_sec;
    secondsRun += (endTime.tv_usec - startTime.item->tv_usec) / 1000000.0;
    PRINTF("The computation took %f seconds\n", secondsRun);
    // Print the result
    PRINTF("score: %d\n", above.item[tw]);
}
