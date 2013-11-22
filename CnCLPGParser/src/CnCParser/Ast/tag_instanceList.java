
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
 *<li>Rule 25:  tag_instance_restricted ::= < tag_definition step_description_opt >
 *</b>
 */
public class tag_instanceList extends AbstractAstList implements Itag_instance_restricted
{
    public tag_instance gettag_instanceAt(int i) { return (tag_instance) getElementAt(i); }

    public tag_instanceList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public tag_instanceList(tag_instance _tag_instance, boolean leftRecursive)
    {
        super((Ast) _tag_instance, leftRecursive);
    }

    public void addElement(tag_instance _tag_instance)
    {
        super.addElement((Ast) _tag_instance);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof tag_instanceList)) return false;
        if (! super.equals(o)) return false;
        tag_instanceList other = (tag_instanceList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            tag_instance element = gettag_instanceAt(i);
            if (! element.equals(other.gettag_instanceAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (gettag_instanceAt(i).hashCode());
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
                tag_instance element = gettag_instanceAt(i);
                if (! v.preVisit(element)) continue;
                element.enter(v);
                v.postVisit(element);
            }
        }
        v.endVisit(this);
    }
}


