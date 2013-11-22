
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
 *<li>Rule 19:  step_prescription ::= tag_instance :: step_instance_list
 *</b>
 */
public class StepPrescription extends Ast implements Istep_prescription
{
    private tag_instance _tag_instance;
    private step_instance_affList _step_instance_list;

    public tag_instance gettag_instance() { return _tag_instance; }
    public step_instance_affList getstep_instance_list() { return _step_instance_list; }

    public StepPrescription(IToken leftIToken, IToken rightIToken,
                            tag_instance _tag_instance,
                            step_instance_affList _step_instance_list)
    {
        super(leftIToken, rightIToken);

        this._tag_instance = _tag_instance;
        this._step_instance_list = _step_instance_list;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof StepPrescription)) return false;
        if (! super.equals(o)) return false;
        StepPrescription other = (StepPrescription) o;
        if (! _tag_instance.equals(other._tag_instance)) return false;
        if (! _step_instance_list.equals(other._step_instance_list)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_tag_instance.hashCode());
        hash = hash * 31 + (_step_instance_list.hashCode());
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
            _tag_instance.accept(v);
            _step_instance_list.accept(v);
        }
        v.endVisit(this);
    }
}


