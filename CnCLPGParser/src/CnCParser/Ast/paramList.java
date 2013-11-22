
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
 *<li>Rule 36:  param_list ::= param
 *<li>Rule 37:  param_list ::= param_list , param
 *</b>
 */
public class paramList extends AbstractAstList implements Iparam_list
{
    public param getparamAt(int i) { return (param) getElementAt(i); }

    public paramList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public paramList(param _param, boolean leftRecursive)
    {
        super((Ast) _param, leftRecursive);
    }

    public void addElement(param _param)
    {
        super.addElement((Ast) _param);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof paramList)) return false;
        if (! super.equals(o)) return false;
        paramList other = (paramList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            param element = getparamAt(i);
            if (! element.equals(other.getparamAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getparamAt(i).hashCode());
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
                param element = getparamAt(i);
                if (! v.preVisit(element)) continue;
                element.enter(v);
                v.postVisit(element);
            }
        }
        v.endVisit(this);
    }
}


