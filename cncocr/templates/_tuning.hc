{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"

#pragma hc continuable
void {{g.name}}_init_tuning({{g.name}}Args *args, {{g.name}}Ctx *ctx) {
{% for output in tuningInfo.initTuning.outputs %}
{%- call util.render_indented(1) -%}
{%- set comment = "Prescribe \"" ~ output.collName ~ "\" steps" -%}
{%- set decl = tuningInfo.getFnDecl(output.collName) -%}
{%- call(args, ranges) util.render_io_nest(comment, output.tag, decl.tag) -%}
cncPrescribeR_{{output.collName}}({% for x in args %}{{x}}, {% endfor %}ctx);
{%- endcall -%}
{%- endcall %}
{% endfor %}
}

{% for groupfun in tuningInfo.tuningGroups.values() %}
#pragma hc continuable
void {{groupfun.collName}}({{ util.print_tag(groupfun.tag, typed=True) 
        }}{{ util.print_bindings(groupfun.inputs, typed=True)
        }}{{g.name}}Ctx *ctx) {
{% for output in groupfun.outputs %}
{%- call util.render_indented(1) -%}
{%- set comment = "Prescribe \"" ~ output.collName ~ "\" steps" -%}
{%- set decl = tuningInfo.getFnDecl(output.collName) -%}
{% set isGroup = tuningInfo.isTuningGroup(decl) -%}
{% set rangedOuts = groupfun.outputs|selectattr('tagRanges')|list -%}
{% if isGroup and rangedOuts %}
// DISTRIBUTE AMONG CHILDREN
{% set userDefinedDistribution = tuningInfo.stepHasDistFn(output.collName) -%}
{%- set inits = ["place_t **_kids = hc_get_current_place()->children;\n"] -%}
{% do inits.append("int _nKids =  hc_get_current_place()->nChildren;\n") -%}
{% if not userDefinedDistribution -%}
{% do inits.append("int _count = "~output.tagRanges[0].sizeExpr~";\n") -%}
{% do inits.append("int _chunk_size = _count / _nKids;\n") -%}
{% do inits.append("int _chunk_rem = _count % _nKids;\n") -%}
{% do inits.append("if (_chunk_rem > 0) { _chunk_size += 1; }\n") -%}
{% do inits.append("int _kidI = 0;\n") -%}
{% endif -%}{#/* not user-defined distribution */#}
{% do inits.append("int _currKid = 0;\n") -%}
{% set inits = "".join(inits) -%}
{%- call(args, ranges) util.render_io_nest(comment, output.tag, decl.tag, inits) -%}
{% if userDefinedDistribution -%}
// User-defined distribution
_currKid = {{ util.stepDistFn(decl, ranks="_nKids") }};
{% endif -%}{#/* user-defined distribution */-#}
async (_kids[_currKid]) IN({% for x in args %}{{x}}, {% endfor %}ctx) {
    cncPrescribeT_{{output.collName}}({% for x in args %}{{x}}, {% endfor %}ctx);
}
{% if not userDefinedDistribution -%}
// Default distribution
if (++_kidI > _chunk_size) {
    _kidI = 0;
    _kids++;
    if (--_chunk_rem == 0) { _chunk_size -= 1; }
}
{% endif -%}{#/* default distribution */#}
{%- endcall -%}
{% else -%}
{%- call(args, ranges) util.render_io_nest(comment, output.tag, decl.tag) -%}
{% if isGroup -%}
// PUSH DOWN
async (hc_get_child_place()->tuning_place)
{%- else -%}
// RELEASE HERE
async (hc_get_current_place())
{%- endif %} IN({% for x in args %}{{x}}, {% endfor %}ctx) {
    cncPrescribeT_{{output.collName}}({% for x in args %}{{x}}, {% endfor %}ctx);
}
{%- endcall -%}
{% endif -%}
{%- endcall %}
{% endfor %}

}
{% endfor %}

