
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
 *<li>Rule 31:  item_type ::= item_type *
 *</b>
 */
public class PointerType extends Ast implements Iitem_type
{
    private Iitem_type _item_type;

    public Iitem_type getitem_type() { return _item_type; }

    public PointerType(IToken leftIToken, IToken rightIToken,
                       Iitem_type _item_type)
    {
        super(leftIToken, rightIToken);

        this._item_type = _item_type;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof PointerType)) return false;
        if (! super.equals(o)) return false;
        PointerType other = (PointerType) o;
        if (! _item_type.equals(other._item_type)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_item_type.hashCode());
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
            _item_type.accept(v);
        v.endVisit(this);
    }
}


