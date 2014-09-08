{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"

{{g.name}}Ctx *{{g.name}}_create() {
    // allocate the context datablock
    ocrGuid_t contextGuid;
    {{g.name}}Ctx *context;
    CNC_CREATE_ITEM(&contextGuid, (void**)&context, sizeof(*context));
    // store a copy of its guid inside
    context->_guids.self = contextGuid;
    // initialize graph events
    ocrEventCreate(&context->_guids.finalizedEvent, OCR_EVENT_ONCE_T, true);
    ocrEventCreate(&context->_guids.doneEvent, OCR_EVENT_ONCE_T, true);
    ocrEventCreate(&context->_guids.awaitTag, OCR_EVENT_ONCE_T, true);
    // initialize item collections
    {% call util.render_indented(1) -%}
{% block arch_itemcoll_init scoped -%}
s32 i;
ocrGuid_t *itemTable;
{% for name, i in g.itemDeclarations.items() -%}
{% if i.key -%}
CNC_CREATE_ITEM(&context->_items.{{name}}, (void**)&itemTable, sizeof(ocrGuid_t) * (CNC_TABLE_SIZE+1));
for (i=0; i<=CNC_TABLE_SIZE; i++) itemTable[i] = NULL_GUID;
{% else -%}
ocrEventCreate(&context->_items.{{name}}, OCR_EVENT_STICKY_T, true);
{% endif -%}
{% endfor -%}
{% endblock arch_itemcoll_init -%}
    {% endcall -%}
    // initialize step collections
    {% for s in g.finalAndSteps -%}
    ocrEdtTemplateCreate(&context->_steps.{{s.collName}},
            _cncStep_{{s.collName}}, EDT_PARAM_UNK, EDT_PARAM_UNK);
    {% endfor -%}
    return context;
}

void {{g.name}}_destroy({{g.name}}Ctx *context) {
    // destroy item collections
    // XXX - need to do a deep free by traversing the table
    {% call util.render_indented(1) -%}
{% block arch_itemcoll_destroy -%}
{% for name, i in g.itemDeclarations.items() -%}
{% if i.key -%}
CNC_DESTROY_ITEM(context->_items.{{name}});
{% else -%}
ocrEventDestroy(context->_items.{{name}});
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
    ocrEdtTemplateDestroy(templGuid);
    // Start graph execution
    {{g.name}}_init(args, context);
    ocrDbDestroy(depv[0].guid);
    return NULL_GUID;
}

static ocrGuid_t _finalizerEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    {{g.name}}Ctx *context = depv[0].ptr;
    cncTag_t *tag = depv[1].ptr; MAYBE_UNUSED(tag);
    cncPrescribe_{{g.finalizeFunction.collName}}(
        {%- for x in g.finalizeFunction.tag %}tag[{{loop.index0}}], {% endfor -%}
        context);
    return NULL_GUID;
}

void {{g.name}}_launch({{g.name}}Args *args, {{g.name}}Ctx *context) {
    {{g.name}}Args *argsCopy;
    ocrGuid_t graphEdtGuid, finalEdtGuid, edtTemplateGuid, outEventGuid, argsDbGuid;
    // copy the args struct into a data block
    CNC_CREATE_ITEM(&argsDbGuid, (void**)&argsCopy, sizeof(*args));
    *argsCopy = *args;
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
    CNC_CREATE_ITEM(&_tagGuid, (void**)&_tagPtr, sizeof(cncTag_t) * {{ g.finalizeFunction.tag|count}});
    {% for x in g.finalizeFunction.tag -%}
    _tagPtr[_i++] = {{x}};
    {% endfor -%}
    {% else -%}
    ocrGuid_t _tagGuid = NULL_GUID;
    {% endif -%}
    ocrEventSatisfy(ctx->_guids.awaitTag, _tagGuid);
}
