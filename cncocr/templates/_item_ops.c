{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"

{% for i in g.itemDeclarations.values() %}
/* {{i.collName}} */

cncHandle_t cncCreateItemSized_{{i.collName}}({{i.type.ptrType}}*item, size_t size) {
    cncHandle_t handle;
    CNC_CREATE_ITEM(&handle, (void**)item, size);
    return handle;
}

void cncPutChecked_{{i.collName}}(cncHandle_t handle, {{
        util.print_tag(i.key, typed=True)
        }}bool checkSingleAssignment, {{g.name}}Ctx *ctx) {
    {% if not i.isVirtual -%}
    {#/*****NON-VIRTUAL*****/-#}
    {% if i.key -%}
    cncTag_t tag[] = { {{i.key|join(", ")}} };
    _cncPut(handle, (unsigned char*)tag, sizeof(tag), ctx->_items.{{i.collName}}, checkSingleAssignment);
    {%- else -%}
    _cncPutSingleton(handle, ctx->_items.{{i.collName}}, checkSingleAssignment);
    {%- endif %}
    {%- else -%}
    {% set targetColl = g.itemDeclarations[i.mapTarget] -%}
    {% if i.isInline -%}
    {#/*****INLINE VIRTUAL*****/-#}
    cncPutChecked_{{i.mapTarget}}(handle, {{
        util.print_tag(i.keyFunction)
        }}checkSingleAssignment, ctx);
    {%- else -%}
    {#/*****EXTERN VIRTUAL******/-#}
    {{i.mapTarget}}ItemKey _key = {{i.functionName}}({{
        util.print_tag(i.key) }}ctx);
    cncPutChecked_{{i.mapTarget}}(handle, {{
        util.print_tag(targetColl.key, prefix="_key.")
        }}checkSingleAssignment, ctx);
    {%- endif %}
    {%- endif %}
}

void cncGet_{{i.collName}}({{ util.print_tag(i.key, typed=True) }}ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, {{g.name}}Ctx *ctx) {
    {% if not i.isVirtual -%}
    {#/*****NON-VIRTUAL*****/-#}
    {% if i.key -%}
    cncTag_t tag[] = { {{i.key|join(", ")}} };
    return _cncGet((unsigned char*)tag, sizeof(tag), destination, slot, mode, ctx->_items.{{i.collName}});
    {%- else -%}
    return _cncGetSingleton(destination, slot, mode, ctx->_items.{{i.collName}});
    {%- endif %}
    {%- else -%}
    {% set targetColl = g.itemDeclarations[i.mapTarget] -%}
    {% if i.isInline -%}
    {#/*****INLINE VIRTUAL*****/-#}
    cncGet_{{i.mapTarget}}({{
        util.print_tag(i.keyFunction)
        }}destination, slot, mode, ctx);
    {%- else -%}
    {#/*****EXTERN VIRTUAL******/-#}
    {{i.mapTarget}}ItemKey _key = {{i.functionName}}({{
        util.print_tag(i.key) }}ctx);
    cncGet_{{i.mapTarget}}({{
        util.print_tag(targetColl.key, prefix="_key.")
        }}destination, slot, mode, ctx);
    {%- endif %}
    {%- endif %}
}

{% endfor %}
