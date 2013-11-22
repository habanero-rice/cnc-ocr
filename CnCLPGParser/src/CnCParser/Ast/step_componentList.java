
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
 *<li>Rule 59:  step_description_opt ::= step_description
 *<li>Rule 60:  step_description_opt ::= $Empty
 *<li>Rule 61:  step_description ::= : step_component_list
 *<li>Rule 62:  step_component_list ::= step_component
 *<li>Rule 63:  step_component_list ::= step_component_list , step_component
 *</b>
 */
public class step_componentList extends AbstractAstList implements Istep_description_opt, Istep_description, Istep_component_list
{
    public step_component getstep_componentAt(int i) { return (step_component) getElementAt(i); }

    public step_componentList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public step_componentList(step_component _step_component, boolean leftRecursive)
    {
        super((Ast) _step_component, leftRecursive);
    }

    public void addElement(step_component _step_component)
    {
        super.addElement((Ast) _step_component);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_componentList)) return false;
        if (! super.equals(o)) return false;
        step_componentList other = (step_componentList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            step_component element = getstep_componentAt(i);
            if (! element.equals(other.getstep_componentAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getstep_componentAt(i).hashCode());
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
                step_component element = getstep_componentAt(i);
                if (! v.preVisit(element)) continue;
                element.enter(v);
                v.postVisit(element);
            }
        }
        v.endVisit(this);
    }
}


