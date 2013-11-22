
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
 *<li>Rule 57:  step_instance_list ::= step_instance
 *<li>Rule 58:  step_instance_list ::= step_instance_list , step_instance
 *</b>
 */
public class step_instanceList extends AbstractAstList implements Istep_instance_list
{
    public Istep_instance getstep_instanceAt(int i) { return (Istep_instance) getElementAt(i); }

    public step_instanceList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public step_instanceList(Istep_instance _step_instance, boolean leftRecursive)
    {
        super((Ast) _step_instance, leftRecursive);
    }

    public void addElement(Istep_instance _step_instance)
    {
        super.addElement((Ast) _step_instance);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_instanceList)) return false;
        if (! super.equals(o)) return false;
        step_instanceList other = (step_instanceList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            Istep_instance element = getstep_instanceAt(i);
            if (! element.equals(other.getstep_instanceAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getstep_instanceAt(i).hashCode());
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
                Istep_instance element = getstep_instanceAt(i);
                element.accept(v);
            }
        }
        v.endVisit(this);
    }
}


