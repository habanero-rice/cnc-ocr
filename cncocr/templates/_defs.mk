##############################################
#  WARNING: AUTO-GENERATED FILE!             #
#  This file WILL BE OVERWRITTEN on each     #
#  invocation of the graph translator tool.  #
##############################################

CNC_STEP_SRCS := {% for s in g.stepFunctions %}{{ g.name ~ "_" ~ s ~ ".hc" }} {% endfor -%}
{% if useHPT %} cncocr_support/{{g.name}}_tuning.hc {% endif %}

{% if logEnabled %}
# single worker when logging
CFG_NAME ?= mach-hc-1w.cfg
{% endif %}

{% if useHPT -%}
HPTDEF := -DHC_TUNING

{#
INSZ=500
TSZ=50
INFILE=/projects/vs3/cholesky-input/m_$(INSZ).in
#}

POLICY=-hf
BIND=--bind ./hpt/bind-davinci.txt
HPT=--hpt ./hpt/hpt-davinci-comm.xml
HPT_ARGS := $(POLICY) $(BIND) $(HPT)
{%- endif %}

{% block additional_defs %}{% endblock additional_defs %}
