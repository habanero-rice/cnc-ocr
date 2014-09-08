##############################################
#  WARNING: AUTO-GENERATED FILE!             #
#  This file WILL BE OVERWRITTEN on each     #
#  invocation of the graph translator tool.  #
##############################################

STEP_SRCS={% for s in g.stepFunctions %}{{ g.name ~ "_" ~ s ~ ".c" }} {% endfor %}
