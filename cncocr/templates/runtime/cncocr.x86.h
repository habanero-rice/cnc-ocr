{% extends "runtime/cncocr.h" %}

{% block arch_typedefs -%}
typedef struct ItemCollEntry **cncItemCollection_t; // item collections
{% endblock arch_typedefs %}

{% block arch_compat_macros %}
//#define MALLOC malloc
//#define FREE free
{% endblock arch_compat_macros %}
