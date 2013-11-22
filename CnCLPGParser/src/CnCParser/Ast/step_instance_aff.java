
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
 *<li>Rule 70:  step_instance_aff ::= ($step_type T_NAME$name step_description_aff_opt )
 *<li>Rule 71:  step_instance_aff ::= {$step_type T_NAME$name step_description_aff_opt }
 *</b>
 */
public class step_instance_aff extends Ast implements Istep_instance_aff
{
    private AstToken _step_type;
    private AstToken _name;
    private step_affinityList _step_description_aff_opt;

    public AstToken getstep_type() { return _step_type; }
    public AstToken getname() { return _name; }
    public step_affinityList getstep_description_aff_opt() { return _step_description_aff_opt; }

    public step_instance_aff(IToken leftIToken, IToken rightIToken,
                             AstToken _step_type,
                             AstToken _name,
                             step_affinityList _step_description_aff_opt)
    {
        super(leftIToken, rightIToken);

        this._step_type = _step_type;
        this._name = _name;
        this._step_description_aff_opt = _step_description_aff_opt;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_instance_aff)) return false;
        if (! super.equals(o)) return false;
        step_instance_aff other = (step_instance_aff) o;
        if (! _step_type.equals(other._step_type)) return false;
        if (! _name.equals(other._name)) return false;
        if (! _step_description_aff_opt.equals(other._step_description_aff_opt)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_step_type.hashCode());
        hash = hash * 31 + (_name.hashCode());
        hash = hash * 31 + (_step_description_aff_opt.hashCode());
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
            _step_description_aff_opt.accept(v);
        }
        v.endVisit(this);
    }
}


