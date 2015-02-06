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
{%- call(args, ranges) util.render_io_nest(comment, output.tag, decl.tag) -%}


cncPrescribeT_{{output.collName}}({% for x in args %}{{x}}, {% endfor %}ctx);


{%- endcall -%}
{%- endcall %}
{% endfor %}

}
{% endfor %}

