{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"

{% if logEnabled %}
#ifndef CNCOCR_x86
#error "Debug logging mode only supported on x86 targets"
#endif
#include <pthread.h>
pthread_mutex_t _cncDebugMutex = PTHREAD_MUTEX_INITIALIZER;
{% endif -%}

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
    ocrGuid_t contextGuid;
    {{g.name}}Ctx *context;
    SIMPLE_DBCREATE(&contextGuid, (void**)&context, sizeof(*context));
    // store a copy of its guid inside
    context->_guids.self = contextGuid;
    // initialize graph events
    ocrEventCreate(&context->_guids.finalizedEvent, OCR_EVENT_STICKY_T, true);
    ocrEventCreate(&context->_guids.doneEvent, OCR_EVENT_STICKY_T, true);
    ocrEventCreate(&context->_guids.awaitTag, OCR_EVENT_ONCE_T, true);
    // initialize item collections
    {% call util.render_indented(1) -%}
{% block arch_itemcoll_init scoped -%}
s32 i;
ocrGuid_t *itemTable;
{% for i in g.concreteItems -%}
{% if i.key -%}
SIMPLE_DBCREATE(&context->_items.{{i.collName}}, (void**)&itemTable, sizeof(ocrGuid_t) * CNC_TABLE_SIZE);
for (i=0; i<CNC_TABLE_SIZE; i++) {
    ocrGuid_t *_ptr;
    // Add one level of indirection to help with contention
    SIMPLE_DBCREATE(&itemTable[i], (void**)&_ptr, sizeof(ocrGuid_t));
    *_ptr = NULL_GUID;
    ocrDbRelease(itemTable[i]);
}
ocrDbRelease(context->_items.{{i.collName}});
{% else -%}
ocrEventCreate(&context->_items.{{i.collName}}, OCR_EVENT_IDEM_T, true);
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_init -%}
    {% endcall %}
    // initialize step collections
    {% for s in g.finalAndSteps -%}
    ocrEdtTemplateCreate(&context->_steps.{{s.collName}},
            _cncStep_{{s.collName}}, EDT_PARAM_UNK, EDT_PARAM_UNK);
    {% endfor -%}
    return context;
}

void {{g.name}}_destroy({{g.name}}Ctx *context) {
    ocrEventDestroy(context->_guids.finalizedEvent);
    ocrEventDestroy(context->_guids.doneEvent);
    // destroy item collections
    // XXX - need to do a deep free by traversing the table
    {% call util.render_indented(1) -%}
{% block arch_itemcoll_destroy -%}
{% for i in g.concereteItems -%}
{% if i.key -%}
ocrDbDestroy(context->_items.{{i.collName}});
{% else -%}
ocrEventDestroy(context->_items.{{i.collName}});
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_destroy -%}
    {% endcall -%}
    // destroy step collections
    {% for s in g.finalAndSteps -%}
    ocrEdtTemplateDestroy(context->_steps.{{s.collName}});
    {% endfor -%}
    ocrDbDestroy(context->_guids.self);
}

static ocrGuid_t _emptyEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    return NULL_GUID;
}

static ocrGuid_t _graphFinishEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    {{g.name}}Args *args = depv[0].ptr;
    {{g.name}}Ctx *context = depv[1].ptr;
    // XXX - just do finalize from within the finish EDT
    // The graph isn't done until the finalizer runs as well,
    // so we need to make a dummy EDT depending on the
    // finalizer's output event.
    ocrGuid_t emptyEdtGuid, templGuid;
    ocrEdtTemplateCreate(&templGuid, _emptyEdt, 0, 1);
    ocrEdtCreate(&emptyEdtGuid, templGuid,
        /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
        /*depc=*/EDT_PARAM_DEF, /*depv=*/&context->_guids.finalizedEvent,
        /*properties=*/EDT_PROP_NONE,
        /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
    // XXX - destroying this template caused crash on FSim
    //ocrEdtTemplateDestroy(templGuid);
    // Start graph execution
    {{ util.step_enter() }}
    {{g.name}}_init(args, context);
    {{ util.step_exit() }}
    if (args) ocrDbDestroy(depv[0].guid);
    return NULL_GUID;
}

