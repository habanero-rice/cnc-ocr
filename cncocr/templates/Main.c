#include "{{g.name}}.h"

int cncMain(int argc, char *argv[]) {

    // Create a new graph context
    {{g.name}}Ctx *context = {{g.name}}_create();

    // Set up arguments for new graph instantiation
    {{g.name}}Args args = {
        // TODO: initialize custom arguments
        // Note that you should define the members of
        // this struct by editing {{g.name}}_defs.h.
    };
    {% if g.ctxParams %}
    // TODO: initialize graph context parameters
    {% for line in g.ctxParams -%}
    // {{ line }}
    {% endfor -%}
    {% endif %}
    // Launch the graph for execution
    {{g.name}}_launch(&args, context);

    // Exit when the graph execution completes
    CNC_SHUTDOWN_ON_FINISH(context);

    return 0;
}
