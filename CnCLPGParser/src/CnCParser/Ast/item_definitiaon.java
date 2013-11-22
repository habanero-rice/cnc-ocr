
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
 *<li>Rule 37:  item_definition ::= t_type T_NAME$name
 *<li>Rule 38:  item_definition ::= T_NAME$name
 *</b>
 */
public class item_definitiaon extends Ast implements Iitem_definition
{
    private It_type _t_type;
    private AstToken _name;

    /**
     * The value returned by <b>gett_type</b> may be <b>null</b>
     */
    public It_type gett_type() { return _t_type; }
    public AstToken getname() { return _name; }

    public item_definitiaon(IToken leftIToken, IToken rightIToken,
                            It_type _t_type,
                            AstToken _name)
    {
        super(leftIToken, rightIToken);

        this._t_type = _t_type;
        this._name = _name;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof item_definitiaon)) return false;
        if (! super.equals(o)) return false;
        item_definitiaon other = (item_definitiaon) o;
        if (_t_type == null)
            if (other._t_type != null) return false;
            else; // continue
        else if (! _t_type.equals(other._t_type)) return false;
        if (! _name.equals(other._name)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_t_type == null ? 0 : _t_type.hashCode());
        hash = hash * 31 + (_name.hashCode());
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
            if (_t_type != null) _t_type.accept(v);
            _name.accept(v);
        }
        v.endVisit(this);
    }
}


