
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
 *<li>Rule 24:  item_declaration ::= item_instance attribute_list_opt
 *</b>
 */
public class item_declaration extends Ast implements Iitem_declaration
{
    private item_instance _item_instance;
    private attributeList _attribute_list_opt;

    public item_instance getitem_instance() { return _item_instance; }
    public attributeList getattribute_list_opt() { return _attribute_list_opt; }

    public item_declaration(IToken leftIToken, IToken rightIToken,
                            item_instance _item_instance,
                            attributeList _attribute_list_opt)
    {
        super(leftIToken, rightIToken);

        this._item_instance = _item_instance;
        this._attribute_list_opt = _attribute_list_opt;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof item_declaration)) return false;
        if (! super.equals(o)) return false;
        item_declaration other = (item_declaration) o;
        if (! _item_instance.equals(other._item_instance)) return false;
        if (! _attribute_list_opt.equals(other._attribute_list_opt)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_item_instance.hashCode());
        hash = hash * 31 + (_attribute_list_opt.hashCode());
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
            _item_instance.accept(v);
            _attribute_list_opt.accept(v);
        }
        v.endVisit(this);
    }
}


