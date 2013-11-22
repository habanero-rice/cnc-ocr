
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser;

import lpg.runtime.*;

public class CncLexer implements RuleAction
{
    private CncLexerLpgLexStream lexStream;
    
    private static ParseTable prs = new CncLexerprs();
    public ParseTable getParseTable() { return prs; }

    private LexParser lexParser = new LexParser();
    public LexParser getParser() { return lexParser; }

    public int getToken(int i) { return lexParser.getToken(i); }
    public int getRhsFirstTokenIndex(int i) { return lexParser.getFirstToken(i); }
    public int getRhsLastTokenIndex(int i) { return lexParser.getLastToken(i); }

    public int getLeftSpan() { return lexParser.getToken(1); }
    public int getRightSpan() { return lexParser.getLastToken(); }

    public void resetKeywordLexer()
    {
        if (kwLexer == null)
              this.kwLexer = new CncKWLexer(lexStream.getInputChars(), CncParsersym.TK_T_NAME);
        else this.kwLexer.setInputChars(lexStream.getInputChars());
    }

    public void reset(String filename, int tab) throws java.io.IOException
    {
        lexStream = new CncLexerLpgLexStream(filename, tab);
        lexParser.reset((ILexStream) lexStream, prs, (RuleAction) this);
        resetKeywordLexer();
    }

    public void reset(char[] input_chars, String filename)
    {
        reset(input_chars, filename, 1);
    }
    
    public void reset(char[] input_chars, String filename, int tab)
    {
        lexStream = new CncLexerLpgLexStream(input_chars, filename, tab);
        lexParser.reset((ILexStream) lexStream, prs, (RuleAction) this);
        resetKeywordLexer();
    }
    
    public CncLexer(String filename, int tab) throws java.io.IOException 
    {
        reset(filename, tab);
    }

    public CncLexer(char[] input_chars, String filename, int tab)
    {
        reset(input_chars, filename, tab);
    }

    public CncLexer(char[] input_chars, String filename)
    {
        reset(input_chars, filename, 1);
    }

    public CncLexer() {}

    public ILexStream getILexStream() { return lexStream; }

    /**
     * @deprecated replaced by {@link #getILexStream()}
     */
    public ILexStream getLexStream() { return lexStream; }

    private void initializeLexer(IPrsStream prsStream, int start_offset, int end_offset)
    {
        if (lexStream.getInputChars() == null)
            throw new NullPointerException("LexStream was not initialized");
        lexStream.setPrsStream(prsStream);
        prsStream.makeToken(start_offset, end_offset, 0); // Token list must start with a bad token
    }

    private void addEOF(IPrsStream prsStream, int end_offset)
    {
        prsStream.makeToken(end_offset, end_offset, CncParsersym.TK_EOF_TOKEN); // and end with the end of file token
        prsStream.setStreamLength(prsStream.getSize());
    }

    public void lexer(IPrsStream prsStream)
    {
        lexer(null, prsStream);
    }
    
    public void lexer(Monitor monitor, IPrsStream prsStream)
    {
        initializeLexer(prsStream, 0, -1);
        lexParser.parseCharacters(monitor);  // Lex the input characters
        addEOF(prsStream, lexStream.getStreamIndex());
    }

    public void lexer(IPrsStream prsStream, int start_offset, int end_offset)
    {
        lexer(null, prsStream, start_offset, end_offset);
    }
    
    public void lexer(Monitor monitor, IPrsStream prsStream, int start_offset, int end_offset)
    {
        if (start_offset <= 1)
             initializeLexer(prsStream, 0, -1);
        else initializeLexer(prsStream, start_offset - 1, start_offset - 1);

        lexParser.parseCharacters(monitor, start_offset, end_offset);

        addEOF(prsStream, (end_offset >= lexStream.getStreamIndex() ? lexStream.getStreamIndex() : end_offset + 1));
    }

    /**
     * If a parse stream was not passed to this Lexical analyser then we
     * simply report a lexical error. Otherwise, we produce a bad token.
     */
    public void reportLexicalError(int startLoc, int endLoc) {
        IPrsStream prs_stream = lexStream.getIPrsStream();
        if (prs_stream == null)
            lexStream.reportLexicalError(startLoc, endLoc);
        else {
            //
            // Remove any token that may have been processed that fall in the
            // range of the lexical error... then add one error token that spans
            // the error range.
            //
            for (int i = prs_stream.getSize() - 1; i > 0; i--) {
                if (prs_stream.getStartOffset(i) >= startLoc)
                     prs_stream.removeLastToken();
                else break;
            }
            prs_stream.makeToken(startLoc, endLoc, 0); // add an error token to the prsStream
        }        
    }

