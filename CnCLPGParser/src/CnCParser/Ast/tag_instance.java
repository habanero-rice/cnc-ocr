
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
 *<li>Rule 33:  tag_instance ::= < tag_definition tag_description_opt >
 *</b>
 */
public class tag_instance extends Ast implements Itag_instance
{
    private tag_definition _tag_definition;
    private tag_componentList _tag_description_opt;

    public tag_definition gettag_definition() { return _tag_definition; }
    public tag_componentList gettag_description_opt() { return _tag_description_opt; }

    public tag_instance(IToken leftIToken, IToken rightIToken,
                        tag_definition _tag_definition,
                        tag_componentList _tag_description_opt)
    {
        super(leftIToken, rightIToken);

        this._tag_definition = _tag_definition;
        this._tag_description_opt = _tag_description_opt;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof tag_instance)) return false;
        if (! super.equals(o)) return false;
        tag_instance other = (tag_instance) o;
        if (! _tag_definition.equals(other._tag_definition)) return false;
        if (! _tag_description_opt.equals(other._tag_description_opt)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_tag_definition.hashCode());
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
            _tag_definition.accept(v);
            _tag_description_opt.accept(v);
        }
        v.endVisit(this);
    }
}


