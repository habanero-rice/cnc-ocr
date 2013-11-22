
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
 *<li>Rule 25:  item_instance ::= [ item_definition tag_description_opt ]
 *</b>
 */
public class item_instance extends Ast implements Iitem_instance
{
    private item_definition _item_definition;
    private tag_componentList _tag_description_opt;

    public item_definition getitem_definition() { return _item_definition; }
    public tag_componentList gettag_description_opt() { return _tag_description_opt; }

    public item_instance(IToken leftIToken, IToken rightIToken,
                         item_definition _item_definition,
                         tag_componentList _tag_description_opt)
    {
        super(leftIToken, rightIToken);

        this._item_definition = _item_definition;
        this._tag_description_opt = _tag_description_opt;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof item_instance)) return false;
        if (! super.equals(o)) return false;
        item_instance other = (item_instance) o;
        if (! _item_definition.equals(other._item_definition)) return false;
        if (! _tag_description_opt.equals(other._tag_description_opt)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_item_definition.hashCode());
        hash = hash * 31 + (_tag_description_opt.hashCode());
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
            _item_definition.accept(v);
            _tag_description_opt.accept(v);
        }
        v.endVisit(this);
    }
}


