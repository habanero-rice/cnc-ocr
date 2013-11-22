
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
 *<li>Rule 77:  step_affinity ::= T_NAME$name = T_NUMBER$val
 *</b>
 */
public class step_affinity extends Ast implements Istep_affinity
{
    private AstToken _name;
    private AstToken _val;

    public AstToken getname() { return _name; }
    public AstToken getval() { return _val; }

    public step_affinity(IToken leftIToken, IToken rightIToken,
                         AstToken _name,
                         AstToken _val)
    {
        super(leftIToken, rightIToken);

        this._name = _name;
        this._val = _val;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_affinity)) return false;
        if (! super.equals(o)) return false;
        step_affinity other = (step_affinity) o;
        if (! _name.equals(other._name)) return false;
        if (! _val.equals(other._val)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_name.hashCode());
        hash = hash * 31 + (_val.hashCode());
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
        {
            _name.accept(v);
            _val.accept(v);
        }
        v.endVisit(this);
    }
}


