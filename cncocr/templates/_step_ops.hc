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

// XXX - assuming flat (1D) ranges
void *_cncUnpackRange(DDF_list_t *ddl) {
    void **data = hc_malloc(sizeof(void*) * ddl->lsize);
    DDF_list_node_t *n = ddl->head;
    void **p = data;
    while (n) {
        *p = (void*)n->self->datum;
        n = n->nextNode;
        p++;
    }
    return (void*)data;
}

extern DDF_t *NULL_DDF;

static inline void *_unpackDDF(DDF_t *ddf) {
    return (ddf == NULL_DDF) ? NULL : (void*)ddf->datum;
}

#ifdef HC_COMM
static int _done[1];
static HCMPI_Status *_doneReq;
void hc_cnc_xprescribe_local(s32 coll, s32 *tag);
#endif 


{% for stepfun in tuningInfo.steplikes %}
#define {{ util.coll2id(stepfun.collName) }} {{ loop.index0 }}
{%- endfor %}
{% for stepfun in tuningInfo.steplikes %}
{% set isFinalizer = loop.first -%}

{% if not isFinalizer %}
#ifdef HC_COMM
static void _{{stepfun.collName}}_remote({{
            util.print_tag(stepfun.tag, typed=True)
        }}int _rank) {
    s32 _xtag[] = { {{ util.coll2id(stepfun.collName) }}{% if stepfun.tag -%}
        {{ ", " ~ (stepfun.tag|join(", ")) }}
    {%- endif %} };
    LOG_INFO("Remote prescribe {{stepfun.collName}}\n");
    hc_cnc_prescribe(_rank, _xtag, {{1+(stepfun.tag|count)}});
}
#endif
{% endif %}

