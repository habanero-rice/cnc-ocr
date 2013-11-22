
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
 * is implemented by:
 *<b>
 *<ul>
 *<li>item_declaration
 *<li>tag_declaration
 *<li>step_declaration
 *</ul>
 *</b>
 */
public interface Ideclaration
{
    public IToken getLeftIToken();
    public IToken getRightIToken();

    void accept(IAstVisitor v);
}


