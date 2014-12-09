#include "Combinations.h"

ocrGuid_t mainEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {

    // Create a new graph context
    CombinationsCtx *context = Combinations_create();

    CombinationsArgs args;

    // TODO: initialize graph context parameters
    // u32 n, k;
    context->n = atoi(OCR_MAIN_ARGV(1));
    context->k = atoi(OCR_MAIN_ARGV(2));

    // Launch the graph for execution
    Combinations_launch(&args, context);

    // Exit when the graph execution completes
    CNC_SHUTDOWN_ON_FINISH(context);
    
    return NULL_GUID;
}
