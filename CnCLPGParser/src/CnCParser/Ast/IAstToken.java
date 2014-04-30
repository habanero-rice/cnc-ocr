
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser.Ast;

import lpg.runtime.*;

/**
 * is always implemented by <b>AstToken</b>. It is also implemented by:
 *<b>
 *<ul>
 *<li>item_definition
 *<li>PointerType
 *<li>tag_definition
 *<li>aritm_factor
 *<li>step_instance
 *<li>step_component
 *<li>t_type
 *<li>step_instance_environment
 *<li>item_type0
 *<li>item_type1
 *<li>item_type2
 *<li>step_instance_name0
 *<li>step_instance_name1
 *</ul>
 *</b>
 */
public interface IAstToken
{
    public IToken getLeftIToken();
    public IToken getRightIToken();

    void accept(IAstVisitor v);
}


