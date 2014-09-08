{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

{% set defname = "_CNCOCR_" ~ g.name.upper() ~ "_INTERNAL_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#include "{{g.name}}.h"
#include "cncocr_internal.h"

/******************************\
 ******** ITEM GETTERS ********
\******************************/

{% for name, i in g.itemDeclarations.items() %}
void cncGet_{{name}}({{ util.print_tag(i.key, typed=True) }}ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, {{g.name}}Ctx *context);
{% endfor %}

/********************************\
 ******** STEP FUNCTIONS ********
\********************************/

void {{g.name}}_init({{g.name}}Args *args, {{g.name}}Ctx *ctx);
{% for stepfun in g.finalAndSteps %}
void {{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True) ~
        util.print_bindings(stepfun.inputs, typed=True)
        }}{{g.name}}Ctx *ctx);
ocrGuid_t _cncStep_{{stepfun.collName}}(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]);
{% endfor %}
#endif /*{{defname}}*/
