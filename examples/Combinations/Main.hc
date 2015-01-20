#include "Combinations.h"

int main(int argc, char **argv) {

    CNC_REQUIRE(OCR_MAIN_ARGC == 3, "Usage: %s N K\nComputes N-choose-K\n", OCR_MAIN_ARGV(0));

    // Create a new graph context
    CombinationsCtx *context = Combinations_create();

    // Set up arguments for new graph instantiation
    CombinationsArgs args = { };
    
    // initialize graph context parameters
    context->n = atoi(OCR_MAIN_ARGV(1));
    context->k = atoi(OCR_MAIN_ARGV(2));
    
    /* Launch the graph for execution */
    Combinations_launch(&args, context);

    // Exit when the graph execution completes
    CNC_SHUTDOWN_ON_FINISH(context);
    
    return 0;
}
