
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
 *<li>Rule 34:  tag_definition ::= tag_type T_NAME$name
 *<li>Rule 35:  tag_definition ::= T_NAME$name
 *</b>
 */
public class tag_definition extends Ast implements Itag_definition
{
    private Itag_type _tag_type;
    private AstToken _name;

    /**
     * The value returned by <b>gettag_type</b> may be <b>null</b>
     */
    public Itag_type gettag_type() { return _tag_type; }
    public AstToken getname() { return _name; }

    public tag_definition(IToken leftIToken, IToken rightIToken,
                          Itag_type _tag_type,
                          AstToken _name)
    {
        super(leftIToken, rightIToken);

        this._tag_type = _tag_type;
        this._name = _name;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof tag_definition)) return false;
        if (! super.equals(o)) return false;
        tag_definition other = (tag_definition) o;
        if (_tag_type == null)
            if (other._tag_type != null) return false;
            else; // continue
        else if (! _tag_type.equals(other._tag_type)) return false;
        if (! _name.equals(other._name)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_tag_type == null ? 0 : _tag_type.hashCode());
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
            if (_tag_type != null) _tag_type.accept(v);
            _name.accept(v);
        }
        v.endVisit(this);
    }
}


