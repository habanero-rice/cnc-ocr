#include "EvenOddSums.h"

ocrGuid_t mainEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    CNC_REQUIRE(OCR_MAIN_ARGC == 2, "Requires one argument N.\n");

    // Create a new graph context
    EvenOddSumsCtx *context = EvenOddSums_create();

    // Set up arguments for new graph instantiation
    EvenOddSumsArgs args = {
        atoi(OCR_MAIN_ARGV(1))
    };
    
    // Launch the graph for execution
    EvenOddSums_launch(&args, context);

    // Exit when the graph execution completes
    CNC_SHUTDOWN_ON_FINISH(context);

    return NULL_GUID;
}
