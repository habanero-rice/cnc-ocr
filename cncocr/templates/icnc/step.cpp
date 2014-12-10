{#/* *******************************************************************************
 *  Copyright (c) 2007-2014, Intel Corporation
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ********************************************************************************/#}
{%- import "common_macros.inc.c" as util with context -%}
{%- import "icnc/macros_icnc.inc" as util with context -%}
{%- set stepfun = g.stepFunctions[targetStep] -%}

#include "{{g.name}}_context.h"

int {{stepfun.collName}}_step::execute( const {{stepfun.collName}}_tag_t & tag, {{g.name}}_context & ctxt ) const
{
    {{g.name}}_context * ctx = &ctxt;
    {% if stepfun.tag|count > 1 -%}
    {%- for arg in stepfun.tag -%}
    const cnc_tag_t {{arg}} = tag.{{arg}};
    {%- endfor -%}
    {%- elif stepfun.tag|count > 0 -%}
    const cnc_tag_t {{stepfun.tag[0]}} = tag;
    {% endif %}

    {{util.render_ctxtargs_init(g, pfx='ctxt.', types=True)}}

    // Get input items
    {%- for input in stepfun.inputs %}
    {{util.render_dependence(g, "ctxt.", input, getput='get', instantiate=True, todo=False)}}
    {%- endfor %}

    // TODO: here goes your computation
    // creating output handles and assign values
    {%- for output in stepfun.outputs %}
    {{util.render_dependence(g, "ctxt.", output, getput=False, instantiate=True)}}
    {%- endfor %}

    // TODO: create output
    {% for output in stepfun.outputs -%}
    {{util.render_dependence(g, "ctxt.", output)}}
    {%- endfor %}
    return CnC::CNC_Success;
}
