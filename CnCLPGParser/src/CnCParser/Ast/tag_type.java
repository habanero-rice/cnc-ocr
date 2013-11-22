
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
 *<li>Rule 38:  tag_type ::= t_type
 *<li>Rule 39:  tag_type ::= t_type [ T_NUMBER$dim ]
 *<li>Rule 40:  tag_type ::= tag_type . t_type
 *</b>
 */
public class tag_type extends Ast implements Itag_type
{
    private t_type _t_type;
    private AstToken _dim;
    private Itag_type _tag_type;

    public t_type gett_type() { return _t_type; }
    /**
     * The value returned by <b>getdim</b> may be <b>null</b>
     */
    public AstToken getdim() { return _dim; }
    /**
     * The value returned by <b>gettag_type</b> may be <b>null</b>
     */
    public Itag_type gettag_type() { return _tag_type; }

    public tag_type(IToken leftIToken, IToken rightIToken,
                    t_type _t_type,
                    AstToken _dim,
                    Itag_type _tag_type)
    {
        super(leftIToken, rightIToken);

        this._t_type = _t_type;
        this._dim = _dim;
        this._tag_type = _tag_type;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof tag_type)) return false;
        if (! super.equals(o)) return false;
        tag_type other = (tag_type) o;
        if (! _t_type.equals(other._t_type)) return false;
        if (_dim == null)
            if (other._dim != null) return false;
            else; // continue
        else if (! _dim.equals(other._dim)) return false;
        if (_tag_type == null)
            if (other._tag_type != null) return false;
            else; // continue
        else if (! _tag_type.equals(other._tag_type)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_t_type.hashCode());
        hash = hash * 31 + (_dim == null ? 0 : _dim.hashCode());
        hash = hash * 31 + (_tag_type == null ? 0 : _tag_type.hashCode());
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
            _t_type.accept(v);
            if (_dim != null) _dim.accept(v);
            if (_tag_type != null) _tag_type.accept(v);
        }
        v.endVisit(this);
    }
}


