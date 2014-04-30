
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
 *<li>Rule 20:  instance_list ::= instance
 *<li>Rule 21:  instance_list ::= instance_list , instance
 *</b>
 */
public class instanceList extends AbstractAstList implements Iinstance_list
{
    public Iinstance getinstanceAt(int i) { return (Iinstance) getElementAt(i); }

    public instanceList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public instanceList(Iinstance _instance, boolean leftRecursive)
    {
        super((Ast) _instance, leftRecursive);
    }

    public void add(Iinstance _instance)
    {
        super.add((Ast) _instance);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof instanceList)) return false;
        if (! super.equals(o)) return false;
        instanceList other = (instanceList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            Iinstance element = getinstanceAt(i);
            if (! element.equals(other.getinstanceAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getinstanceAt(i).hashCode());
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
                Iinstance element = getinstanceAt(i);
                element.accept(v);
            }
        }
        v.endVisit(this);
    }
}


