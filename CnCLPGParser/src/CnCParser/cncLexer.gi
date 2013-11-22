--
-- The Java Lexer
--
%Options fp=CncLexer
%options single-productions
%options package=CnCParser
%options template=LexerTemplateF.gi
%options filter=cncKWLexer.gi

%Notice
/.
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//
./
%End

%Define
    --
    -- Definition of macro used in the included file LexerBasicMapB.g
    --
    $kw_lexer_class /.$cncKWLexer./
    $_IDENTIFIER    /.$_T_NAME./

%End

%Include
    LexerBasicMapF.gi
%End

%Export

    T_NAME
    T_NUMBER
    T_QUOTEDVAL

    SEMICOLON
    RIGHT_ARROW
    LEFT_ARROW
    COLON_COLON
    COMMA
    LESS_THAN
    GREATER_THAN
    COLON
    LEFT_PARENTHESIS
    RIGHT_PARENTHESIS
    LEFT_BRACKET
    RIGHT_BRACKET
    LEFT_BRACE
    RIGHT_BRACE
    EQUAL
    AMPERSAND
    STAR
    DOT
    DOT_DOT
    PLUS
    MINUS
    SLASH
    SHARP
    ATSIGN
	--UNSIGNED
    --STRUCT

%End

%Terminals
    CtlCharNotWS

    LF   CR   HT   FF

    a    b    c    d    e    f    g    h    i    j    k    l    m
    n    o    p    q    r    s    t    u    v    w    x    y    z
    _

    A    B    C    D    E    F    G    H    I    J    K    L    M
    N    O    P    Q    R    S    T    U    V    W    X    Y    Z

    0    1    2    3    4    5    6    7    8    9

    AfterASCII   ::= '\u0080..\ufffe'
    Space        ::= ' '
    LF           ::= NewLine
    CR           ::= Return
    HT           ::= HorizontalTab
    FF           ::= FormFeed
    DoubleQuote  ::= '"'
    SingleQuote  ::= "'"
    Percent      ::= '%'
    VerticalBar  ::= '|'
    Exclamation  ::= '!'
    AtSign       ::= '@'
    BackQuote    ::= '`'
    Tilde        ::= '~'
    Sharp        ::= '#'
    DollarSign   ::= '$'
    Ampersand    ::= '&'
    Caret        ::= '^'
    Colon        ::= ':'
    SemiColon    ::= ';'
    BackSlash    ::= '\'
    LeftBrace    ::= '{'
    RightBrace   ::= '}'
    LeftBracket  ::= '['
    RightBracket ::= ']'
    QuestionMark ::= '?'
    Comma        ::= ','
    Dot          ::= '.'
    LessThan     ::= '<'
    GreaterThan  ::= '>'
    Plus         ::= '+'
    Minus        ::= '-'
    Slash        ::= '/'
    Star         ::= '*'
    LeftParen    ::= '('
    RightParen   ::= ')'
    Equal        ::= '='
    -- Unsigned	 ::= "unsigned"
    -- Struct		 ::= "struct"

%End

%Start
    Token
%End

