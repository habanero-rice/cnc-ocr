#include "{{g.name}}.h"

ocrGuid_t mainEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {

    // Create a new graph context
    {{g.name}}Ctx *context = {{g.name}}_create();

    // Exit when the graph execution completes
    // NOTE: This call MUST come before {{g.name}}_launch
    CNC_SHUTDOWN_ON_FINISH(context);
    
    // Set up arguments for new graph instantiation
    {{g.name}}Args args = {
        /* TODO: initialize custom arguments
         * Note that you should define the members of
         * this struct by editing {{g.name}}_defs.h.
         */
    };
    {% if g.ctxParams %}
    // TODO: initialize graph context parameters
    {% for line in g.ctxParams -%}
    // {{ line }}
    {% endfor -%}
    {% endif %}
    // Launch the graph for execution
    {{g.name}}_launch(&args, context);

    return NULL_GUID;
}
