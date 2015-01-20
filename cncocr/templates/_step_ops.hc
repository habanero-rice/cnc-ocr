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
#define {{ util.coll2id(stepfun.collName) }} {{ loop.index0 }}
{%- endfor %}
{% for stepfun in g.finalAndSteps %}
{% set isFinalizer = loop.first -%}

#ifdef HC_COMM
static int _done[1];
static HCMPI_Status *_doneReq;
#endif 

{% if not isFinalizer %}
#ifdef HC_COMM
static void _{{stepfun.collName}}_remote({{
            util.print_tag(stepfun.tag, typed=True)
        }}int _rank) {
    s32 _xtag[] = { {{ util.coll2id(stepfun.collName) }}{% if stepfun.tag -%}
        {{ ", " ~ (stepfun.tag|join(", ")) }}
    {%- endif %} };
    hc_cnc_prescribe(_rank, _xtag, {{1+(stepfun.tag|count)}});
}
#endif
{% endif %}

/* {{stepfun.collName}} task creation */
void cncPrescribe_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True)
        }}{{g.name}}Ctx *ctx) {
{% if not isFinalizer %}
#ifdef HC_COMM
    int _rank = {{ util.stepDistFn(stepfun) }};
    if (_rank != HCMPI_COMM_RANK) {
        LOG_INFO("Remote prescribe {{stepfun.collName}}\n");
        _{{stepfun.collName}}_remote({{ util.print_tag(stepfun.tag) }}_rank);
        return;
    }
    LOG_INFO("Local prescribe {{stepfun.collName}}\n");
#endif
{% endif %}
    {#- /* TODO - figure out if there's a way to compute the size of non-rectangular
           ranges (e.g. _i3={0.._i1}). Writing out a whole loop nest, and then
           letting the compiler optimize it away to a constant in the trivial
           (rectangular) case might be possible. */ #}
    //u64 _depc = {{stepfun.inputCountExpr}} + 1;

    {#-/****** Set up input items *****/#}
    {% for input in stepfun.inputs %}
    // Set up "{{input.binding}}" input dependencies
    DDF_t *{{input.binding}} = cncGet_{{input.collName}}(
            {%- for k in input.key %}{{k.expr}}, {% endfor -%}
            ctx);
    {% endfor %}

    // TODO - refactor into an _internal helper function (no rank check)
    {% set ddfList = stepfun.inputs | join(", ", attribute='binding') -%}
    {% set inDDFs = (ddfList ~ ", ") if ddfList else "" -%}
    async IN({{util.print_tag(stepfun.tag) ~ inDDFs}}ctx)
        {%- if ddfList %} AWAIT({{ddfList}}){% endif %} {
        {{ util.log_msg("RUNNING", stepfun.collName, stepfun.tag) }}
        {{stepfun.collName}}({{ util.print_tag(stepfun.tag) }}
                {%- for input in stepfun.inputs -%}
                {% if g.lookupType(input).isPtrType -%}
                ({{input.collName}}Item){{input.binding}}->datum,
                {%- else -%}
                *({{input.collName}}Item*){{input.binding}}->datum,
                {%- endif %} {% endfor -%}
                ctx);
        {{ util.log_msg("DONE", stepfun.collName, stepfun.tag) }}
        {% if isFinalizer %}
#ifdef HC_COMM
        { // Done!
            int _dest = 1;
            // XXX - looping might not be the best idea here.
            for (; _dest < HCMPI_COMM_SIZE; _dest++) {
                HCMPI_Send(_done, 0, HCMPI_BYTE, _dest, CNC_SHUTDOWN_TAG, HCMPI_COMM_WORLD);
                LOG_INFO("Sent done message to %d\n", _dest);
            }
            LOG_INFO("Broadcast sent!");
        }
#endif
        {% endif %}
    }
    {{ util.log_msg("PRESCRIBED", stepfun.collName, stepfun.tag) }}
}

{% if not isFinalizer %}
#ifdef HC_COMM
static void _cncPrescribeF_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True)
        }}{{g.name}}Ctx *ctx) {
    finish {
        async IN({{ util.print_tag(stepfun.tag) }}ctx) {
            cncPrescribe_{{stepfun.collName}}({{ util.print_tag(stepfun.tag) }}ctx);
        }
    }
}
#endif
{% endif %}

{% endfor %}

#ifdef HC_COMM
void hc_cnc_xprescribe_internal(void *msg) {
    s32 *xtag = msg;
    s32 coll = xtag[0];
    switch (coll) {
    {% for stepfun in g.stepFunctions.values() %}
        case {{ util.coll2id(stepfun.collName) }}: {
            _cncPrescribeF_{{stepfun.collName}}({% for x in stepfun.tag -%}
                xtag[{{loop.index}}], {% endfor %}{{ util.globalCtx(g) }});
            break;
        }
    {% endfor %}
        default:
            ASSERT(!"Unreachable");
    }
    // XXX - debugging
    xtag[0] = 9999;
}

#endif

void {{g.name}}_launch({{g.name}}Args *args, {{g.name}}Ctx *ctx) {
#ifdef HC_COMM
    {{g.name}}_startDaemons(ctx);
#endif
    finish {
#ifdef HC_COMM
        if (0 == HCMPI_COMM_RANK) {
#endif
            {{g.name}}_init(args, ctx);
#ifdef HC_COMM
        }
        else {
            // XXX - Couldn't actually use Bcast here because MPI_Bcast doesn't accept a tag
            // and HC-MPI doesn't allow for multiple communicators.
            HCMPI_Recv(_done, 0, HCMPI_BYTE, 0, CNC_SHUTDOWN_TAG, HCMPI_COMM_WORLD, &_doneReq);
            LOG_INFO("Broadcast received!");
        }
#endif
    }
}
