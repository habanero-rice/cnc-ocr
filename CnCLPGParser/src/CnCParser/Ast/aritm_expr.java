
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
 *<li>Rule 47:  aritm_expr ::= aritm_expr$first +$operand aritm_term$second
 *<li>Rule 48:  aritm_expr ::= aritm_expr$first -$operand aritm_term$second
 *<li>Rule 49:  aritm_expr ::= aritm_term$second
 *</b>
 */
public class aritm_expr extends Ast implements Iaritm_expr
{
    private Iaritm_expr _first;
    private AstToken _operand;
    private Iaritm_term _second;

    /**
     * The value returned by <b>getfirst</b> may be <b>null</b>
     */
    public Iaritm_expr getfirst() { return _first; }
    /**
     * The value returned by <b>getoperand</b> may be <b>null</b>
     */
    public AstToken getoperand() { return _operand; }
    public Iaritm_term getsecond() { return _second; }

    public aritm_expr(IToken leftIToken, IToken rightIToken,
                      Iaritm_expr _first,
                      AstToken _operand,
                      Iaritm_term _second)
    {
        super(leftIToken, rightIToken);

        this._first = _first;
        this._operand = _operand;
        this._second = _second;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof aritm_expr)) return false;
        if (! super.equals(o)) return false;
        aritm_expr other = (aritm_expr) o;
        if (_first == null)
            if (other._first != null) return false;
            else; // continue
        else if (! _first.equals(other._first)) return false;
        if (_operand == null)
            if (other._operand != null) return false;
            else; // continue
        else if (! _operand.equals(other._operand)) return false;
        if (! _second.equals(other._second)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_first == null ? 0 : _first.hashCode());
        hash = hash * 31 + (_operand == null ? 0 : _operand.hashCode());
        hash = hash * 31 + (_second.hashCode());
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
            if (_first != null) _first.accept(v);
            if (_operand != null) _operand.accept(v);
            _second.accept(v);
        }
        v.endVisit(this);
    }
}


