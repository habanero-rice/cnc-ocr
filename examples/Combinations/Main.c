#include "Combinations.h"

int cncMain(int argc, char *argv[]) {

    // Create a new graph context
    CombinationsCtx *context = Combinations_create();

    CombinationsArgs args;

    // initialize graph context parameters
    // u32 n, k;
    context->n = atoi(argv[1]);
    context->k = atoi(argv[2]);

    // Launch the graph for execution
    Combinations_launch(&args, context);

    // Exit when the graph execution completes
    CNC_SHUTDOWN_ON_FINISH(context);
    
    return 0;
}