/* {{stepfun.collName}} task creation */
#pragma hc continuable
void cncPrescribeT_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True)
        }}{{g.name}}Ctx *ctx) {
    {#- /* TODO - figure out if there's a way to compute the size of non-rectangular
           ranges (e.g. _i3={0.._i1}). Writing out a whole loop nest, and then
           letting the compiler optimize it away to a constant in the trivial
           (rectangular) case might be possible. */ #}
    //u64 _depc = {{stepfun.inputCountExpr}} + 1;
    LOG_INFO("Local prescribe {{stepfun.collName}}\n");

    {#-/****** Set up input items *****/#}
    {% for input in stepfun.inputs %}
    // Set up "{{input.binding}}" input dependencies
    {% if input.keyRanges -%}
    {#/*RANGED*/-#}
    {% set comment = "// Init ranges for \"" ~ input.binding ~ "\"" -%}
    {{ util.render_hc_gets_nest(comment, input) }}
    {% else -%}
    {#/*SCALAR*/-#}
    DDF_t *{{input.binding}} = {% if input.condition -%}
    ({{input.condition}}) ? {% endif %}cncGet_{{input.collName}}(
            {%- for k in input.key %}{{k.expr}}, {% endfor -%}
            ctx){% if input.condition %} : NULL_DDF{% endif %};
    {% endif %}
    {% endfor %}

    {{ util.log_msg("PRESCRIBED", stepfun.collName, stepfun.tag) }}
    // TODO - refactor into an _internal helper function (no rank check)
    {% set ddfList = stepfun.inputs | join(", ", attribute='binding') -%}
    {% set inDDFs = (ddfList ~ ", ") if ddfList else "" -%}
    async IN({{util.print_tag(stepfun.tag) ~ inDDFs}}ctx)
        {%- if ddfList %} AWAIT({{ddfList}}){% endif %} {
        {{ util.log_msg("RUNNING", stepfun.collName, stepfun.tag) }}
        {{stepfun.collName}}({{ util.print_tag(stepfun.tag) }}
                {%- for input in stepfun.inputs -%}
                {% if input.keyRanges -%}
                _cncUnpackRange({{input.binding}}),
                {% elif g.lookupType(input).isPtrType -%}
                ({{input.collName}}Item)_unpackDDF({{input.binding}}),
                {%- else -%}
                *({{input.collName}}Item*)_unpackDDF({{input.binding}}),
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
}

#pragma hc continuable
{#/* XXX - assuming all cncPrescribeR_* calls are made at
     the tuning root node in the generated tuning code */#}
void cncPrescribe{{ "R" if useHPT else "" }}_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True)
        }}{{g.name}}Ctx *ctx) {
{% if not isFinalizer %}
#ifdef HC_COMM
    int _rank = {{ util.stepDistFn(stepfun) }};
    if (_rank != HCMPI_COMM_RANK) {
        _{{stepfun.collName}}_remote({{ util.print_tag(stepfun.tag) }}_rank);
        return;
    }
#endif
{% endif %}
    {% if useHPT -%}
    // All "R" prescriptions are done at root when using HPTs
    // XXX - duplicate code (see _cncPrescribeF_*)
    place_t * _root_pl = (current_ws())->context->tuning_root
    {%- if not tuningInfo.isTuningGroup(stepfun) -%}
    {#-/* this gets you back to the non-tuning-tree */-#}
    ->tuning_place
    {%- endif %};
    async (_root_pl) IN({{ util.print_tag(stepfun.tag) }}ctx) {
        cncPrescribeT_{{stepfun.collName}}({{ util.print_tag(stepfun.tag) }}ctx);
    }
    {% else -%}
    cncPrescribeT_{{stepfun.collName}}({{ util.print_tag(stepfun.tag) }}ctx);
    {%- endif %}
}

{% if not isFinalizer %}
#ifdef HC_COMM
static void _cncPrescribeF_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True)
        }}{{g.name}}Ctx *ctx) {
    finish {
        {% if useHPT -%}
        // XXX - shouldn't need this --  can't I do this from the comm worker?
        // (i.e. put the xprescribe function's frame on the right deque)
        // All remote prescriptions are done at root when using HPTs
        place_t * _root_pl = (current_ws())->context->tuning_root
        {%- if not tuningInfo.isTuningGroup(stepfun) -%}
        {#-/* this gets you back to the non-tuning-tree */-#}
        ->tuning_place
        {%- endif %};
        async (_root_pl) IN({{ util.print_tag(stepfun.tag) }}ctx) {
            cncPrescribeT_{{stepfun.collName}}({{ util.print_tag(stepfun.tag) }}ctx);
        }
        {% else -%}
        async IN({{ util.print_tag(stepfun.tag) }}ctx) {
            cncPrescribeT_{{stepfun.collName}}({{ util.print_tag(stepfun.tag) }}ctx);
        }
        {%- endif %}
    }
}
#endif
{% endif %}

{% endfor %}

#ifdef HC_COMM
void hc_cnc_xprescribe_local(s32 coll, s32 *tag) {
    switch (coll) {
    {% for stepfun in tuningInfo.steplikes[1:] %}
        case {{ util.coll2id(stepfun.collName) }}: {
            _cncPrescribeF_{{stepfun.collName}}({% for x in stepfun.tag -%}
                tag[{{loop.index0}}], {% endfor %}{{ util.globalCtx(g) }});
            break;
        }
    {% endfor %}
        default:
            ASSERT(!"Unreachable");
    }
}

void hc_cnc_xprescribe_internal(void *msg) {
    s32 *xtag = msg;
    hc_cnc_xprescribe_local(*xtag, xtag+1);
}
#endif

void {{g.name}}_launch({{g.name}}Args *args, {{g.name}}Ctx *ctx) {
    // Set up Null DDF for conditional inputs
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

{% for vstep in tuningInfo.vSteps.values() -%}
// virtual step mapping
void cncPrescribeT_{{vstep.collName}}({{
        util.print_tag(vstep.tag, typed=True) }}{{g.name}}Ctx *ctx) {
    cncPrescribeT_{{vstep.mapTarget}}({{util.print_tag(vstep.mappedTag) }}ctx);
}
void cncPrescribeR_{{vstep.collName}}({{
        util.print_tag(vstep.tag, typed=True) }}{{g.name}}Ctx *ctx) {
    cncPrescribeR_{{vstep.mapTarget}}({{util.print_tag(vstep.mappedTag) }}ctx);
}
{% endfor %}

