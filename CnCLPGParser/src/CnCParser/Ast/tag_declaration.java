
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
 *<li>Rule 32:  tag_declaration ::= tag_instance attribute_list_opt
 *</b>
 */
public class tag_declaration extends Ast implements Itag_declaration
{
    private tag_instance _tag_instance;
    private attributeList _attribute_list_opt;

    public tag_instance gettag_instance() { return _tag_instance; }
    public attributeList getattribute_list_opt() { return _attribute_list_opt; }

    public tag_declaration(IToken leftIToken, IToken rightIToken,
                           tag_instance _tag_instance,
                           attributeList _attribute_list_opt)
    {
        super(leftIToken, rightIToken);

        this._tag_instance = _tag_instance;
        this._attribute_list_opt = _attribute_list_opt;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof tag_declaration)) return false;
        if (! super.equals(o)) return false;
        tag_declaration other = (tag_declaration) o;
        if (! _tag_instance.equals(other._tag_instance)) return false;
        if (! _attribute_list_opt.equals(other._attribute_list_opt)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_tag_instance.hashCode());
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
            _tag_instance.accept(v);
            _attribute_list_opt.accept(v);
        }
        v.endVisit(this);
    }
}


