
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
 *<li>Rule 41:  aritm_term ::= aritm_term$first *$operand aritm_factor$second
 *<li>Rule 42:  aritm_term ::= aritm_term$first /$operand aritm_factor$second
 *<li>Rule 43:  aritm_term ::= aritm_factor$second
 *</b>
 */
public class aritm_exprList extends AbstractAstList implements Iaritm_term
{
    public Iaritm_expr getaritm_exprAt(int i) { return (Iaritm_expr) getElementAt(i); }

    public aritm_exprList(IToken leftIToken, IToken rightIToken, boolean leftRecursive)
    {
        super(leftIToken, rightIToken, leftRecursive);
    }

    public aritm_exprList(Iaritm_expr _aritm_expr, boolean leftRecursive)
    {
        super((Ast) _aritm_expr, leftRecursive);
    }

    public void addElement(Iaritm_expr _aritm_expr)
    {
        super.addElement((Ast) _aritm_expr);
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof aritm_exprList)) return false;
        if (! super.equals(o)) return false;
        aritm_exprList other = (aritm_exprList) o;
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
        {
            Iaritm_expr element = getaritm_exprAt(i);
            if (! element.equals(other.getaritm_exprAt(i))) return false;
        }
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        for (int i = 0; i < size(); i++)
            hash = hash * 31 + (getaritm_exprAt(i).hashCode());
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
                Iaritm_expr element = getaritm_exprAt(i);
                element.accept(v);
            }
        }
        v.endVisit(this);
    }
}


