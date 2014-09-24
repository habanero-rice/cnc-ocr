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
        ocrGuid_t self;
        ocrGuid_t finalizedEvent;
        ocrGuid_t doneEvent;
        ocrGuid_t awaitTag;
    } _guids;
    struct {
        {%- for i in g.concreteItems %}
        {{ ("cncItemCollection_t " if i.key else "cncHandle_t ") ~ i.collName }};
        {%- endfor %}
    } _items;
    struct {
        {%- for s in g.finalAndSteps %}
        ocrGuid_t {{s.collName}};
        {%- endfor %}
    } _steps;
{%- for line in g.ctxParams %}
    {{ line }}
{%- endfor %}
} {{g.name}}Ctx;
{# /* TODO - Use a GUID instead of a pointer to the context */ #}
{{g.name}}Ctx *{{g.name}}_create();
void {{g.name}}_destroy({{g.name}}Ctx *context);

void {{g.name}}_launch({{g.name}}Args *args, {{g.name}}Ctx *ctx);
void {{g.name}}_await({{
        util.print_tag(g.finalizeFunction.tag, typed=True)
        }}{{g.name}}Ctx *context);

/****************************\
 ******** ITEM TYPES ********
\****************************/

{% for name, i in g.itemDeclarations.items() -%}
typedef struct { {{i.type}}item; cncHandle_t handle; } {{name}}Item;
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
cncHandle_t cncCreateItemSized_{{name}}({{i.type.ptrType}}*item, size_t size);
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
void cncPrescribe_{{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True) }}{{g.name}}Ctx *ctx);
{% endfor %}
#endif /*{{defname}}*/
