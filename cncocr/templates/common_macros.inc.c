{#/****** Warning banner for auto-generated files ******/#}
{% macro auto_file_banner() -%}
/**********************************************\
 *  WARNING: AUTO-GENERATED FILE!             *
 *  This file WILL BE OVERWRITTEN on each     *
 *  invocation of the graph translator tool.  *
\**********************************************/
{%- endmacro %}


{#/****** Indent calling block to the specified level ******/#}
{% macro log_msg(msgType, collName, tag) -%}
    LOG_INFO("{{msgType}} {{collName}} @ {{
            (['%ld'] * tag|count)|join(', ') if tag else 0 }}\n"{{
            ([""] + tag|list)|join(', ') }});
{%- endmacro %}

{#/****** Indent calling block to the specified level ******/#}
{% macro render_indented(level) -%}
{{ caller()|indent(width=4*level) }}
{%- endmacro %}

{#/****** Print all the components of a key or tag ******/#}
{% macro print_tag(tag, typed=False, prefix="") -%}
{% for x in tag %}{% if typed %}cncTag_t {% endif %}{{prefix ~ x}}, {% endfor -%}
{%- endmacro %}

{#/****** Print ranged type for item collection ******/#}
{% macro ranged_type(item) -%}
{{item.collName}}Item {{"*" * item.keyRanges|count}}
{%- endmacro %}

{#/****** Print bindings for a list of items ******/#}
{% macro print_bindings(items, typed=False) -%}
{% for i in items %}
{%- if typed %}{{ ranged_type(i) }}{% endif -%}
{{i.binding}}, {% endfor -%}
{%- endmacro %}

{#/****** Print indices for an array access ******/#}
{% macro print_indices(xs) -%}
{% for x in xs %}[{{x}}]{% endfor -%}
{%- endmacro %}

{#/****** For-loop nest for iterating over a multi-dimentional
          item array based on a ranged tag function ******/#}
{% macro render_hc_gets_nest(comment, item) %}
{% set ranges = [] -%}
{% set indices = [] -%}
{% macro iVarIndexed() %}{{item.binding ~ ranges|join}}{% endmacro -%}
DDF_list_t *{{item.binding}} = DDF_LIST_CREATE();
{ // {{comment}}
{%- for k in item.key -%}
{% set idx = "_i" ~ loop.index0 -%}
{%- do indices.append(idx~", ") -%}
{% call render_indented(1 + ranges|count) -%}
{% if k.isRanged %}{#/* Range */#}
s64 {{idx}};
for ({{idx}} = 0; {{idx}} < {{k.sizeExpr}}; {{idx}}++) {
{%- do ranges.append(idx~", ") -%}
{%- else %}{#/* Scalar */#}
s64 {{idx}} = {{k.expr}};
{%- endif -%}
{%- endcall -%}
{%- endfor -%}
{%- call render_indented(1 + ranges|count) %}
DDF_LIST_ADD(cncGet_{{item.collName}}({{ indices|join }}ctx), {{item.binding}});
{%- endcall -%}
{%- for r in item.keyRanges -%}
{% call render_indented(1 + loop.revindex0) %}
}
{%- endcall -%}
{%- endfor %}
}
{%- endmacro %}

{#/* TODO: There should be a way to combine the following two macros
     (especially now since I lifted out the memory allocation stuff) */#}
{#/****** For-loop nest for iterating over a multi-dimentional
          item array based on a ranged tag function ******/#}
{% macro render_tag_nest(comment, item) %}
{% set ranges = [] -%}
{% macro iVarIndexed() %}{{item.binding ~ ranges|join}}{% endmacro -%}
{ // {{comment}}
{%- for k in item.key -%}
{% call render_indented(1 + ranges|count) -%}
{% set idx = "_i" ~ loop.index0 -%}
{% if k.isRanged %}{#/* Range */#}
s64 {{idx}};
for ({{idx}} = 0; {{idx}} < {{k.sizeExpr}}; {{idx}}++) {
{%- do ranges.append("["~idx~"]") -%}
{%- else %}{#/* Scalar */#}
s64 {{idx}} = {{k.expr}};
{%- endif -%}
{%- endcall -%}
{%- endfor -%}
{% set content = caller(iVarIndexed()) -%}
{%- call render_indented(1 + ranges|count) %}
{{ content }}
{%- endcall -%}
{%- for r in item.keyRanges -%}
{% call render_indented(1 + loop.revindex0) %}
}
{%- endcall -%}
{%- endfor %}
}
{%- endmacro %}

{#/****** For-loop nest for iterating over a multi-dimentional
          item array based on a ranged tag function ******/#}
{% macro render_io_nest(comment, tag, bindings, initStatements="") %}
{% set ranges = [] -%}
{% set args = [] -%}
{%- for x in tag -%}
{% if x.isRanged %}{#/* Range */#}
{%- set idx = "_" ~ bindings[loop.index0] -%}
{%- do ranges.append([idx, x]) -%}
{%- do args.append(idx) -%}
{%- else %}{#/* Scalar */#}
{%- do args.append(x.expr) -%}
{%- endif -%}
{%- endfor -%}
{% if ranges -%}
{ // {{comment}}
    s64 {{ranges|join(", ", attribute=0)}};
{%- if initStatements %}
{%- call render_indented(1) %}
{{ initStatements }}
{%- endcall -%}
{%- endif -%}
{%- for idx, x in ranges -%}
{% call render_indented(loop.index) %}
for ({{idx}} = {{x.start}}; {{idx}} < {{x.end}}; {{idx}}++) {
{%- endcall -%}
{%- endfor -%}
{% set content = caller(args, ranges|map('first')|list) -%}
{%- call render_indented(1 + ranges|count) %}
{{ content }}
{%- endcall -%}
{%- for x in ranges -%}
{% call render_indented(1 + loop.revindex0) %}
}
{%- endcall -%}
{%- endfor %}
}
{%- else -%}
// {{comment}}
{{ caller(args, ranges) }}
{% endif -%}
{%- endmacro %}

{% macro coll2id(collName) -%}
{{ collName | upper }}_COLL_ID
{%- endmacro -%}

{% macro globalCtx(g) -%}
{{ g.name | upper }}_GLOBAL_CNC_CONTEXT
{%- endmacro -%}

{% macro stepDistFn(s, ranks="HCMPI_COMM_SIZE") -%}
{{ tuningInfo.stepDistFn(s.collName, coll2id(s.collName), ranks) }}
{%- endmacro -%}

{% macro itemDistFn(i, ranks="HCMPI_COMM_SIZE") -%}
{{ tuningInfo.itemDistFn(i.collName, coll2id(i.collName), ranks) }}
{%- endmacro -%}

