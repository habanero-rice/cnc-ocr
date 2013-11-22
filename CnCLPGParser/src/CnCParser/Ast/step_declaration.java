
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
 *<li>Rule 56:  step_declaration ::= step_instance attribute_list_opt
 *</b>
 */
public class step_declaration extends Ast implements Istep_declaration
{
    private Istep_instance _step_instance;
    private attributeList _attribute_list_opt;

    public Istep_instance getstep_instance() { return _step_instance; }
    public attributeList getattribute_list_opt() { return _attribute_list_opt; }

    public step_declaration(IToken leftIToken, IToken rightIToken,
                            Istep_instance _step_instance,
                            attributeList _attribute_list_opt)
    {
        super(leftIToken, rightIToken);

        this._step_instance = _step_instance;
        this._attribute_list_opt = _attribute_list_opt;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_declaration)) return false;
        if (! super.equals(o)) return false;
        step_declaration other = (step_declaration) o;
        if (! _step_instance.equals(other._step_instance)) return false;
        if (! _attribute_list_opt.equals(other._attribute_list_opt)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_step_instance.hashCode());
        hash = hash * 31 + (_attribute_list_opt.hashCode());
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
            _step_instance.accept(v);
            _attribute_list_opt.accept(v);
        }
        v.endVisit(this);
    }
}


