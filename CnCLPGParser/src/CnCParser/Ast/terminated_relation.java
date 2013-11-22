
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
 *<li>Rule 10:  terminated_relation ::= relation ;
 *</b>
 */
public class terminated_relation extends Ast implements Iterminated_relation
{
    private Irelation _relation;

    public Irelation getrelation() { return _relation; }

    public terminated_relation(IToken leftIToken, IToken rightIToken,
                               Irelation _relation)
    {
        super(leftIToken, rightIToken);

        this._relation = _relation;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof terminated_relation)) return false;
        if (! super.equals(o)) return false;
        terminated_relation other = (terminated_relation) o;
        if (! _relation.equals(other._relation)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_relation.hashCode());
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
            _relation.accept(v);
        v.endVisit(this);
    }
}


