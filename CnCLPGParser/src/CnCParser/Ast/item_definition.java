
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
 *<li>Rule 26:  item_definition ::= item_type T_NAME$name
 *<li>Rule 27:  item_definition ::= T_NAME$name
 *</b>
 */
public class item_definition extends Ast implements Iitem_definition
{
    private Iitem_type _item_type;
    private AstToken _name;

    /**
     * The value returned by <b>getitem_type</b> may be <b>null</b>
     */
    public Iitem_type getitem_type() { return _item_type; }
    public AstToken getname() { return _name; }

    public item_definition(IToken leftIToken, IToken rightIToken,
                           Iitem_type _item_type,
                           AstToken _name)
    {
        super(leftIToken, rightIToken);

        this._item_type = _item_type;
        this._name = _name;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof item_definition)) return false;
        if (! super.equals(o)) return false;
        item_definition other = (item_definition) o;
        if (_item_type == null)
            if (other._item_type != null) return false;
            else; // continue
        else if (! _item_type.equals(other._item_type)) return false;
        if (! _name.equals(other._name)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_item_type == null ? 0 : _item_type.hashCode());
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
            if (_item_type != null) _item_type.accept(v);
            _name.accept(v);
        }
        v.endVisit(this);
    }
}


