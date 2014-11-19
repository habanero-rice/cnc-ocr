{% import "common_macros.inc.c" as util with context -%}

#include "{{g.name}}.h"

void {{g.name}}_init({{g.name}}Args *args, {{g.name}}Ctx *ctx) {
{% if g.initFunction.tag %}
    // TODO: Initialize these tag variables using args
    cncTag_t {{ g.initFunction.tag|join(", ") }};
{% endif %}
{#/* XXX - This code is copied from StepFunc.c */-#}
{% for output in g.initFunction.outputs %}
{%- call util.render_indented(1) -%}
{% if output.kind == 'ITEM' -%}
{%- set comment = "Put \"" ~ output.binding ~ "\" items" -%}
{%- set decl = g.itemDeclarations[output.collName] -%}
{%- call(args, ranges) util.render_io_nest(comment, output.key, decl.key) -%}
{%- set var = output.binding ~ util.print_indices(ranges) -%}
{{decl.type.ptrType ~ output.binding}};
cncHandle_t {{output.binding}}Handle = cncCreateItem_{{output.collName
    }}(&{{output.binding}}{% if decl.type.isPtrType %}, /* TODO: count=*/1{% endif %});
/* TODO: Initialize {{output.binding}} */
cncPut_{{output.collName}}({{output.binding}}Handle, {% for x in args %}{{x}}, {% endfor %}ctx);
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
    // Set finalizer function's tag
    {{g.name}}_await({{util.print_tag(g.finalizeFunction.tag)}}ctx);

}


{#/* XXX -  This code is copied from StepFunc.c */-#}
{% set stepfun = g.finalizeFunction -%}
/*{% for name in stepfun.inputColls %}
 * typeof {{name}} is {{g.itemDeclarations[name].type}}
{%- endfor %}
 */
void {{stepfun.collName}}({{ util.print_tag(stepfun.tag, typed=True) 
        }}{{ util.print_bindings(stepfun.inputs, typed=True)
        }}{{g.name}}Ctx *ctx) {
{% for input in stepfun.inputs -%}
{% if input.keyRanges %}
{%- set comment = "Access \"" ~ input.binding ~ "\" inputs" -%}
{%- set decl = g.itemDeclarations[input.collName] -%}
{%- call util.render_indented(1) -%}
{%- call(args, ranges) util.render_io_nest(comment, input.key, decl.key, zeroBased=True) -%}
{%- set var = input.binding ~ util.print_indices(ranges) -%}
/* TODO: Do something with {{var}}.item */
{%- endcall -%}
{%- endcall -%}
{% else %}
    /* TODO: Do something with {{input.binding}}.item */
{% endif -%}
{% endfor %}
}
{% if g.externVms %}

{% for i in g.externVms -%}
/* Mapping {{i.collName}} onto {{i.mapTarget}} */
{{i.mapTarget}}ItemKey {{i.functionName}}({{
  util.print_tag(i.key, typed=True)
  }}{{g.name}}Ctx *ctx) {
    {{i.mapTarget}}ItemKey _result;
    {% for x in g.itemDeclarations[i.mapTarget].key -%}
    _result.{{x}} = /*TODO*/0;
    {% endfor -%}
    return _result;
}
{% endfor %}
{% endif %}