    //
    // The Lexer contains an array of characters as the input stream to be parsed.
    // There are methods to retrieve and classify characters.
    // The lexparser "token" is implemented simply as the index of the next character in the array.
    // The Lexer extends the abstract class LpgLexStream with an implementation of the abstract
    // method getKind.  The template defines the Lexer class and the lexer() method.
    // A driver creates the action class, "Lexer", passing an Option object to the constructor.
    //
    CncKWLexer kwLexer;
    boolean printTokens;
    private final static int ECLIPSE_TAB_VALUE = 4;

    public int [] getKeywordKinds() { return kwLexer.getKeywordKinds(); }

    public CncLexer(String filename) throws java.io.IOException
    {
        this(filename, ECLIPSE_TAB_VALUE);
        this.kwLexer = new CncKWLexer(lexStream.getInputChars(), CncParsersym.TK_T_NAME);
    }

    /**
     * @deprecated function replaced by {@link #reset(char [] content, String filename)}
     */
    public void initialize(char [] content, String filename)
    {
        reset(content, filename);
    }
    
    final void makeToken(int left_token, int right_token, int kind)
    {
        lexStream.makeToken(left_token, right_token, kind);
    }
    
    final void makeToken(int kind)
    {
        int startOffset = getLeftSpan(),
            endOffset = getRightSpan();
        lexStream.makeToken(startOffset, endOffset, kind);
        if (printTokens) printValue(startOffset, endOffset);
    }

    final void makeComment(int kind)
    {
        int startOffset = getLeftSpan(),
            endOffset = getRightSpan();
        lexStream.getIPrsStream().makeAdjunct(startOffset, endOffset, kind);
    }

    final void skipToken()
    {
        if (printTokens) printValue(getLeftSpan(), getRightSpan());
    }
    
    final void checkForKeyWord()
    {
        int startOffset = getLeftSpan(),
            endOffset = getRightSpan(),
            kwKind = kwLexer.lexer(startOffset, endOffset);
        lexStream.makeToken(startOffset, endOffset, kwKind);
        if (printTokens) printValue(startOffset, endOffset);
    }
    
    //
    // This flavor of checkForKeyWord is necessary when the default kind
    // (which is returned when the keyword filter doesn't match) is something
    // other than _IDENTIFIER.
    //
    final void checkForKeyWord(int defaultKind)
    {
        int startOffset = getLeftSpan(),
            endOffset = getRightSpan(),
            kwKind = kwLexer.lexer(startOffset, endOffset);
        if (kwKind == CncParsersym.TK_T_NAME)
            kwKind = defaultKind;
        lexStream.makeToken(startOffset, endOffset, kwKind);
        if (printTokens) printValue(startOffset, endOffset);
    }
    
    final void printValue(int startOffset, int endOffset)
    {
        String s = new String(lexStream.getInputChars(), startOffset, endOffset - startOffset + 1);
        System.out.print(s);
    }

