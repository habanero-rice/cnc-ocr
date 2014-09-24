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
{% if logEnabled %}
    fprintf(stderr, "<#CNC_LOG#> {{msgType}} {{collName}} @ {{
            (['%lu'] * tag|count)|join(', ') if tag else 0 }}\n"{{
            ([""]+tag)|join(', ') }});
{% endif -%}
{%- endmacro %}

{#/****** Indent calling block to the specified level ******/#}
{% macro render_indented(level) -%}
{{ caller()|indent(width=4*level) }}
{%- endmacro %}

{#/****** Print all the components of a key or tag ******/#}
{% macro print_tag(tag, typed=False, prefix="") -%}
{% for x in tag %}{% if typed %}cncTag_t {% endif %}{{prefix ~ x}}, {% endfor -%}
{%- endmacro %}

{#/****** Print bindings for a list of items ******/#}
{% macro print_bindings(items, typed=False) -%}
{% for i in items %}
{%- if typed %}{{i.collName}}Item {{"*" * i.keyRanges|count}}{% endif -%}
{{i.binding}}, {% endfor -%}
{%- endmacro %}

{#/****** Print indices for an array access ******/#}
{% macro print_indices(xs) -%}
{% for x in xs %}[{{x}}]{% endfor -%}
{%- endmacro %}

{#/* TODO: There should be a way to combine the following two macros */#}

{#/****** For-loop nest for iterating over a multi-dimentional
          item array based on a ranged tag function ******/#}
{% macro render_tag_nest(comment, item, malloc=False) %}
{% set ranges = [] -%}
{% set stars = ("*" * item.keyRanges|count)|list -%}
{% macro iType() %}{{item.collName ~ "Item " ~ stars|join}}{% endmacro -%}
{% macro iVarIndexed() %}{{item.binding ~ ranges|join}}{% endmacro -%}
{% if malloc -%}
{{iType() ~ item.binding}};
{% endif -%}
{ // {{comment}}
{%- for k in item.key -%}
{% call render_indented(1 + ranges|count) -%}
{% set idx = "_i" ~ loop.index0 -%}
{% if k.isRanged %}{#/* Range */#}
s64 {{idx}};
{% if malloc -%}
{% do stars.pop() -%}
{{iVarIndexed()}} = MALLOC(sizeof({{iType()|trim}}) * {{k.sizeExpr}});
// XXX - This needs to get freed at some point
{% endif -%}
for ({{idx}} = 0; {{idx}} < {{k.sizeExpr}}; {{idx}}++) {
{%- do ranges.append("["~idx~"]") -%}
{%- else %}{#/* Scalar */#}
s64 {{idx}} = {{k.expr}};
{%- if malloc %} MAYBE_UNUSED({{idx}});{% endif %}
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
{% macro render_io_nest(comment, tag, bindings) %}
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
{%- for idx, x in ranges -%}
{% call render_indented(loop.index) %}
for ({{idx}} = 0; {{idx}} < {{x.sizeExpr}}; {{idx}}++) {
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
