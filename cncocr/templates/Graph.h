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
void cncPutChecked_{{name}}(cncHandle_t handle, {{
        util.print_tag(i.key, typed=True)
        }}bool checkSingleAssignment, {{g.name}}Ctx *context);
#define cncPut_{{name}}(handle, {{ util.print_tag(i.key) }}context) \
 cncPutChecked_{{name}}(handle, {{ util.print_tag(i.key) }}true, context)
{% endfor %}
/************************************\
 ******** STEP PRESCRIPTIONS ********
\************************************/

{% for stepfun in g.finalAndSteps -%}
#pragma hc continuable
void cncPrescribeT_{{stepfun.collName}}(void *args);
#pragma hc continuable
void cncPrescribeR_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True) }}{{g.name}}Ctx *ctx);
#pragma hc continuable
void cncPrescribe_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True) }}{{g.name}}Ctx *ctx);
{% endfor %}
#define {{g.name}}_await cncPrescribe_{{g.finalizeFunction.collName}}

#endif /*{{defname}}*/
