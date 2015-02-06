{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

{% set defname = "_CNCOCR_" ~ g.name.upper() ~ "_INTERNAL_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#include "{{g.name}}.h"
#include "cncocr_internal.h"

#define CNC_SHUTDOWN_TAG 32323

/******************************\
 ******** ITEM GETTERS ********
\******************************/

{% for name, i in g.itemDeclarations.items() %}
DDF_t *cncGet_{{name}}({{ util.print_tag(i.key, typed=True) }}{{g.name}}Ctx *context);
{% endfor %}

/********************************\
 ******** STEP FUNCTIONS ********
\********************************/

{% for stepfun in tuningInfo.steplikes %}

#pragma hc continuable
void {{stepfun.collName}}({{
        util.print_tag(stepfun.tag, typed=True) ~
        util.print_bindings(stepfun.inputs, typed=True)
        }}{{g.name}}Ctx *ctx);
{% endfor %}
#endif /*{{defname}}*/