    //
    //
    //
    static class CncLexerLpgLexStream extends LpgLexStream
    {
    public final static int tokenKind[] =
    {
        CncLexersym.Char_CtlCharNotWS,    // 000    0x00
        CncLexersym.Char_CtlCharNotWS,    // 001    0x01
        CncLexersym.Char_CtlCharNotWS,    // 002    0x02
        CncLexersym.Char_CtlCharNotWS,    // 003    0x03
        CncLexersym.Char_CtlCharNotWS,    // 004    0x04
        CncLexersym.Char_CtlCharNotWS,    // 005    0x05
        CncLexersym.Char_CtlCharNotWS,    // 006    0x06
        CncLexersym.Char_CtlCharNotWS,    // 007    0x07
        CncLexersym.Char_CtlCharNotWS,    // 008    0x08
        CncLexersym.Char_HT,              // 009    0x09
        CncLexersym.Char_LF,              // 010    0x0A
        CncLexersym.Char_CtlCharNotWS,    // 011    0x0B
        CncLexersym.Char_FF,              // 012    0x0C
        CncLexersym.Char_CR,              // 013    0x0D
        CncLexersym.Char_CtlCharNotWS,    // 014    0x0E
        CncLexersym.Char_CtlCharNotWS,    // 015    0x0F
        CncLexersym.Char_CtlCharNotWS,    // 016    0x10
        CncLexersym.Char_CtlCharNotWS,    // 017    0x11
        CncLexersym.Char_CtlCharNotWS,    // 018    0x12
        CncLexersym.Char_CtlCharNotWS,    // 019    0x13
        CncLexersym.Char_CtlCharNotWS,    // 020    0x14
        CncLexersym.Char_CtlCharNotWS,    // 021    0x15
        CncLexersym.Char_CtlCharNotWS,    // 022    0x16
        CncLexersym.Char_CtlCharNotWS,    // 023    0x17
        CncLexersym.Char_CtlCharNotWS,    // 024    0x18
        CncLexersym.Char_CtlCharNotWS,    // 025    0x19
        CncLexersym.Char_CtlCharNotWS,    // 026    0x1A
        CncLexersym.Char_CtlCharNotWS,    // 027    0x1B
        CncLexersym.Char_CtlCharNotWS,    // 028    0x1C
        CncLexersym.Char_CtlCharNotWS,    // 029    0x1D
        CncLexersym.Char_CtlCharNotWS,    // 030    0x1E
        CncLexersym.Char_CtlCharNotWS,    // 031    0x1F
        CncLexersym.Char_Space,           // 032    0x20
        CncLexersym.Char_Exclamation,     // 033    0x21
        CncLexersym.Char_DoubleQuote,     // 034    0x22
        CncLexersym.Char_Sharp,           // 035    0x23
        CncLexersym.Char_DollarSign,      // 036    0x24
        CncLexersym.Char_Percent,         // 037    0x25
        CncLexersym.Char_Ampersand,       // 038    0x26
        CncLexersym.Char_SingleQuote,     // 039    0x27
        CncLexersym.Char_LeftParen,       // 040    0x28
        CncLexersym.Char_RightParen,      // 041    0x29
        CncLexersym.Char_Star,            // 042    0x2A
        CncLexersym.Char_Plus,            // 043    0x2B
        CncLexersym.Char_Comma,           // 044    0x2C
        CncLexersym.Char_Minus,           // 045    0x2D
        CncLexersym.Char_Dot,             // 046    0x2E
        CncLexersym.Char_Slash,           // 047    0x2F
        CncLexersym.Char_0,               // 048    0x30
        CncLexersym.Char_1,               // 049    0x31
        CncLexersym.Char_2,               // 050    0x32
        CncLexersym.Char_3,               // 051    0x33
        CncLexersym.Char_4,               // 052    0x34
        CncLexersym.Char_5,               // 053    0x35
        CncLexersym.Char_6,               // 054    0x36
        CncLexersym.Char_7,               // 055    0x37
        CncLexersym.Char_8,               // 056    0x38
        CncLexersym.Char_9,               // 057    0x39
        CncLexersym.Char_Colon,           // 058    0x3A
        CncLexersym.Char_SemiColon,       // 059    0x3B
        CncLexersym.Char_LessThan,        // 060    0x3C
        CncLexersym.Char_Equal,           // 061    0x3D
        CncLexersym.Char_GreaterThan,     // 062    0x3E
        CncLexersym.Char_QuestionMark,    // 063    0x3F
        CncLexersym.Char_AtSign,          // 064    0x40
        CncLexersym.Char_A,               // 065    0x41
        CncLexersym.Char_B,               // 066    0x42
        CncLexersym.Char_C,               // 067    0x43
        CncLexersym.Char_D,               // 068    0x44
        CncLexersym.Char_E,               // 069    0x45
        CncLexersym.Char_F,               // 070    0x46
        CncLexersym.Char_G,               // 071    0x47
        CncLexersym.Char_H,               // 072    0x48
        CncLexersym.Char_I,               // 073    0x49
        CncLexersym.Char_J,               // 074    0x4A
        CncLexersym.Char_K,               // 075    0x4B
        CncLexersym.Char_L,               // 076    0x4C
        CncLexersym.Char_M,               // 077    0x4D
        CncLexersym.Char_N,               // 078    0x4E
        CncLexersym.Char_O,               // 079    0x4F
        CncLexersym.Char_P,               // 080    0x50
        CncLexersym.Char_Q,               // 081    0x51
        CncLexersym.Char_R,               // 082    0x52
        CncLexersym.Char_S,               // 083    0x53
        CncLexersym.Char_T,               // 084    0x54
        CncLexersym.Char_U,               // 085    0x55
        CncLexersym.Char_V,               // 086    0x56
        CncLexersym.Char_W,               // 087    0x57
        CncLexersym.Char_X,               // 088    0x58
        CncLexersym.Char_Y,               // 089    0x59
        CncLexersym.Char_Z,               // 090    0x5A
        CncLexersym.Char_LeftBracket,     // 091    0x5B
        CncLexersym.Char_BackSlash,       // 092    0x5C
        CncLexersym.Char_RightBracket,    // 093    0x5D
        CncLexersym.Char_Caret,           // 094    0x5E
        CncLexersym.Char__,               // 095    0x5F
        CncLexersym.Char_BackQuote,       // 096    0x60
        CncLexersym.Char_a,               // 097    0x61
        CncLexersym.Char_b,               // 098    0x62
        CncLexersym.Char_c,               // 099    0x63
        CncLexersym.Char_d,               // 100    0x64
        CncLexersym.Char_e,               // 101    0x65
        CncLexersym.Char_f,               // 102    0x66
        CncLexersym.Char_g,               // 103    0x67
        CncLexersym.Char_h,               // 104    0x68
        CncLexersym.Char_i,               // 105    0x69
        CncLexersym.Char_j,               // 106    0x6A
        CncLexersym.Char_k,               // 107    0x6B
        CncLexersym.Char_l,               // 108    0x6C
        CncLexersym.Char_m,               // 109    0x6D
        CncLexersym.Char_n,               // 110    0x6E
        CncLexersym.Char_o,               // 111    0x6F
        CncLexersym.Char_p,               // 112    0x70
        CncLexersym.Char_q,               // 113    0x71
        CncLexersym.Char_r,               // 114    0x72
        CncLexersym.Char_s,               // 115    0x73
        CncLexersym.Char_t,               // 116    0x74
        CncLexersym.Char_u,               // 117    0x75
        CncLexersym.Char_v,               // 118    0x76
        CncLexersym.Char_w,               // 119    0x77
        CncLexersym.Char_x,               // 120    0x78
        CncLexersym.Char_y,               // 121    0x79
        CncLexersym.Char_z,               // 122    0x7A
        CncLexersym.Char_LeftBrace,       // 123    0x7B
        CncLexersym.Char_VerticalBar,     // 124    0x7C
        CncLexersym.Char_RightBrace,      // 125    0x7D
        CncLexersym.Char_Tilde,           // 126    0x7E

        CncLexersym.Char_AfterASCII,      // for all chars in range 128..65534
        CncLexersym.Char_EOF              // for '\uffff' or 65535 
    };
            
