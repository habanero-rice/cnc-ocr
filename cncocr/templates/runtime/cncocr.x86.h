{% extends "runtime/cncocr.h" %}

{% block arch_includes -%}
{#/* XXX x86-only */-#}
#include <stdlib.h>
{% if logEnabled -%}
#include <stdio.h>
{% endif -%}
{% endblock arch_includes %}

{% block arch_typedefs -%}
typedef struct ItemCollEntry **cncItemCollection_t; // item collections
{% endblock arch_typedefs %}

{% block arch_compat_macros %}
#define MALLOC malloc
#define FREE free
#define MEMCMP memcmp
{% endblock arch_compat_macros %}
