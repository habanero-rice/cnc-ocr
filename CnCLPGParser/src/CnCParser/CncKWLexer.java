
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser;

import lpg.runtime.*;

public class CncKWLexer extends CncKWLexerprs
{
    private char[] inputChars;
    private final int keywordKind[] = new int[3 + 1];

    public int[] getKeywordKinds() { return keywordKind; }

    public int lexer(int curtok, int lasttok)
    {
        int current_kind = getKind(inputChars[curtok]),
            act;

        for (act = tAction(START_STATE, current_kind);
             act > NUM_RULES && act < ACCEPT_ACTION;
             act = tAction(act, current_kind))
        {
            curtok++;
            current_kind = (curtok > lasttok
                                   ? CncKWLexersym.Char_EOF
                                   : getKind(inputChars[curtok]));
        }

        if (act > ERROR_ACTION)
        {
            curtok++;
            act -= ERROR_ACTION;
        }

        return keywordKind[act == ERROR_ACTION  || curtok <= lasttok ? 0 : act];
    }

    public void setInputChars(char[] inputChars) { this.inputChars = inputChars; }


    //
    // Each upper case letter is mapped into its corresponding
    // lower case counterpart. For example, if an 'A' appears
    // in the input, it is mapped into CncKWLexersym.Char_a just
    // like 'a'.
    //
    final static int tokenKind[] = new int[128];
    static
    {
        tokenKind['$'] = CncKWLexersym.Char_DollarSign;
        tokenKind['%'] = CncKWLexersym.Char_Percent;
        tokenKind['_'] = CncKWLexersym.Char__;

        tokenKind['a'] = CncKWLexersym.Char_a;
        tokenKind['b'] = CncKWLexersym.Char_b;
        tokenKind['c'] = CncKWLexersym.Char_c;
        tokenKind['d'] = CncKWLexersym.Char_d;
        tokenKind['e'] = CncKWLexersym.Char_e;
        tokenKind['f'] = CncKWLexersym.Char_f;
        tokenKind['g'] = CncKWLexersym.Char_g;
        tokenKind['h'] = CncKWLexersym.Char_h;
        tokenKind['i'] = CncKWLexersym.Char_i;
        tokenKind['j'] = CncKWLexersym.Char_j;
        tokenKind['k'] = CncKWLexersym.Char_k;
        tokenKind['l'] = CncKWLexersym.Char_l;
        tokenKind['m'] = CncKWLexersym.Char_m;
        tokenKind['n'] = CncKWLexersym.Char_n;
        tokenKind['o'] = CncKWLexersym.Char_o;
        tokenKind['p'] = CncKWLexersym.Char_p;
        tokenKind['q'] = CncKWLexersym.Char_q;
        tokenKind['r'] = CncKWLexersym.Char_r;
        tokenKind['s'] = CncKWLexersym.Char_s;
        tokenKind['t'] = CncKWLexersym.Char_t;
        tokenKind['u'] = CncKWLexersym.Char_u;
        tokenKind['v'] = CncKWLexersym.Char_v;
        tokenKind['w'] = CncKWLexersym.Char_w;
        tokenKind['x'] = CncKWLexersym.Char_x;
        tokenKind['y'] = CncKWLexersym.Char_y;
        tokenKind['z'] = CncKWLexersym.Char_z;

        tokenKind['A'] = CncKWLexersym.Char_a;
        tokenKind['B'] = CncKWLexersym.Char_b;
        tokenKind['C'] = CncKWLexersym.Char_c;
        tokenKind['D'] = CncKWLexersym.Char_d;
        tokenKind['E'] = CncKWLexersym.Char_e;
        tokenKind['F'] = CncKWLexersym.Char_f;
        tokenKind['G'] = CncKWLexersym.Char_g;
        tokenKind['H'] = CncKWLexersym.Char_h;
        tokenKind['I'] = CncKWLexersym.Char_i;
        tokenKind['J'] = CncKWLexersym.Char_j;
        tokenKind['K'] = CncKWLexersym.Char_k;
        tokenKind['L'] = CncKWLexersym.Char_l;
        tokenKind['M'] = CncKWLexersym.Char_m;
        tokenKind['N'] = CncKWLexersym.Char_n;
        tokenKind['O'] = CncKWLexersym.Char_o;
        tokenKind['P'] = CncKWLexersym.Char_p;
        tokenKind['Q'] = CncKWLexersym.Char_q;
        tokenKind['R'] = CncKWLexersym.Char_r;
        tokenKind['S'] = CncKWLexersym.Char_s;
        tokenKind['T'] = CncKWLexersym.Char_t;
        tokenKind['U'] = CncKWLexersym.Char_u;
        tokenKind['V'] = CncKWLexersym.Char_v;
        tokenKind['W'] = CncKWLexersym.Char_w;
        tokenKind['X'] = CncKWLexersym.Char_x;
        tokenKind['Y'] = CncKWLexersym.Char_y;
        tokenKind['Z'] = CncKWLexersym.Char_z;
    };

    final int getKind(char c)
    {
        return (c < 128 ? tokenKind[c] : 0);
    }


    public CncKWLexer(char[] inputChars, int identifierKind)
    {
        this.inputChars = inputChars;
        keywordKind[0] = identifierKind;

        //
        // Rule 1:  KeyWord ::= e n v
        //
        keywordKind[1] = (CncParsersym.TK_T_ENV);

        //
        // Rule 2:  KeyWord ::= s t r u c t
        //
        keywordKind[2] = (CncParsersym.TK_T_STRUCT);

        //
        // Rule 3:  KeyWord ::= u n s i g n e d
        //
        keywordKind[3] = (CncParsersym.TK_T_UNSIGNED);

        for (int i = 0; i < keywordKind.length; i++)
        {
            if (keywordKind[i] == 0)
                keywordKind[i] = identifierKind;
        }
    }
}

