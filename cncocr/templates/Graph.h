{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

{% set defname = "_CNCOCR_" ~ g.name.upper() ~ "_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#include "cncocr.h"
#include "{{g.name}}_defs.h"

/***************************\
 ******** CNC GRAPH ********
\***************************/
{#- /* TODO - Move this section into _external.h */ #}

typedef struct {{g.name}}Context {
    struct {
        cncHandle_t self;
        cncHandle_t finalizedEvent;
        cncHandle_t doneEvent;
        cncHandle_t awaitTag;
    } _guids;
    struct {
        {%- for i in g.concreteItems %}
        {{ ("cncItemCollection_t " if i.key else "DDF_t *") ~ i.collName }};
        {%- endfor %}
    } _items;
{%- for line in g.ctxParams %}
    {{ line }}
{%- endfor %}
} {{g.name}}Ctx;
{# /* TODO - Use a GUID instead of a pointer to the context */ #}
{{g.name}}Ctx *{{g.name}}_create();
void {{g.name}}_destroy({{g.name}}Ctx *context);

extern {{g.name}}Ctx *{{ util.globalCtx(g) }};
void {{g.name}}_startDaemons({{g.name}}Ctx * ctx);

#pragma hc continuable
void {{g.name}}_init({{g.name}}Args *args, {{g.name}}Ctx *ctx);
#pragma hc continuable
void {{g.name}}_launch({{g.name}}Args *args, {{g.name}}Ctx *ctx);

/****************************\
 ******** ITEM TYPES ********
\****************************/

{% for name, i in g.itemDeclarations.items() -%}
typedef {{i.type ~ name}}Item;
{% endfor %}
/**********************************\
 ******** ITEM KEY STRUCTS ********
\**********************************/

{% for name, i in g.itemDeclarations.items() if not i.isSingleton -%}
typedef struct { cncTag_t {{ i.key|join(", ") }}; } {{name}}ItemKey;
{% endfor %}
{% if g.externVms -%}
/****************************************\
 ******** ITEM MAPPING FUNCTIONS ********
\****************************************/

{% for i in g.externVms -%}
{{i.mapTarget}}ItemKey {{i.functionName}}({{
  util.print_tag(i.key, typed=True)
  }}{{g.name}}Ctx *ctx);
{% endfor %}
{% endif -%}
/*****************************\
 ******** ITEM CREATE ********
\*****************************/
{% for name, i in g.itemDeclarations.items() %}
cncHandle_t cncCreateItemSized_{{name}}({{i.type.ptrType}}*, size_t);
{% if i.type.isPtrType -%}
{# /* TODO - ADD NAMESPACE PREFIX DEFINE THING */ -#}
#define cncCreateItem_{{name}}(ptrptr, count) \
   cncCreateItemSized_{{name}}(ptrptr, sizeof(**(ptrptr)) * (count))
{% else -%}
#define cncCreateItem_{{name}}(ptrptr) \
   cncCreateItemSized_{{name}}(ptrptr, sizeof(**(ptrptr)))
{% endif -%}
{% endfor %}
/**************************\
 ******** ITEM PUT ********
\**************************/
{% for name, i in g.itemDeclarations.items() %}
{# /* TODO - ADD NAMESPACE PREFIX DEFINE THING */ -#}
void cncPutCheckedR_{{name}}(cncHandle_t handle, {{
        util.print_tag(i.key, typed=True)
        }}bool checkSingleAssignment, int srcRank, {{g.name}}Ctx *context);
#define cncPutChecked_{{name}}(handle, {{ util.print_tag(i.key) }}chk, context) \
 cncPutCheckedR_{{name}}(handle, {{ util.print_tag(i.key) }}chk, -1, context)
#define cncPut_{{name}}(handle, {{ util.print_tag(i.key) }}context) \
 cncPutChecked_{{name}}(handle, {{ util.print_tag(i.key) }}true, context)
{% endfor %}
/************************************\
 ******** STEP PRESCRIPTIONS ********
\************************************/

{% for stepfun in tuningInfo.steplikes -%}
{% if useHPT -%}
#pragma hc continuable
void cncPrescribeT_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True) }}{{g.name}}Ctx *ctx);
#pragma hc continuable
void cncPrescribeR_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True) }}{{g.name}}Ctx *ctx);
/* Normal prescribe is ignored for HPTs */
#define cncPrescribe_{{stepfun.collName}}({{ util.print_tag(stepfun.tag) }}ctx) do {} while (0)
{% else -%}
#pragma hc continuable
void cncPrescribe_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True) }}{{g.name}}Ctx *ctx);
{% endif -%}
{% endfor %}
{% if useHPT -%}
#define {{g.name}}_await(...) do {\
    {{g.name}}_init_tuning(args, ctx);\
    cncPrescribeT_{{g.finalizeFunction.collName}}(__VA_ARGS__);\
} while (0)
#pragma hc continuable
void {{g.name}}_init_tuning({{g.name}}Args *args, {{g.name}}Ctx *ctx);
{% else -%}
#define {{g.name}}_await cncPrescribe_{{g.finalizeFunction.collName}}
{% endif %}

{% for vstep in tuningInfo.vSteps.values() -%}
// virtual step mapping
#pragma hc continuable
void cncPrescribeT_{{vstep.collName}}({{
        util.print_tag(vstep.tag, typed=True) }}{{g.name}}Ctx *ctx);
#pragma hc continuable
void cncPrescribeR_{{vstep.collName}}({{
        util.print_tag(vstep.tag, typed=True) }}{{g.name}}Ctx *ctx);
{% endfor %}

#endif /*{{defname}}*/
