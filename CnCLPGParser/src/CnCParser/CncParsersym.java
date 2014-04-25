
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser;

public interface CncParsersym {
    public final static int
      TK_SEMICOLON = 9,
      TK_RIGHT_ARROW = 13,
      TK_LEFT_ARROW = 14,
      TK_COLON_COLON = 22,
      TK_COMMA = 2,
      TK_LESS_THAN = 15,
      TK_GREATER_THAN = 19,
      TK_COLON = 16,
      TK_LEFT_PARENTHESIS = 10,
      TK_RIGHT_PARENTHESIS = 20,
      TK_LEFT_BRACKET = 3,
      TK_RIGHT_BRACKET = 17,
      TK_LEFT_BRACE = 4,
      TK_RIGHT_BRACE = 11,
      TK_EQUAL = 23,
      TK_AMPERSAND = 29,
      TK_STAR = 5,
      TK_DOT = 24,
      TK_DOT_DOT = 21,
      TK_PLUS = 6,
      TK_MINUS = 7,
      TK_SLASH = 18,
      TK_SHARP = 30,
      TK_ATSIGN = 25,
      TK_T_ENV = 12,
      TK_T_UNSIGNED = 26,
      TK_T_STRUCT = 27,
      TK_EOF_TOKEN = 28,
      TK_T_NAME = 1,
      TK_T_NUMBER = 8,
      TK_T_QUOTEDVAL = 31,
      TK_ERROR_TOKEN = 32;

    public final static String orderedTerminalSymbols[] = {
                 "",
                 "T_NAME",
                 "COMMA",
                 "LEFT_BRACKET",
                 "LEFT_BRACE",
                 "STAR",
                 "PLUS",
                 "MINUS",
                 "T_NUMBER",
                 "SEMICOLON",
                 "LEFT_PARENTHESIS",
                 "RIGHT_BRACE",
                 "T_ENV",
                 "RIGHT_ARROW",
                 "LEFT_ARROW",
                 "LESS_THAN",
                 "COLON",
                 "RIGHT_BRACKET",
                 "SLASH",
                 "GREATER_THAN",
                 "RIGHT_PARENTHESIS",
                 "DOT_DOT",
                 "COLON_COLON",
                 "EQUAL",
                 "DOT",
                 "ATSIGN",
                 "T_UNSIGNED",
                 "T_STRUCT",
                 "EOF_TOKEN",
                 "AMPERSAND",
                 "SHARP",
                 "T_QUOTEDVAL",
                 "ERROR_TOKEN"
             };

    public final static int numTokenKinds = orderedTerminalSymbols.length;
    public final static boolean isValidForParser = true;
}
