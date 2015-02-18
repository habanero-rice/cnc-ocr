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
    fprintf(cncDebugLog, "{{msgType}} {{collName}} @ {{
            (['%ld'] * tag|count)|join(', ') if tag else 0 }}\n"{{
            ([""] + tag|list)|join(', ') }});
    fflush(cncDebugLog);
{% elif traceEnabled %}
    PRINTF("<<CnC Trace>>: {{msgType}} {{collName}} @ {{
           (['%ld'] * tag|count)|join(', ') if tag else 0 }}\n"{{
           ([""] + tag|list)|join(', ') }});
{% endif %}
{%- endmacro %}

{#/****** CnC Item Create call + variable declaration ******/#}
{% macro item_create_statement(itemcoll, varname) -%}
{% set suffix = "Vector" if itemcoll.type.isVecType else "" -%}
{% set count = "/*TODO: count=*/1" if itemcoll.type.isVecType else "" -%}
{% set vecSize = itemcoll.type.vecSize or count -%}
{{itemcoll.type.ptrType ~ varname}} = cncCreateItem{{suffix}}_{{
    itemcoll.collName}}({{vecSize}});
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
{{ g.lookupType(item)
 }}{{ ("*" * item.keyRanges|count) }}
{%- endmacro %}

{#/****** Print bindings for a list of items ******/#}
{% macro print_bindings(items, typed=False) -%}
{% for i in items %}
{%- if typed %}{{ ranged_type(i) }}{% endif -%}
{{ i.binding}}, {% endfor -%}
{%- endmacro %}

{#/****** Print indices for an array access ******/#}
{% macro print_indices(xs) -%}
{% for x in xs %}[{{x}}]{% endfor -%}
{%- endmacro %}

{#/****** Print indices for an array access ******/#}
{% macro range_cmp_op(r) -%}
{{ "<=" if r.inclusive else "<" }}
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
for ({{idx}} = {{k.start}}; {{idx}} {{range_cmp_op(k)}} {{k.end}}; {{idx}}++) {
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
{% macro render_io_nest(comment, tag, bindings, zeroBased=False) %}
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
{% set startVal = 0 if zeroBased else x.start -%}
{% set endVal = x.upperLoopBound if zeroBased else x.end -%}
for ({{idx}} = {{startVal}}; {{idx}} {{range_cmp_op(x)}} {{endVal}}; {{idx}}++) {
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

{#/* Scaffolding code generation for step inputs */#}
{% macro step_input_scaffolding(stepfun, indent=1) %}
{% set rangedInputs = stepfun.inputs|selectattr('keyRanges')|list -%}
{% if rangedInputs %}
    //
    // INPUTS
    //
{% for input in rangedInputs -%}
{%- set comment = "Access \"" ~ input.binding ~ "\" inputs" -%}
{%- set decl = g.itemDeclarations[input.collName] -%}
{%- call util.render_indented(1) -%}
{%- call(args, ranges) util.render_io_nest(comment, input.key, decl.key, zeroBased=True) -%}
{%- set var = input.binding ~ util.print_indices(ranges) -%}
/* TODO: Do something with {{var}} */
{%- endcall -%}
{%- endcall %}
{% endfor %}
{% endif %}
{%- endmacro %}

{% macro step_enter() -%}
{% if logEnabled %}pthread_mutex_lock(&_cncDebugMutex);{% endif %}
{%- endmacro %}
{% macro step_exit() -%}
{% if logEnabled %}pthread_mutex_unlock(&_cncDebugMutex);{% endif %}
{%- endmacro %}
