
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
 *<li>Rule 53:  aritm_factor ::= T_NAME$name
 *<li>Rule 54:  aritm_factor ::= T_NAME$name [ aritm_expr$index ]
 *<li>Rule 55:  aritm_factor ::= T_NUMBER$val
 *</b>
 */
public class aritm_factor extends Ast implements Iaritm_factor
{
    private CncParser environment;
    public CncParser getEnvironment() { return environment; }

    private AstToken _name;
    private Iaritm_expr _index;
    private AstToken _val;

    /**
     * The value returned by <b>getname</b> may be <b>null</b>
     */
    public AstToken getname() { return _name; }
    /**
     * The value returned by <b>getindex</b> may be <b>null</b>
     */
    public Iaritm_expr getindex() { return _index; }
    /**
     * The value returned by <b>getval</b> may be <b>null</b>
     */
    public AstToken getval() { return _val; }

    public aritm_factor(CncParser environment, IToken leftIToken, IToken rightIToken,
                        AstToken _name,
                        Iaritm_expr _index,
                        AstToken _val)
    {
        super(leftIToken, rightIToken);

        this.environment = environment;
        this._name = _name;
        this._index = _index;
        this._val = _val;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof aritm_factor)) return false;
        if (! super.equals(o)) return false;
        aritm_factor other = (aritm_factor) o;
        if (_name == null)
            if (other._name != null) return false;
            else; // continue
        else if (! _name.equals(other._name)) return false;
        if (_index == null)
            if (other._index != null) return false;
            else; // continue
        else if (! _index.equals(other._index)) return false;
        if (_val == null)
            if (other._val != null) return false;
            else; // continue
        else if (! _val.equals(other._val)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_name == null ? 0 : _name.hashCode());
        hash = hash * 31 + (_index == null ? 0 : _index.hashCode());
        hash = hash * 31 + (_val == null ? 0 : _val.hashCode());
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
            if (_name != null) _name.accept(v);
            if (_index != null) _index.accept(v);
            if (_val != null) _val.accept(v);
        }
        v.endVisit(this);
    }

    //
    // Keep another variable, for possible name change of name
    //
    String _new_name;
    public void setNewName(String change) {
        _new_name = change;
    }
    
    @Override
    public String toString(){
    	StringBuilder toret =  new StringBuilder();
    	if(_new_name != null){
    		toret.append(_new_name);
    		if(_index != null) toret.append("["+_index.toString()+"]");
    	}
    	else if(_name != null){
    		toret.append(_name);
    		if(_index != null) toret.append("["+_index.toString()+"]");
    	}
    	else if(_val != null){
    		toret.append(_val);
    	}
    	//else throw an error? (grammar does not accept empty)
    	
    	return toret.toString();
    }
}


