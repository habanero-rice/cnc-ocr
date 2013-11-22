
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
 *<li>Rule 44:  tag_component ::= t_type aritm_expr$expression
 *<li>Rule 45:  tag_component ::= aritm_expr$expression
 *<li>Rule 46:  tag_component ::= { aritm_expr$start_range .. aritm_expr$stop_range }
 *</b>
 */
public class tag_component extends Ast implements Itag_component
{
    private t_type _t_type;
    private Iaritm_expr _expression;
    private Iaritm_expr _start_range;
    private Iaritm_expr _stop_range;

    /**
     * The value returned by <b>gett_type</b> may be <b>null</b>
     */
    public t_type gett_type() { return _t_type; }
    /**
     * The value returned by <b>getexpression</b> may be <b>null</b>
     */
    public Iaritm_expr getexpression() { return _expression; }
    /**
     * The value returned by <b>getstart_range</b> may be <b>null</b>
     */
    public Iaritm_expr getstart_range() { return _start_range; }
    /**
     * The value returned by <b>getstop_range</b> may be <b>null</b>
     */
    public Iaritm_expr getstop_range() { return _stop_range; }

    public tag_component(IToken leftIToken, IToken rightIToken,
                         t_type _t_type,
                         Iaritm_expr _expression,
                         Iaritm_expr _start_range,
                         Iaritm_expr _stop_range)
    {
        super(leftIToken, rightIToken);

        this._t_type = _t_type;
        this._expression = _expression;
        this._start_range = _start_range;
        this._stop_range = _stop_range;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof tag_component)) return false;
        if (! super.equals(o)) return false;
        tag_component other = (tag_component) o;
        if (_t_type == null)
            if (other._t_type != null) return false;
            else; // continue
        else if (! _t_type.equals(other._t_type)) return false;
        if (_expression == null)
            if (other._expression != null) return false;
            else; // continue
        else if (! _expression.equals(other._expression)) return false;
        if (_start_range == null)
            if (other._start_range != null) return false;
            else; // continue
        else if (! _start_range.equals(other._start_range)) return false;
        if (_stop_range == null)
            if (other._stop_range != null) return false;
            else; // continue
        else if (! _stop_range.equals(other._stop_range)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_t_type == null ? 0 : _t_type.hashCode());
        hash = hash * 31 + (_expression == null ? 0 : _expression.hashCode());
        hash = hash * 31 + (_start_range == null ? 0 : _start_range.hashCode());
        hash = hash * 31 + (_stop_range == null ? 0 : _stop_range.hashCode());
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
            if (_expression != null) _expression.accept(v);
            if (_start_range != null) _start_range.accept(v);
            if (_stop_range != null) _stop_range.accept(v);
        }
        v.endVisit(this);
    }
}


