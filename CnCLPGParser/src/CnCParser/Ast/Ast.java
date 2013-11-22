
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser.Ast;

import lpg.runtime.*;

public abstract class Ast implements IAst
{
    public IAst getNextAst() { return null; }
    protected IToken leftIToken,
                     rightIToken;
    public IAst getParent()
    {
        throw new UnsupportedOperationException("noparent-saved option in effect");
    }

    public IToken getLeftIToken() { return leftIToken; }
    public IToken getRightIToken() { return rightIToken; }
    public IToken[] getPrecedingAdjuncts() { return leftIToken.getPrecedingAdjuncts(); }
    public IToken[] getFollowingAdjuncts() { return rightIToken.getFollowingAdjuncts(); }

    public String toString()
    {
        return leftIToken.getILexStream().toString(leftIToken.getStartOffset(), rightIToken.getEndOffset());
    }

    public Ast(IToken token) { this.leftIToken = this.rightIToken = token; }
    public Ast(IToken leftIToken, IToken rightIToken)
    {
        this.leftIToken = leftIToken;
        this.rightIToken = rightIToken;
    }

    void initialize() {}

    public java.util.ArrayList getChildren()
    {
        throw new UnsupportedOperationException("noparent-saved option in effect");
    }
    public java.util.ArrayList getAllChildren() { return getChildren(); }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof Ast)) return false;
        Ast other = (Ast) o;
        return getLeftIToken().getILexStream() == other.getLeftIToken().getILexStream() &&
               getLeftIToken().getTokenIndex() == other.getLeftIToken().getTokenIndex() &&
               getRightIToken().getILexStream() == other.getRightIToken().getILexStream() &&
               getRightIToken().getTokenIndex() == other.getRightIToken().getTokenIndex();
    }

    public int hashCode()
    {
        int hash = 7;
        if (getLeftIToken().getILexStream() != null) hash = hash * 31 + getLeftIToken().getILexStream().hashCode();
        hash = hash * 31 + getLeftIToken().getTokenIndex();
        if (getRightIToken().getILexStream() != null) hash = hash * 31 + getRightIToken().getILexStream().hashCode();
        hash = hash * 31 + getRightIToken().getTokenIndex();
        return hash;
    }
    public abstract void accept(IAstVisitor v);
}