    public final int getKind(int i)  // Classify character at ith location
    {
        int c = (i >= getStreamLength() ? '\uffff' : getCharValue(i));
        return (c < 128 // ASCII Character
                  ? tokenKind[c]
                  : c == '\uffff'
                       ? CncLexersym.Char_EOF
                       : CncLexersym.Char_AfterASCII);
    }

    public String[] orderedExportedSymbols() { return CncParsersym.orderedTerminalSymbols; }

    public CncLexerLpgLexStream(String filename, int tab) throws java.io.IOException
    {
        super(filename, tab);
    }

    public CncLexerLpgLexStream(char[] input_chars, String filename, int tab)
    {
        super(input_chars, filename, tab);
    }

    public CncLexerLpgLexStream(char[] input_chars, String filename)
    {
        super(input_chars, filename, 1);
    }
    }

    public void ruleAction(int ruleNumber)
    {
        switch(ruleNumber)
        {

            //
            // Rule 1:  Token ::= ;
            //
            case 1: { 
            
                makeToken(CncParsersym.TK_SEMICOLON);
                break;
            }
            //
            // Rule 2:  Token ::= - >
            //
            case 2: { 
            
                makeToken(CncParsersym.TK_RIGHT_ARROW);
                break;
            }
            //
            // Rule 3:  Token ::= < -
            //
            case 3: { 
            
                makeToken(CncParsersym.TK_LEFT_ARROW);
                break;
            }
            //
            // Rule 4:  Token ::= : :
            //
            case 4: { 
            
                makeToken(CncParsersym.TK_COLON_COLON);
                break;
            }
            //
            // Rule 5:  Token ::= ,
            //
            case 5: { 
            
                makeToken(CncParsersym.TK_COMMA);
                break;
            }
            //
            // Rule 6:  Token ::= <
            //
            case 6: { 
            
                makeToken(CncParsersym.TK_LESS_THAN);
                break;
            }
            //
            // Rule 7:  Token ::= >
            //
            case 7: { 
            
                makeToken(CncParsersym.TK_GREATER_THAN);
                break;
            }
            //
            // Rule 8:  Token ::= :
            //
            case 8: { 
            
                makeToken(CncParsersym.TK_COLON);
                break;
            }
            //
            // Rule 9:  Token ::= (
            //
            case 9: { 
            
                makeToken(CncParsersym.TK_LEFT_PARENTHESIS);
                break;
            }
            //
            // Rule 10:  Token ::= )
            //
            case 10: { 
            
                makeToken(CncParsersym.TK_RIGHT_PARENTHESIS);
                break;
            }
            //
            // Rule 11:  Token ::= [
            //
            case 11: { 
            
                makeToken(CncParsersym.TK_LEFT_BRACKET);
                break;
            }
            //
            // Rule 12:  Token ::= ]
            //
            case 12: { 
            
                makeToken(CncParsersym.TK_RIGHT_BRACKET);
                break;
            }
            //
            // Rule 13:  Token ::= {
            //
            case 13: { 
            
                makeToken(CncParsersym.TK_LEFT_BRACE);
                break;
            }
            //
            // Rule 14:  Token ::= }
            //
            case 14: { 
            
                makeToken(CncParsersym.TK_RIGHT_BRACE);
                break;
            }
            //
            // Rule 15:  Token ::= =
            //
            case 15: { 
            
                makeToken(CncParsersym.TK_EQUAL);
                break;
            }
            //
            // Rule 16:  Token ::= @
            //
            case 16: { 
            
                makeToken(CncParsersym.TK_ATSIGN);
                break;
            }
            //
            // Rule 17:  Token ::= Identifier
            //
            case 17: { 
            
                checkForKeyWord();
                break;
            }
            //
            // Rule 18:  Token ::= &
            //
            case 18: { 
            
                makeToken(CncParsersym.TK_AMPERSAND);
                break;
            }
            //
            // Rule 19:  Token ::= *
            //
            case 19: { 
            
                makeToken(CncParsersym.TK_STAR);
                break;
            }
            //
            // Rule 20:  Token ::= /
            //
            case 20: { 
            
                makeToken(CncParsersym.TK_SLASH);
                break;
            }
            //
            // Rule 21:  Token ::= +
            //
            case 21: { 
            
                makeToken(CncParsersym.TK_PLUS);
                break;
            }
            //
            // Rule 22:  Token ::= -
            //
            case 22: { 
            
                makeToken(CncParsersym.TK_MINUS);
                break;
            }
            //
            // Rule 23:  Token ::= .
            //
            case 23: { 
            
                makeToken(CncParsersym.TK_DOT);
                break;
            }
            //
            // Rule 24:  Token ::= . .
            //
            case 24: { 
            
                makeToken(CncParsersym.TK_DOT_DOT);
                break;
            }
            //
            // Rule 25:  Token ::= #
            //
            case 25: { 
            
                makeToken(CncParsersym.TK_SHARP);
                break;
            }
            //
            // Rule 26:  Token ::= " SLBody "
            //
            case 26: { 
            
                makeToken(CncParsersym.TK_T_QUOTEDVAL);
                break;
            }
            //
            // Rule 27:  Token ::= " SLBody Eol
            //
            case 27: { 
            
                makeToken(CncParsersym.TK_T_QUOTEDVAL);
                break;
            }
            //
            // Rule 28:  Token ::= Integer
            //
            case 28: { 
            
                makeToken(CncParsersym.TK_T_NUMBER);
                break;
            }
            //
            // Rule 29:  Token ::= WS
            //
            case 29: { 
            
                skipToken();
                break;
            }
            //
            // Rule 30:  Token ::= SLC
            //
            case 30: { 
            
                skipToken();
                break;
            }
    
            default:
                break;
        }
        return;
    }
}

