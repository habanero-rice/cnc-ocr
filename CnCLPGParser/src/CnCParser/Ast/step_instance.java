
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
 *<li>Rule 59:  step_instance ::= ($step_type step_instance_name$name step_description_opt )
 *<li>Rule 60:  step_instance ::= {$step_type T_NAME$name step_description_opt }
 *</b>
 */
public class step_instance extends Ast implements Istep_instance
{
    private AstToken _step_type;
    private Istep_instance_name _name;
    private step_componentList _step_description_opt;

    public AstToken getstep_type() { return _step_type; }
    public Istep_instance_name getname() { return _name; }
    public step_componentList getstep_description_opt() { return _step_description_opt; }

    public step_instance(IToken leftIToken, IToken rightIToken,
                         AstToken _step_type,
                         Istep_instance_name _name,
                         step_componentList _step_description_opt)
    {
        super(leftIToken, rightIToken);

        this._step_type = _step_type;
        this._name = _name;
        this._step_description_opt = _step_description_opt;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_instance)) return false;
        if (! super.equals(o)) return false;
        step_instance other = (step_instance) o;
        if (! _step_type.equals(other._step_type)) return false;
        if (! _name.equals(other._name)) return false;
        if (! _step_description_opt.equals(other._step_description_opt)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_step_type.hashCode());
        hash = hash * 31 + (_name.hashCode());
        hash = hash * 31 + (_step_description_opt.hashCode());
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
            _step_type.accept(v);
            _name.accept(v);
            _step_description_opt.accept(v);
        }
        v.endVisit(this);
    }
}


