
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
 *<li>Rule 36:  tag_description_opt ::= tag_description
 *<li>Rule 37:  tag_description_opt ::= $Empty
 *<li>Rule 41:  tag_description ::= : tag_component_list
 *<li>Rule 42:  tag_component_list ::= tag_component
 *<li>Rule 43:  tag_component_list ::= tag_component_list , tag_component
 *</b>
 */
public class tag_componentList extends AbstractAstList implements Itag_description_opt, Itag_description, Itag_component_list
{
    public Itag_component gettag_componentAt(int i) { return (Itag_component) getElementAt(i); }

    public tag_componentList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public tag_componentList(Itag_component _tag_component, boolean leftRecursive)
    {
        super((Ast) _tag_component, leftRecursive);
    }

    public void addElement(Itag_component _tag_component)
    {
        super.addElement((Ast) _tag_component);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof tag_componentList)) return false;
        if (! super.equals(o)) return false;
        tag_componentList other = (tag_componentList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            Itag_component element = gettag_componentAt(i);
            if (! element.equals(other.gettag_componentAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (gettag_componentAt(i).hashCode());
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
                Itag_component element = gettag_componentAt(i);
                element.accept(v);
            }
        }
        v.endVisit(this);
    }
}


