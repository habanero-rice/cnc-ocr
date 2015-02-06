{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"

{{g.name}}Ctx *{{ util.globalCtx(g) }};

#ifdef HC_COMM
extern void {{g.name}}_startItemCollDaemons({{g.name}}Ctx * ctx);

void {{g.name}}_startDaemons({{g.name}}Ctx * ctx) {
    {{g.name}}_startItemCollDaemons(ctx);
    hc_mpi_cnc_sc_daemons({{
           g.finalAndSteps|map(attribute="tag")|map("count")|sort|last
           }});
}
#endif

{{g.name}}Ctx *{{g.name}}_create() {
{% if logEnabled %}
    // init debug logger (only once)
    if (!cncDebugLog) {
        const char *logPath = getenv("CNC_LOG");
        if (!logPath) logPath = "./cnc_events.log";
        cncDebugLog = fopen(logPath ,"w");
    }
{% endif -%}
    // allocate the context datablock
    {{g.name}}Ctx *context = hc_malloc(sizeof(*context));
    // store a copy of its guid inside
    //context->_guids.self = contextGuid;
    // initialize graph events
    context->_guids.finalizedEvent = NULL;
    context->_guids.doneEvent = NULL;
    context->_guids.awaitTag = NULL;
    // initialize item collections
    {% call util.render_indented(1) -%}
{% block arch_itemcoll_init scoped -%}
{% endblock arch_itemcoll_init -%}
    {% endcall %}
    // 
    {{ util.globalCtx(g) }} = context;
    return context;
}

void {{g.name}}_destroy({{g.name}}Ctx *context) {
    hc_free(context->_guids.finalizedEvent);
    hc_free(context->_guids.doneEvent);
    // destroy item collections
    // XXX - need to do a deep free by traversing the table
    {% call util.render_indented(1) -%}
{% block arch_itemcoll_destroy -%}
{% endblock arch_itemcoll_destroy -%}
    {% endcall -%}
    //ocrDbDestroy(context->_guids.self);
}

//
// Black magic for invoking HC code
//

#ifdef HC_COMM
#include "hc.h"
// Rose-generated grossness
typedef struct __hc_hc_cnc_xprescribe_internal__frame_t__ {
  struct hc_frameHeader header;
  s32 *xtag;
  void *msg;
} HC_PFrame;
void __hc_hc_cnc_xprescribe_internal__(struct hc_workerState *ws,struct hc_frameHeader *__hc_frame__,int __hc_pc__);

void hc_cnc_xprescribe(void *msg) {
    struct hc_workerState *ws = current_ws();
    HC_PFrame *f = hc_init_susp_mth_frame_ws(ws, sizeof(HC_PFrame), __hc_hc_cnc_xprescribe_internal__);
    f->msg = msg;
    deque_push_default(f);
}
#endif