%Rules

    ---------------------  Rules for Scanned Tokens --------------------------------
    -- The lexer creates an array list of tokens which is defined in the PrsStream class.
    -- A token has three attributes: a start offset, an end offset and a kind.
    -- 
    -- Only rules that produce complete tokens have actions to create token objects.
    -- When making a token, calls to the methods, $getToken(1) and $getRightSpan(), 
    -- provide the offsets (i.e. the span) of a rule's right hand side (rhs) and thus of the token.
    -- For a rule of the form A ::= A1 A2 ... An, the start offset of the rhs of A is given by
    -- $getToken(1) or by $getLeftSpan() and the end offset by $getRightSpan().
    --  
    -- Regarding rules for parsing in general, note that for a rhs symbol Ai, the 
    -- method $getToken(i) returns the location of the leftmost character derived from Ai.  
    -- The method $getLeftSpan(i) returns the same location unless Ai produces %Empty in which case
    -- it returns the location of the last character derived before reducing Ai to %Empty. 
    -- The method $getRightSpan(i) returns the location of the rightmost character derived from Ai 
    -- unless Ai produces %Empty in which case it returns the location of the last character 
    -- derived before reducing Ai to %Empty.
    --------------------------------------------------------------------------------
    Token ::= ';'
        /.
                    makeToken($_SEMICOLON);
        ./

    Token ::= '-' '>'
        /.
                    makeToken($_RIGHT_ARROW);
        ./

    Token ::= '<' '-'
        /.
                    makeToken($_LEFT_ARROW);
        ./

    Token ::= ':' ':'
        /.
                    makeToken($_COLON_COLON);
        ./

    Token ::= ','
        /.
                    makeToken($_COMMA);
        ./

    Token ::= '<'
        /.
                    makeToken($_LESS_THAN);
        ./

    Token ::= '>'
        /.
                    makeToken($_GREATER_THAN);
        ./

    Token ::= ':'
        /.
                    makeToken($_COLON);
        ./

    Token ::= '('
        /.
                    makeToken($_LEFT_PARENTHESIS);
        ./

    Token ::= ')'
        /.
                    makeToken($_RIGHT_PARENTHESIS);
        ./

    Token ::= '['
        /.
                    makeToken($_LEFT_BRACKET);
        ./

    Token ::= ']'
        /.
                    makeToken($_RIGHT_BRACKET);
        ./

	Token ::= '{'
        /.
                    makeToken($_LEFT_BRACE);
        ./

    Token ::= '}'
        /.
                    makeToken($_RIGHT_BRACE);
        ./
        
    Token ::= '='
        /.
                    makeToken($_EQUAL);
        ./

	Token ::= '@'
        /.
                    makeToken($_ATSIGN);
        ./
        
    Token ::= Identifier
        /.
                    checkForKeyWord();
        ./

    Token ::= '&'
        /.
                    makeToken($_AMPERSAND);
        ./

    Token ::= '*'
        /.
                    makeToken($_STAR);
        ./
        
    Token ::= '/'
        /.
                    makeToken($_SLASH);
        ./
	
	Token ::= '+'
        /.
                    makeToken($_PLUS);
        ./
        
    Token ::= '-'
        /.
                    makeToken($_MINUS);
        ./

    Token ::= '.'
        /.
                    makeToken($_DOT);
        ./
	
	Token ::= '.' '.'
        /.
                    makeToken($_DOT_DOT);
        ./
   
   	Token ::= '#'
        /.
                    makeToken($_SHARP);
        ./
    --Token ::= 'u' 'n' 's' 'i' 'g' 'n' 'e' 'd'
      --  /.
       --             makeToken($_UNSIGNED);
       -- ./
    --Token ::= 's' 't' 'r' 'u' 'c' 't'
      --  /.
        --            makeToken($_STRUCT);
        --./    
    
    Token ::= '"' SLBody '"'
        /.
                    makeToken($_T_QUOTEDVAL);
        ./

    Token ::= '"' SLBody Eol -- TODO: remove the Eol from the string
        /.
                    makeToken($_T_QUOTEDVAL);
        ./

    Token ::= Integer
        /.
                    makeToken($_T_NUMBER);
        ./
    Token ::= WS -- White Space is scanned but not added to output vector
        /.
                    skipToken();
        ./

    Token ::= SLC
        /.
                    skipToken();
        ./
       

    SLBody ::= %Empty
             | SLBody NotDQ

    SLC ::= '/' '/'
          | SLC NotEol

    NotEol -> Letter
            | Digit
            | Special
            | Space
            | HT
            | FF
            | CtlCharNotWS

    Special -> '+' | '-' | '*' | '/' | '(' | ')' | '"' | '!' | '@' | '`' | '~' |
               '%' | '&' | '^' | ':' | ';' | "'" | '\' | '|' | '{' | '}' |
               '[' | ']' | '?' | ',' | '.' | '<' | '>' | '=' | '#'

    SpecialNotDQ -> '+' | '-' | '*' | '/' | '(' | ')' | '!' | '@' | '`' | '~' |
                    '%' | '&' | '^' | ':' | ';' | "'" | '\' | '|' | '{' | '}' |
                    '[' | ']' | '?' | ',' | '.' | '<' | '>' | '=' | '#'

    Integer -> Digit
             | Integer Digit

    WSChar -> Space
            | Eol
            | HT
            | FF

    Eol -> LF
         | CR

    Letter -> LowerCaseLetter
            | UpperCaseLetter
            | _
            | '$'
            | '\u0080..\ufffe'

    LowerCaseLetter -> a | b | c | d | e | f | g | h | i | j | k | l | m |
                       n | o | p | q | r | s | t | u | v | w | x | y | z

    UpperCaseLetter -> A | B | C | D | E | F | G | H | I | J | K | L | M |
                       N | O | P | Q | R | S | T | U | V | W | X | Y | Z

    Digit -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

    WS -> WSChar
        | WS WSChar

    Identifier -> Letter
                | Identifier Letter
                | Identifier Digit

    NotDQ -> Letter
           | Digit
           | SpecialNotDQ
           | Space
           | HT
           | FF
%End
