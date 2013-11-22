
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
 *<li>Rule 2:  statements ::= statement
 *<li>Rule 3:  statements ::= statements statement
 *</b>
 */
public class statementList extends AbstractAstList implements Istatements
{
    public Istatement getstatementAt(int i) { return (Istatement) getElementAt(i); }

    public statementList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public statementList(Istatement _statement, boolean leftRecursive)
    {
        super((Ast) _statement, leftRecursive);
    }

    public void addElement(Istatement _statement)
    {
        super.addElement((Ast) _statement);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof statementList)) return false;
        if (! super.equals(o)) return false;
        statementList other = (statementList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            Istatement element = getstatementAt(i);
            if (! element.equals(other.getstatementAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getstatementAt(i).hashCode());
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
                Istatement element = getstatementAt(i);
                element.accept(v);
            }
        }
        v.endVisit(this);
    }
}


