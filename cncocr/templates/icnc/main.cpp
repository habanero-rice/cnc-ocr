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
{%- import "common_macros.inc.c" as util -%}
{%- import "icnc/macros_icnc.inc" as util -%}

#include "{{g.name}}_context.h"
#include "{{g.name}}_defs.h"

int {{g.name}}_main( {{g.name ~ "Args * args" ~ (", " if g.initFunction.tag or g.ctxParams|count else " ")}}
{%- if g.initFunction.tag -%}
{%- for a in g.initFunction.tag -%}
cnc_tag_t {{a}}{{", " if not loop.last or g.ctxParams|count}}
{%- endfor -%}
{%- endif -%}
{{util.render_ctxtargs_param(g, pfx='')}} )
{
#ifdef _DIST_
    CnC::dist_cnc_init< {{g.name}}_context > _dinit;
#endif

    // create our context
    {{g.name}}_context ctxt{{("( " ~ util.render_ctxtargs_param(g, types=False, pfx='') ~ " )") if g.ctxParams|count}};
    
    // Put initial items
    {% for output in g.initFunction.outputs %}
    {{util.render_dependence(g, "ctxt.", output, instantiate=True)}}
    {%- endfor %}

    // wait for completetion
    ctxt.wait();

    {
        // get the results
        {%- for input in g.finalizeFunction.inputs %}
        {{util.render_dependence(g, "ctxt.", input, getput='get', instantiate=True)}}
        {%- endfor %}
    }
    return 0;
}

int main( const int argc, const char*[] ) 
{
    /* TODO: parse arguments etc. */

    {% if g.initFunction.tag %}
    // TODO: Initialize these tag variables using args
    cnc_tag_t {{ g.initFunction.tag|join(", ") }};
    {% endif %}
    {% if g.ctxParams|count > 0 %}
    // initialize context parameters
    {% for line in g.ctxParams %}
    {{line}} /* TODO: Initialize */
    {%- endfor %}
    {% endif %}
    
    {{g.name}}Args args /* = TODO: Initialize args struct */;

    return {{g.name}}_main({{" &args" ~ (", " if g.initFunction.tag or g.ctxParams|count else " ")}}
    {%- if g.initFunction.tag -%}
    {%- for a in g.initFunction.tag -%}
    {{ " " ~ a ~ (", " if not loop.last or g.ctxParams|count > 0)}}
    {%- endfor -%}
    {%- endif -%}
    {{util.render_ctxtargs_param(g, types=False, pfx='')}} );
}
