{% import "common_macros.inc.c" as util with context -%}

{% set defname = "_CNCOCR_" ~ g.name.upper() ~ "_TYPES_H_" -%}
#ifndef {{defname}}
#define {{defname}}

#include "{{g.name}}.h"

{% for i in g.concreteItems -%}
static inline int cncItemSize_{{i.collName}}({{g.name}}Ctx *ctx) {
    return sizeof({{i.type.baseType}});
}
{% endfor %}
#endif /*{{defname}}*/
