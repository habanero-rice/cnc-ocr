{% extends "_graph_ops.c" %}

{% block arch_itemcoll_init scoped -%}
{% for i in g.concreteItems -%}
{% if i.key -%}
context->_items.{{i.collName}} = calloc(CNC_TABLE_SIZE, sizeof(struct ItemCollEntry*));
{% else -%}
context->_items.{{i.collName}} = DDF_CREATE();
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_init %}

{% block arch_itemcoll_destroy -%}
{% for i in g.concreteItems -%}
{% if i.key -%}
hc_free(context->_items.{{i.collName}});
{% else -%}
//ocrEventDestroy(context->_items.{{i.collName}});
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_destroy %}
