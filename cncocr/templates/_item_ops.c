{% import "common_macros.inc.c" as util with context -%}
{{ util.auto_file_banner() }}

#include "{{g.name}}_internal.h"
#include "{{g.name}}_itemInfo.h"

{% for i in g.itemDeclarations.values() -%}
#define {{ util.coll2id(i.collName) }} {{ loop.index }}
{% endfor %}
{% for i in g.itemDeclarations.values() %}
/* {{i.collName}} */

cncHandle_t cncCreateItemSized_{{i.collName}}({{i.type.ptrType}}*item, size_t size) {
    cncHandle_t handle;
    // XXX - do I need to check for busy (and do a retry)?
    CNC_CREATE_ITEM(&handle, (void**)item, size);
    return handle;
}

void cncPutCheckedR_{{i.collName}}(cncHandle_t _handle, {{
        util.print_tag(i.key, typed=True)
        }}bool _checkSingleAssignment, int _srcRank, {{g.name}}Ctx *ctx) {
    {% if i.key %}
    cncTag_t _tag[] = { {{i.key|join(", ")}} };
    {% else %}
    cncTag_t *_tag = NULL;
    {% endif %}
    {% if not i.isVirtual -%}
    {#/*****NON-VIRTUAL*****/-#}
    {{ util.log_msg("PUT", i.collName, i.key) }}
    {% if i.key -%}
    _cncPut(_handle, (unsigned char*)_tag, sizeof(_tag), ctx->_items.{{i.collName}}, _checkSingleAssignment, _srcRank);
    {%- else -%}
    CNC_DDF_PUT(ctx->_items.{{i.collName}}, _handle);
    {%- endif %}
    {%- else -%}
    {% set targetColl = g.itemDeclarations[i.mapTarget] -%}
    {% if i.isInline -%}
    {#/*****INLINE VIRTUAL*****/-#}
    cncPutCheckedR_{{i.mapTarget}}(_handle, {{
        util.print_tag(i.keyFunction)
        }}_checkSingleAssignment, _srcRank, ctx);
    {%- else -%}
    {#/*****EXTERN VIRTUAL******/-#}
    {{i.mapTarget}}ItemKey _key = {{i.functionName}}({{
        util.print_tag(i.key) }}ctx);
    cncPutCheckedR_{{i.mapTarget}}(_handle, {{
        util.print_tag(targetColl.key, prefix="_key.")
        }}_checkSingleAssignment, _srcRank, ctx);
    {%- endif %}
    {%- endif %}
#ifdef HC_COMM
    int _rank = {{ util.itemDistFn(i) }};
    if (_rank != HCMPI_COMM_RANK) {
        LOG_INFO("Remote put {{i.collName}}\n");
        hc_cnc_put(_rank, {{ util.coll2id(i.collName) }}, _tag, {{i.key|count}}, _handle, cncItemSize_{{i.collName}}(ctx));
    }
    else {
        LOG_INFO("Local put {{i.collName}}\n");
    }
#endif
}

DDF_t *cncGet_{{i.collName}}({{ util.print_tag(i.key, typed=True) }}{{g.name}}Ctx *ctx) {
    {% if not i.isVirtual -%}
    {#/*****NON-VIRTUAL*****/-#}
    {{ util.log_msg("GET-DEP", i.collName, i.key) }}
    {% if i.key %}
    cncTag_t _tag[] = { {{i.key|join(", ")}} };
    {% else %}
    cncTag_t *_tag = NULL;
    {% endif %}
    {% if i.key -%}
    DDF_t *_ddf = _cncGet((unsigned char*)_tag, sizeof(_tag), ctx->_items.{{i.collName}});
    {%- else -%}
    DDF_t *_ddf = ctx->_items.{{i.collName}};
    {%- endif %}
#ifdef HC_COMM
    int _rank = {{ util.itemDistFn(i) }};
    if (_rank != HCMPI_COMM_RANK) {
        // _ddf->cancel actually means it's already been requested (for CnC)
        if (!_ddf->cancel && !__sync_lock_test_and_set(&_ddf->cancel, 1)) {
            LOG_INFO("Remote get {{i.collName}}\n");
            hc_cnc_ddf_await(_rank, {{ util.coll2id(i.collName) }}, _tag, {{i.key|count}}, _ddf);
        }
        else {
            LOG_INFO("Remote get {{i.collName}} (cached)\n");
        }
    }
    else {
        LOG_INFO("Local get {{i.collName}}\n");
    }
#endif
    return _ddf;
    {%- else -%}
    {% set targetColl = g.itemDeclarations[i.mapTarget] -%}
    {% if i.isInline -%}
    {#/*****INLINE VIRTUAL*****/-#}
    DDF_t *_ddf = cncGet_{{i.mapTarget}}({{
        util.print_tag(i.keyFunction)
        }}destination, slot, mode, ctx);
    {%- else -%}
    {#/*****EXTERN VIRTUAL******/-#}
    {{i.mapTarget}}ItemKey _key = {{i.functionName}}({{
        util.print_tag(i.key) }}ctx);
    DDF_t *_ddf = cncGet_{{i.mapTarget}}({{
        util.print_tag(targetColl.key, prefix="_key.")
        }}destination, slot, mode, ctx);
    {%- endif %}
    {%- endif %}
}

{% endfor %}

#ifdef HC_COMM
void {{g.name}}_startItemCollDaemons({{g.name}}Ctx * ctx) {
    {% for i in g.concreteItems -%}
    hc_mpi_cnc_ic_daemons(cncItemSize_{{i.collName}}(ctx), {{
            i.key|count}}, {{util.coll2id(i.collName)}});
    {% endfor %}
}

void hc_cnc_xput(int collID, int *key, void *data, int srcRank) {
    switch (collID) {
    {% for i in g.itemDeclarations.values() %}
        case {{ util.coll2id(i.collName) }}: {
            cncPutCheckedR_{{i.collName}}(data, {% for k in i.key -%}
                key[{{loop.index0}}], {% endfor %}false, srcRank, {{ util.globalCtx(g) }});
            return;
        }
    {% endfor %}
    }
    ASSERT(!"Unreachable");
}

DDF_t *hc_cnc_xget(int collID, void *msg) {
    s32 *key = msg;
    switch (collID) {
    {% for i in g.itemDeclarations.values() %}
        case {{ util.coll2id(i.collName) }}:
            return cncGet_{{i.collName}}({% for k in i.key -%}
                key[{{loop.index0}}], {% endfor %}{{ util.globalCtx(g) }});
    {% endfor %}
    }
    ASSERT(!"Unreachable");
    return NULL;
}
#endif

