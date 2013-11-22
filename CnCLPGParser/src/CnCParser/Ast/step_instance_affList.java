
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
 *<li>Rule 68:  step_instance_list ::= step_instance_aff
 *<li>Rule 69:  step_instance_list ::= step_instance_list , step_instance_aff
 *</b>
 */
public class step_instance_affList extends AbstractAstList implements Istep_instance_list
{
    public step_instance_aff getstep_instance_affAt(int i) { return (step_instance_aff) getElementAt(i); }

    public step_instance_affList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public step_instance_affList(step_instance_aff _step_instance_aff, boolean leftRecursive)
    {
        super((Ast) _step_instance_aff, leftRecursive);
    }

    public void addElement(step_instance_aff _step_instance_aff)
    {
        super.addElement((Ast) _step_instance_aff);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_instance_affList)) return false;
        if (! super.equals(o)) return false;
        step_instance_affList other = (step_instance_affList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            step_instance_aff element = getstep_instance_affAt(i);
            if (! element.equals(other.getstep_instance_affAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getstep_instance_affAt(i).hashCode());
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
            for (int i = 0; i < size(); i++)
            {
                step_instance_aff element = getstep_instance_affAt(i);
                if (! v.preVisit(element)) continue;
                element.enter(v);
                v.postVisit(element);
            }
        }
        v.endVisit(this);
    }
}


