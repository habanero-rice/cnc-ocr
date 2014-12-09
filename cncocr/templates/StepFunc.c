{% import "common_macros.inc.c" as util with context -%}
{% set stepfun = g.stepFunctions[targetStep] -%}
{% set rangedInputs = stepfun.inputs|selectattr('keyRanges')|list -%}

#include "{{g.name}}.h"

/**
 * Step function defintion for "{{stepfun.collName}}"
 */
void {{stepfun.collName}}({{ util.print_tag(stepfun.tag, typed=True) 
        }}{{ util.print_bindings(stepfun.inputs, typed=True)
        }}{{g.name}}Ctx *ctx) {
{% if rangedInputs %}
    //
    // INPUTS
    //
{% for input in rangedInputs %}
{%- set comment = "Access \"" ~ input.binding ~ "\" inputs" -%}
{%- set decl = g.itemDeclarations[input.collName] -%}
{%- call util.render_indented(1) -%}
{%- call(args, ranges) util.render_io_nest(comment, input.key, decl.key, zeroBased=True) -%}
{%- set var = input.binding ~ util.print_indices(ranges) -%}
/* TODO: Do something with {{var}} */
{%- endcall -%}
{%- endcall %}
{% endfor %}
{% endif %}
    //
    // OUTPUTS
    //
{% for output in stepfun.outputs %}
{%- call util.render_indented(1) -%}
{% if output.kind == 'ITEM' -%}
{%- set comment = "Put \"" ~ output.binding ~ "\" items" -%}
{%- set decl = g.itemDeclarations[output.collName] -%}
{%- call(args, ranges) util.render_io_nest(comment, output.key, decl.key) -%}
{%- set var = output.binding ~ util.print_indices(ranges) -%}
{{decl.type.ptrType ~ output.binding}} = cncCreateItem_{{output.collName
    }}({% if decl.type.isPtrType %}/* TODO: count=*/1{% endif %});
/* TODO: Initialize {{output.binding}} */
cncPut_{{output.collName}}({{output.binding}}, {% for x in args %}{{x}}, {% endfor %}ctx);
{%- endcall -%}
{% else -%}
{%- set comment = "Prescribe \"" ~ output.collName ~ "\" steps" -%}
{%- set decl = g.stepFunctions[output.collName] -%}
{%- call(args, ranges) util.render_io_nest(comment, output.tag, decl.tag) -%}
cncPrescribe_{{output.collName}}({% for x in args %}{{x}}, {% endfor %}ctx);
{%- endcall -%}
{% endif -%}
{%- endcall %}
{% endfor %}

}
