
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
 *<li>Rule 81:  attribute_list_opt ::= $Empty
 *<li>Rule 82:  attribute_list ::= attribute
 *<li>Rule 83:  attribute_list ::= attribute_list , attribute
 *</b>
 */
public class attributeList extends AbstractAstList implements Iattribute_list_opt, Iattribute_list
{
    public Iattribute getattributeAt(int i) { return (Iattribute) getElementAt(i); }

    public attributeList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public attributeList(Iattribute _attribute, boolean leftRecursive)
    {
        super((Ast) _attribute, leftRecursive);
    }

    public void add(Iattribute _attribute)
    {
        super.add((Ast) _attribute);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof attributeList)) return false;
        if (! super.equals(o)) return false;
        attributeList other = (attributeList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            Iattribute element = getattributeAt(i);
            if (! element.equals(other.getattributeAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getattributeAt(i).hashCode());
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
                Iattribute element = getattributeAt(i);
                element.accept(v);
            }
        }
        v.endVisit(this);
    }
}


