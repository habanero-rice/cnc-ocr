#include "SimpleGraph.h"

int main(int argc, char **argv) {

    /* Create a new graph context */
    SimpleGraphCtx *context = SimpleGraph_create();

    /* Set up arguments for new graph instantiation */
    SimpleGraphArgs args = {
        /* TODO: initialize custom arguments
         * Note that you should define the members of
         * this struct by editing SimpleGraph_defs.h.
         */
    };
    
    finish {
        /* Launch the graph for execution */
        SimpleGraph_init(&args, context);
    }

    /* Exit when the graph execution completes */
    CNC_SHUTDOWN_ON_FINISH(context);
    
    return 0;
}
