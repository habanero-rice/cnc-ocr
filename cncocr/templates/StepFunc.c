{% import "common_macros.inc.c" as util with context -%}
{% set stepfun = g.stepFunctions[targetStep] -%}

#include "{{g.name}}.h"

/**
 * Step function defintion for "{{stepfun.collName}}"
 */
void {{stepfun.collName}}({{ util.print_tag(stepfun.tag, typed=True) 
        }}{{ util.print_bindings(stepfun.inputItems, typed=True)
        }}{{g.name}}Ctx *ctx) {
{% if stepfun.rangedInputItems %}
    //
    // INPUTS
    //
{% call util.render_indented(1) -%}
{{ util.render_step_inputs(stepfun.rangedInputItems) }}
{% endcall -%}
{% endif %}
    //
    // OUTPUTS
    //
{% call util.render_indented(1) -%}
{{ util.render_step_outputs(stepfun.outputs) }}
{%- endcall %}

}
