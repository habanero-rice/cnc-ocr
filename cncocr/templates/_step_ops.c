{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"
{#/****** Item instance data cast ******/-#}
{%- macro unpack_item(i) -%}
{%- with item = g.itemDeclarations[i.collName] -%}
{%- if not item.type.isPtrType %}*{% endif -%}
{{ "(" ~ item.type.ptrType ~ ")" }}
{%- endwith -%}
{%- endmacro -%}

{% for stepfun in g.finalAndSteps %}
{% set isFinalizer = loop.first -%}
/* {{stepfun.collName}} setup/teardown function */
ocrGuid_t _cncStep_{{stepfun.collName}}(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    {{g.name}}Ctx *ctx = depv[0].ptr;

    {% for x in stepfun.tag -%}
    const cncTag_t {{x}} = (cncTag_t)paramv[{{loop.index0}}]; MAYBE_UNUSED({{x}});
    {% endfor %}
    s32 _edtSlot = 1; MAYBE_UNUSED(_edtSlot);

    {#-/****** Set up input items *****/#}
    {% for input in stepfun.inputs %}
{%- set comment = "Get \"" ~ input.binding ~ "\" inputs" -%}
{%- call util.render_indented(1) -%}
{%- call(var) util.render_tag_nest(comment, input, malloc=True) -%}
{{var}}.item = {{unpack_item(input)}}depv[_edtSlot].ptr;
{{var}}.handle = depv[_edtSlot++].guid;
{%- endcall -%}
{%- endcall %}
    {% endfor %}
    // Call user-defined step function
    {{stepfun.collName}}({{ util.print_tag(stepfun.tag) ~ util.print_bindings(stepfun.inputs) }}ctx);
    {% if isFinalizer %}
    // Signal that the finalizer is done
    ocrEventSatisfy(ctx->_guids.finalizedEvent, NULL_GUID);
    {% endif %}
    // TODO - Clean up
    {{ util.log_msg("DONE", stepfun.collName, stepfun.tag) }}
    return NULL_GUID;
}

/* {{stepfun.collName}} task creation */
void cncPrescribe_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True)
        }}{{g.name}}Ctx *ctx) {

    ocrGuid_t _stepGuid;
    {# /* TODO - figure out if there's a way to compute the size of non-rectangular
          ranges (e.g. _i3={0.._i1}). Writing out a whole loop nest, and then
          letting the compiler optimize it away to a constant in the trivial
          (rectangular) case might be possible. */ -#}
    {% if stepfun.tag -%}
    u64 _args[] = { (u64){{ stepfun.tag|join(", (u64)") }} };
    {% else -%}
    u64 *_args = NULL;
    {% endif -%}
    u64 _depc = {{stepfun.inputCountExpr}} + 1;
    ocrEdtCreate(&_stepGuid, ctx->_steps.{{stepfun.collName}},
        /*paramc=*/{{stepfun.tag|count}}, /*paramv=*/_args,
        /*depc=*/_depc, /*depv=*/NULL,
        /*properties=*/EDT_PROP_NONE,
        /*affinity=*/NULL_GUID, /*outEvent=*/NULL);

    s32 _edtSlot = 0; MAYBE_UNUSED(_edtSlot);
    ocrAddDependence(ctx->_guids.self, _stepGuid, _edtSlot++, DB_MODE_RO);

    {#-/****** Set up input items *****/#}
    {% for input in stepfun.inputs %}
{%- set comment = "Set up \"" ~ input.binding ~ "\" input dependencies" -%}
{%- call util.render_indented(1) -%}
{%- call(var) util.render_tag_nest(comment, input) -%}
cncGet_{{input.collName}}(
        {%- for k in input.key %}_i{{loop.index0}}, {% endfor -%}
         _stepGuid, _edtSlot++, DB_DEFAULT_MODE, ctx);
{%- endcall -%}
{%- endcall %}
    {% endfor %}
    ASSERT(_depc == _edtSlot);
    {{ util.log_msg("PRESCRIBED", stepfun.collName, stepfun.tag) }}
}
{% endfor %}

