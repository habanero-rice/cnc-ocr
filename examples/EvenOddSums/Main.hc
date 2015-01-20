#include "EvenOddSums.h"

int main(int argc, char **argv) {
    CNC_REQUIRE(argc == 2, "Requires one argument N.\n");

    // Create a new graph context
    EvenOddSumsCtx *context = EvenOddSums_create();

    // Exit when the graph execution completes
    CNC_SHUTDOWN_ON_FINISH(context);
    
    // Set up arguments for new graph instantiation
    EvenOddSumsArgs args = { atoi(argv[1]) };

    finish {
        /* Launch the graph for execution */
        EvenOddSums_init(&args, context);
    }

    return 0;
}
