
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
 *<li>Rule 64:  step_component ::= t_type T_NAME$name
 *<li>Rule 65:  step_component ::= T_NAME$name
 *<li>Rule 66:  step_component ::= { T_NAME$start_range .. T_NAME$end_range }
 *</b>
 */
public class step_component extends Ast implements Istep_component
{
    private t_type _t_type;
    private AstToken _name;
    private AstToken _start_range;
    private AstToken _end_range;

    /**
     * The value returned by <b>gett_type</b> may be <b>null</b>
     */
    public t_type gett_type() { return _t_type; }
    /**
     * The value returned by <b>getname</b> may be <b>null</b>
     */
    public AstToken getname() { return _name; }
    /**
     * The value returned by <b>getstart_range</b> may be <b>null</b>
     */
    public AstToken getstart_range() { return _start_range; }
    /**
     * The value returned by <b>getend_range</b> may be <b>null</b>
     */
    public AstToken getend_range() { return _end_range; }

    public step_component(IToken leftIToken, IToken rightIToken,
                          t_type _t_type,
                          AstToken _name,
                          AstToken _start_range,
                          AstToken _end_range)
    {
        super(leftIToken, rightIToken);

        this._t_type = _t_type;
        this._name = _name;
        this._start_range = _start_range;
        this._end_range = _end_range;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_component)) return false;
        if (! super.equals(o)) return false;
        step_component other = (step_component) o;
        if (_t_type == null)
            if (other._t_type != null) return false;
            else; // continue
        else if (! _t_type.equals(other._t_type)) return false;
        if (_name == null)
            if (other._name != null) return false;
            else; // continue
        else if (! _name.equals(other._name)) return false;
        if (_start_range == null)
            if (other._start_range != null) return false;
            else; // continue
        else if (! _start_range.equals(other._start_range)) return false;
        if (_end_range == null)
            if (other._end_range != null) return false;
            else; // continue
        else if (! _end_range.equals(other._end_range)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_t_type == null ? 0 : _t_type.hashCode());
        hash = hash * 31 + (_name == null ? 0 : _name.hashCode());
        hash = hash * 31 + (_start_range == null ? 0 : _start_range.hashCode());
        hash = hash * 31 + (_end_range == null ? 0 : _end_range.hashCode());
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
            if (_name != null) _name.accept(v);
            if (_start_range != null) _start_range.accept(v);
            if (_end_range != null) _end_range.accept(v);
        }
        v.endVisit(this);
    }
}


