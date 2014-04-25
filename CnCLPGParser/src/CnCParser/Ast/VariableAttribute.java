
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
 *<li>Rule 84:  attribute ::= T_NAME$name = T_NAME$value
 *</b>
 */
public class VariableAttribute extends Ast implements Iattribute
{
    private AstToken _name;
    private AstToken _value;

    public AstToken getname() { return _name; }
    public AstToken getvalue() { return _value; }

    public VariableAttribute(IToken leftIToken, IToken rightIToken,
                             AstToken _name,
                             AstToken _value)
    {
        super(leftIToken, rightIToken);

        this._name = _name;
        this._value = _value;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof VariableAttribute)) return false;
        if (! super.equals(o)) return false;
        VariableAttribute other = (VariableAttribute) o;
        if (! _name.equals(other._name)) return false;
        if (! _value.equals(other._value)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_name.hashCode());
        hash = hash * 31 + (_value.hashCode());
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
            _value.accept(v);
        }
        v.endVisit(this);
    }
}


