{% extends "_graph_ops.c" %}

{% block arch_itemcoll_init scoped -%}
{% for i in g.concreteItems -%}
{% if i.key -%}
context->_items.{{i.collName}} = calloc(CNC_TABLE_SIZE, sizeof(struct ItemCollEntry*));
{% else -%}
ocrEventCreate(&context->_items.{{i.collName}}, OCR_EVENT_IDEM_T, true);
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_init %}

{% block arch_itemcoll_destroy -%}
{% for i in g.concreteItems -%}
{% if i.key -%}
FREE(context->_items.{{i.collName}});
{% else -%}
ocrEventDestroy(context->_items.{{i.collName}});
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_destroy %}
