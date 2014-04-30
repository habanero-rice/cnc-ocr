
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
 *<li>Rule 74:  step_description_aff_opt ::= step_description_aff
 *<li>Rule 75:  step_description_aff_opt ::= $Empty
 *<li>Rule 76:  step_description_aff ::= @ step_affinity_list
 *<li>Rule 77:  step_affinity_list ::= step_affinity
 *<li>Rule 78:  step_affinity_list ::= step_affinity_list , step_affinity
 *</b>
 */
public class step_affinityList extends AbstractAstList implements Istep_description_aff_opt, Istep_description_aff, Istep_affinity_list
{
    public step_affinity getstep_affinityAt(int i) { return (step_affinity) getElementAt(i); }

    public step_affinityList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public step_affinityList(step_affinity _step_affinity, boolean leftRecursive)
    {
        super((Ast) _step_affinity, leftRecursive);
    }

    public void add(step_affinity _step_affinity)
    {
        super.add((Ast) _step_affinity);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof step_affinityList)) return false;
        if (! super.equals(o)) return false;
        step_affinityList other = (step_affinityList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            step_affinity element = getstep_affinityAt(i);
            if (! element.equals(other.getstep_affinityAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getstep_affinityAt(i).hashCode());
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
                step_affinity element = getstep_affinityAt(i);
                if (! v.preVisit(element)) continue;
                element.enter(v);
                v.postVisit(element);
            }
        }
        v.endVisit(this);
    }
}


