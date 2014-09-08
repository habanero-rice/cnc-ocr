{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"

{% for name, i in g.itemDeclarations.items() %}
/* {{name}} */

cncHandle_t cncCreateItemSized_{{name}}({{i.type.ptrType}}*item, size_t size) {
    cncHandle_t handle;
    CNC_CREATE_ITEM(&handle, (void**)item, size);
    return handle;
}

void cncPutChecked_{{name}}(cncHandle_t handle, {{
        util.print_tag(i.key, typed=True)
        }}bool checkSingleAssignment, {{g.name}}Ctx *context) {
    {% if i.key -%}
    cncTag_t tag[] = { {{i.key|join(", ")}} };
    _cncPut(handle, (unsigned char*)tag, sizeof(tag), context->_items.{{name}}, checkSingleAssignment);
    {%- else -%}
    _cncPutSingleton(handle, context->_items.{{name}}, checkSingleAssignment);
    {%- endif %}
}

void cncGet_{{name}}({{ util.print_tag(i.key, typed=True) }}ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, {{g.name}}Ctx *context) {
    {% if i.key -%}
    cncTag_t tag[] = { {{i.key|join(", ")}} };
    return _cncGet((unsigned char*)tag, sizeof(tag), destination, slot, mode, context->_items.{{name}});
    {%- else -%}
    return _cncGetSingleton(destination, slot, mode, context->_items.{{name}});
    {%- endif %}
}

{% endfor %}
