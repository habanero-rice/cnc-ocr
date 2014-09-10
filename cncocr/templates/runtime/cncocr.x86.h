{% extends "runtime/cncocr.h" %}

{% block arch_typedefs -%}
typedef struct ItemCollEntry **cncItemCollection_t; // item collections
{% endblock arch_typedefs %}

{% block arch_compat_macros %}
#define MALLOC malloc
#define FREE free
#define MEMCPY memcpy
#define MEMCMP memcmp
{% endblock arch_compat_macros %}
