{% extends "_graph_ops.c" %}

{% block arch_itemcoll_init scoped -%}
{% for name, i in g.itemDeclarations.items() -%}
{% if i.key -%}
context->_items.{{name}} = calloc(CNC_TABLE_SIZE, sizeof(struct ItemCollEntry*));
{% else -%}
ocrEventCreate(&context->_items.{{name}}, OCR_EVENT_STICKY_T, true);
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_init %}

{% block arch_itemcoll_destroy -%}
{% for name, i in g.itemDeclarations.items() -%}
{% if i.key -%}
FREE(context->_items.{{name}});
{% else -%}
ocrEventDestroy(context->_items.{{name}});
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_destroy %}
