##############################################
#  WARNING: AUTO-GENERATED FILE!             #
#  This file WILL BE OVERWRITTEN on each     #
#  invocation of the graph translator tool.  #
##############################################

CNC_STEP_SRCS := {% for s in g.stepFunctions %}{{ g.name ~ "_" ~ s ~ ".c" }} {% endfor %}
{% if logEnabled %}
# single worker when logging
CFG_NAME ?= mach-hc-1w.cfg
{% endif %}
{% block additional_defs %}{% endblock additional_defs %}