static ocrGuid_t _finalizerEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    {{g.name}}Ctx *context = depv[0].ptr;
    cncTag_t *tag = depv[1].ptr; MAYBE_UNUSED(tag);
    cncPrescribe_{{g.finalizeFunction.collName}}(
        {%- for x in g.finalizeFunction.tag %}tag[{{loop.index0}}], {% endfor -%}
        context);
    // XXX - for some reason this causes a segfault?
    //ocrDbDestroy(depv[1].guid);
    return NULL_GUID;
}

void {{g.name}}_launch({{g.name}}Args *args, {{g.name}}Ctx *context) {
    {{g.name}}Args *argsCopy;
    ocrGuid_t graphEdtGuid, finalEdtGuid, edtTemplateGuid, outEventGuid, argsDbGuid;
    ocrDbRelease(context->_guids.self);
    // copy the args struct into a data block
    // TODO - I probably need to free this sometime
    if (sizeof(*args) > 0) {
        SIMPLE_DBCREATE(&argsDbGuid, (void**)&argsCopy, sizeof(*args));
        *argsCopy = *args;
        ocrDbRelease(argsDbGuid);
    }
    // Don't need to copy empty args structs
    else {
        argsDbGuid = NULL_GUID;
    }
    // create a finish EDT for the CnC graph
    ocrEdtTemplateCreate(&edtTemplateGuid, _graphFinishEdt, 0, 2);
    ocrEdtCreate(&graphEdtGuid, edtTemplateGuid,
        /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
        /*depc=*/EDT_PARAM_DEF, /*depv=*/NULL,
        /*properties=*/EDT_PROP_FINISH,
        /*affinity=*/NULL_GUID, /*outEvent=*/&outEventGuid);
    ocrEdtTemplateDestroy(edtTemplateGuid);
    // hook doneEvent into the graph's output event
    ocrAddDependence(outEventGuid, context->_guids.doneEvent, 0, DB_DEFAULT_MODE);
    // set up the finalizer
    ocrEdtTemplateCreate(&edtTemplateGuid, _finalizerEdt, 0, 2);
    ocrGuid_t deps[] = { context->_guids.self, context->_guids.awaitTag };
    ocrEdtCreate(&finalEdtGuid, edtTemplateGuid,
        /*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
        /*depc=*/EDT_PARAM_DEF, /*depv=*/deps,
        /*properties=*/EDT_PROP_NONE,
        /*affinity=*/NULL_GUID, /*outEvent=*/NULL);
    ocrEdtTemplateDestroy(edtTemplateGuid);
    // start the graph execution
    ocrAddDependence(argsDbGuid, graphEdtGuid, 0, DB_DEFAULT_MODE);
    ocrAddDependence(context->_guids.self, graphEdtGuid, 1, DB_DEFAULT_MODE);
}

void {{g.name}}_await({{
        util.print_tag(g.finalizeFunction.tag, typed=True)
        }}{{g.name}}Ctx *ctx) {
    // Can't launch the finalizer EDT from within the finish EDT,
    // so we copy the tag information into a DB and do it indirectly.
    {% if g.finalizeFunction.tag -%}
    cncTag_t *_tagPtr;
    ocrGuid_t _tagGuid;
    int _i = 0;
    SIMPLE_DBCREATE(&_tagGuid, (void**)&_tagPtr, sizeof(cncTag_t) * {{ g.finalizeFunction.tag|count}});
    {% for x in g.finalizeFunction.tag -%}
    _tagPtr[_i++] = {{x}};
    {% endfor -%}
    ocrDbRelease(_tagGuid);
    {% else -%}
    ocrGuid_t _tagGuid = NULL_GUID;
    {% endif -%}
    ocrEventSatisfy(ctx->_guids.awaitTag, _tagGuid);
}

/* define NO_CNC_MAIN if you want to use mainEdt as the entry point instead */
#ifndef NO_CNC_MAIN

extern int cncMain(int argc, char *argv[]);

#pragma weak mainEdt
ocrGuid_t mainEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    // Unpack argc and argv (passed thru from mainEdt)
    int i, argc = OCR_MAIN_ARGC;
    char **argv = cncMalloc(sizeof(char*)*argc);
    for (i=0; i<argc; i++) argv[i] = OCR_MAIN_ARGV(i);
    // Run user's cncEnvIn function
    cncMain(argc, argv);
    cncFree(argv);
    return NULL_GUID;
}

#endif /* NO_CNC_MAIN */

