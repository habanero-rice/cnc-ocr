{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"
{% if affinitiesEnabled -%}
#include <extensions/ocr-affinity.h>
{% endif %}
{#/****** Item instance data cast ******/-#}
{%- macro unpack_item(i) -%}
{%- with itemType = g.lookupType(i) -%}
{%- if not itemType.isPtrType %}*{% endif -%}
{{ "(" ~ itemType.ptrType ~ ")" }}
{%- endwith -%}
{%- endmacro -%}

{% if logEnabled %}
#ifndef CNCOCR_x86
#error "Debug logging mode only supported on x86 targets"
#endif
#include <pthread.h>
extern pthread_mutex_t _cncDebugMutex;
{% endif -%}

{% for stepfun in g.finalAndSteps %}
{% set isFinalizer = loop.first -%}
{% set paramTag = (stepfun.tag|count) <= 8 -%}
/* {{stepfun.collName}} setup/teardown function */
ocrGuid_t _cncStep_{{stepfun.collName}}(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    {{g.name}}Ctx *ctx = depv[0].ptr;

    u64 *_tag = {{ "paramv" if paramTag else "depv[1].ptr" }}; MAYBE_UNUSED(_tag);
    {% for x in stepfun.tag -%}
    const cncTag_t {{x}} = (cncTag_t)_tag[{{loop.index0}}]; MAYBE_UNUSED({{x}});
    {% endfor -%}
    {% if not paramTag -%}
    ocrDbDestroy(depv[1].guid); // free tag component datablock
    {% endif %}
    s32 _edtSlot = {{ 1 if paramTag else 2 }}; MAYBE_UNUSED(_edtSlot);
    {#-/****** Set up input items *****/#}
    {% for input in stepfun.inputItems %}
    {% if input.keyRanges -%}
    {#/*RANGED*/-#}
    {{ util.ranged_type(input) ~ input.binding }};
    ocrEdtDep_t _block_{{input.binding}};
    { // Init ranges for "{{input.binding}}"
        u32 _i;
        u32 _itemCount = {{input.keyRanges|join("*", attribute='sizeExpr')}};
        u32 _dims[] = { {{input.keyRanges|join(", ", attribute='sizeExpr')}} };
        // XXX - I'd like to use pdMalloc here instead of creating a datablock
        {{ g.lookupType(input) }}*_item = _cncRangedInputAlloc({{ input.keyRanges|count
                }}, _dims, sizeof({{ g.lookupType(input) }}), &_block_{{input.binding}});
        {{input.binding}} = _block_{{input.binding}}.ptr;
        for (_i=0; _i<_itemCount; _i++) {
            _item[_i] = {{unpack_item(input)}}_cncItemDataPtr(depv[_edtSlot++].ptr);
        }
    }
    {% else -%}
    {#/*SCALAR*/-#}
    {{ g.lookupType(input) ~ input.binding }};
    {{input.binding}} = {{unpack_item(input)}}_cncItemDataPtr(depv[_edtSlot++].ptr);
    {% endif -%}
    {% endfor %}
    {{ util.step_enter() }}
    // Call user-defined step function
    {{ util.log_msg("RUNNING", stepfun.collName, stepfun.tag) }}
    {{stepfun.collName}}({{ util.print_tag(stepfun.tag) ~ util.print_bindings(stepfun.inputItems) }}ctx);
    {% if isFinalizer %}
    // Signal that the finalizer is done
    ocrEventSatisfy(ctx->_guids.finalizedEvent, NULL_GUID);
    {% endif %}
    // Clean up
    {% for input in stepfun.rangedInputItems -%}
    ocrDbDestroy(_block_{{input.binding}}.guid);
    {% endfor -%}
    {{ util.log_msg("DONE", stepfun.collName, stepfun.tag) }}
    {{ util.step_exit() }}
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
    {% if not paramTag -%}
    ocrGuid_t _tagBlockGuid;
    u64 *_tagBlockPtr;
    SIMPLE_DBCREATE(&_tagBlockGuid, (void**)&_tagBlockPtr, sizeof(_args));
    hal_memCopy(_tagBlockPtr, _args, sizeof(_args), 0);
    ocrDbRelease(_tagBlockGuid);
    {% endif -%}
    {% else -%}
    u64 *_args = NULL;
    {% endif -%}
    // affinity
    // TODO - allow custom distribution
    {% if affinitiesEnabled and stepfun.tag -%}
    ocrGuid_t _affinity;
    {
        u64 _affinityCount;
        ocrAffinityCount(AFFINITY_PD, &_affinityCount);
        ASSERT(_affinityCount >= 1);
        ocrGuid_t _affinities[_affinityCount];
        ocrAffinityGet(AFFINITY_PD, &_affinityCount, _affinities);
        const u64 _i = {{stepfun.tag[0]}} % _affinityCount;
        _affinity = _affinities[_i];
    }
    {%- else -%}
    const ocrGuid_t _affinity = NULL_GUID;
    {%- endif %}
    u64 _depc = {{stepfun.inputCountExpr}} + {{ 1 if paramTag else 2 }};
    ocrEdtCreate(&_stepGuid, ctx->_steps.{{stepfun.collName}},
        {% if paramTag -%}
        /*paramc=*/{{(stepfun.tag|count)}}, /*paramv=*/_args,
        {% else -%}
        /*paramc=*/0, /*paramv=*/NULL,
        {% endif -%}
        /*depc=*/_depc, /*depv=*/NULL,
        /*properties=*/EDT_PROP_NONE,
        /*affinity=*/_affinity, /*outEvent=*/NULL);

    s32 _edtSlot = 0; MAYBE_UNUSED(_edtSlot);
    ocrAddDependence(ctx->_guids.self, _stepGuid, _edtSlot++, DB_MODE_RO);
    {% if not paramTag -%}
    ocrAddDependence(_tagBlockGuid, _stepGuid, _edtSlot++, DB_MODE_RO);
    {% endif -%}

    {#-/****** Set up input items *****/#}
    {% set inputIsEnabled = [ true ] -%}
    {%- call util.render_indented(1) -%}
{% for input in stepfun.inputs recursive -%}
{% if input.kind in ['IF', 'ELSE'] -%}
if ({{ input.cond }}) {
{%- call util.render_indented(1) -%}
{{ loop(input.refs) }}
{%- endcall %}
}
{% do inputIsEnabled.append(false) -%}
else {
{%- call util.render_indented(1) -%}
{{ loop(input.refs) }}
{%- endcall %}
}
{% do inputIsEnabled.pop() -%}
{% else -%}
{%- set comment = "Set up \"" ~ input.binding ~ "\" input dependencies" -%}
{%- call(var) util.render_tag_nest(comment, input, useTag=inputIsEnabled[-1]) -%}
{%- if inputIsEnabled[-1] -%}
cncGet_{{input.collName}}(
        {%- for k in input.key %}_i{{loop.index0}}, {% endfor -%}
         _stepGuid, _edtSlot++, DB_DEFAULT_MODE, ctx);
{%- else -%}
ocrAddDependence(NULL_GUID, _stepGuid, _edtSlot++, DB_DEFAULT_MODE);
{%- endif -%}
{%- endcall -%}
{% endif %}
{% endfor %}
{% endcall %}
    ASSERT(_depc == _edtSlot);
    {{ util.log_msg("PRESCRIBED", stepfun.collName, stepfun.tag) }}
}
{% endfor %}

