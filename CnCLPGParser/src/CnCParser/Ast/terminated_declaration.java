
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
 *<b>
 *<li>Rule 6:  terminated_declaration ::= declaration ;
 *</b>
 */
public class terminated_declaration extends Ast implements Iterminated_declaration
{
    private Ideclaration _declaration;

    public Ideclaration getdeclaration() { return _declaration; }

    public terminated_declaration(IToken leftIToken, IToken rightIToken,
                                  Ideclaration _declaration)
    {
        super(leftIToken, rightIToken);

        this._declaration = _declaration;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof terminated_declaration)) return false;
        if (! super.equals(o)) return false;
        terminated_declaration other = (terminated_declaration) o;
        if (! _declaration.equals(other._declaration)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_declaration.hashCode());
        return hash;
    }

    public void accept(IAstVisitor v)
    {
        if (! v.preVisit(this)) return;
        enter((Visitor) v);
        v.postVisit(this);
    }

    public void enter(Visitor v)
    {
        boolean checkChildren = v.visit(this);
        if (checkChildren)
            _declaration.accept(v);
        v.endVisit(this);
    }
}


