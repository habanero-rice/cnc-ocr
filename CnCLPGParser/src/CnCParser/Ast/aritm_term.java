
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser.Ast;

import CnCParser.*;
import lpg.runtime.*;

/**
 *<b>
 *<li>Rule 50:  aritm_term ::= aritm_term$first *$operand aritm_factor$second
 *<li>Rule 51:  aritm_term ::= aritm_term$first /$operand aritm_factor$second
 *<li>Rule 52:  aritm_term ::= aritm_factor$second
 *</b>
 */
public class aritm_term extends Ast implements Iaritm_term
{
    private CncParser environment;
    public CncParser getEnvironment() { return environment; }

    private Iaritm_term _first;
    private AstToken _operand;
    private aritm_factor _second;

    /**
     * The value returned by <b>getfirst</b> may be <b>null</b>
     */
    public Iaritm_term getfirst() { return _first; }
    /**
     * The value returned by <b>getoperand</b> may be <b>null</b>
     */
    public AstToken getoperand() { return _operand; }
    public aritm_factor getsecond() { return _second; }

    public aritm_term(CncParser environment, IToken leftIToken, IToken rightIToken,
                      Iaritm_term _first,
                      AstToken _operand,
                      aritm_factor _second)
    {
        super(leftIToken, rightIToken);

        this.environment = environment;
        this._first = _first;
        this._operand = _operand;
        this._second = _second;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof aritm_term)) return false;
        if (! super.equals(o)) return false;
        aritm_term other = (aritm_term) o;
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

    @Override
    public String toString(){
        if(_first != null)
            return _first.toString() + _operand.toString() + _second.toString();
        else
            return _second.toString();
    }
}


