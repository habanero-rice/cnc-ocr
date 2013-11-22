
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser.Ast;

import lpg.runtime.*;

public class AstToken extends Ast implements IAstToken
{
    public AstToken(IToken token) { super(token); }
    public IToken getIToken() { return leftIToken; }
    public String toString() { return leftIToken.toString(); }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof AstToken)) return false;
        AstToken other = (AstToken) o;
        return getIToken().getILexStream() == other.getIToken().getILexStream() &&
               getIToken().getTokenIndex() == other.getIToken().getTokenIndex();
    }

    public int hashCode()
    {
        int hash = 7;
        if (getIToken().getILexStream() != null) hash = hash * 31 + getIToken().getILexStream().hashCode();
        hash = hash * 31 + getIToken().getTokenIndex();
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
        v.visit(this);
        v.endVisit(this);
    }
}


