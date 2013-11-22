
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser;

public class CncLexerprs implements lpg.runtime.ParseTable, CncLexersym {
    public final static int ERROR_SYMBOL = 0;
    public final int getErrorSymbol() { return ERROR_SYMBOL; }

    public final static int SCOPE_UBOUND = 0;
    public final int getScopeUbound() { return SCOPE_UBOUND; }

    public final static int SCOPE_SIZE = 0;
    public final int getScopeSize() { return SCOPE_SIZE; }

    public final static int MAX_NAME_LENGTH = 0;
    public final int getMaxNameLength() { return MAX_NAME_LENGTH; }

    public final static int NUM_STATES = 16;
    public final int getNumStates() { return NUM_STATES; }

    public final static int NT_OFFSET = 102;
    public final int getNtOffset() { return NT_OFFSET; }

    public final static int LA_STATE_OFFSET = 423;
    public final int getLaStateOffset() { return LA_STATE_OFFSET; }

    public final static int MAX_LA = 1;
    public final int getMaxLa() { return MAX_LA; }

    public final static int NUM_RULES = 186;
    public final int getNumRules() { return NUM_RULES; }

    public final static int NUM_NONTERMINALS = 17;
    public final int getNumNonterminals() { return NUM_NONTERMINALS; }

    public final static int NUM_SYMBOLS = 119;
    public final int getNumSymbols() { return NUM_SYMBOLS; }

    public final static int SEGMENT_SIZE = 8192;
    public final int getSegmentSize() { return SEGMENT_SIZE; }

    public final static int START_STATE = 187;
    public final int getStartState() { return START_STATE; }

    public final static int IDENTIFIER_SYMBOL = 0;
    public final int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

    public final static int EOFT_SYMBOL = 74;
    public final int getEoftSymbol() { return EOFT_SYMBOL; }

    public final static int EOLT_SYMBOL = 103;
    public final int getEoltSymbol() { return EOLT_SYMBOL; }

    public final static int ACCEPT_ACTION = 236;
    public final int getAcceptAction() { return ACCEPT_ACTION; }

    public final static int ERROR_ACTION = 237;
    public final int getErrorAction() { return ERROR_ACTION; }

    public final static boolean BACKTRACK = false;
    public final boolean getBacktrack() { return BACKTRACK; }

    public final int getStartSymbol() { return lhs(0); }
    public final boolean isValidForParser() { return CncLexersym.isValidForParser; }


    public interface IsNullable {
        public final static byte isNullable[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            1,0,0,0,0,0,0,0,0
        };
    };
    public final static byte isNullable[] = IsNullable.isNullable;
    public final boolean isNullable(int index) { return isNullable[index] != 0; }

    public interface ProsthesesIndex {
        public final static byte prosthesesIndex[] = {0,
            12,11,16,17,5,15,2,3,4,6,
            7,8,9,10,13,14,1
        };
    };
    public final static byte prosthesesIndex[] = ProsthesesIndex.prosthesesIndex;
    public final int prosthesesIndex(int index) { return prosthesesIndex[index]; }

    public interface IsKeyword {
        public final static byte isKeyword[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0
        };
    };
    public final static byte isKeyword[] = IsKeyword.isKeyword;
    public final boolean isKeyword(int index) { return isKeyword[index] != 0; }

    public interface BaseCheck {
        public final static byte baseCheck[] = {0,
            1,2,2,2,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,2,1,3,3,1,1,1,
            0,2,2,2,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,2,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,2,2,
            1,1,1,1,1,1
        };
    };
    public final static byte baseCheck[] = BaseCheck.baseCheck;
    public final int baseCheck(int index) { return baseCheck[index]; }
    public final static byte rhs[] = baseCheck;
    public final int rhs(int index) { return rhs[index]; };

    public interface BaseAction {
        public final static char baseAction[] = {
            7,7,7,7,7,7,7,7,7,7,
            7,7,7,7,7,7,7,7,7,7,
            7,7,7,7,7,7,7,7,7,7,
            7,9,9,12,12,14,14,14,14,14,
            14,14,15,15,15,15,15,15,15,15,
            15,15,15,15,15,15,15,15,15,15,
            15,15,15,15,15,15,15,15,15,15,
            15,15,16,16,16,16,16,16,16,16,
            16,16,16,16,16,16,16,16,16,16,
            16,16,16,16,16,16,16,16,16,16,
            16,10,10,6,6,6,6,5,5,2,
            2,2,2,2,3,3,3,3,3,3,
            3,3,3,3,3,3,3,3,3,3,
            3,3,3,3,3,3,3,3,3,3,
            4,4,4,4,4,4,4,4,4,4,
            4,4,4,4,4,4,4,4,4,4,
            4,4,4,4,4,4,1,1,1,1,
            1,1,1,1,1,1,11,11,8,8,
            8,13,13,13,13,13,13,206,233,232,
            232,232,234,234,196,222,310,214,212,206,
            1,32,32,32,32,27,103,34,34,34,
            34,311,379,32,368,102,32,177,177,75,
            34,34,299,180,179,179,179,366,200,380,
            382,383,385,386,387,237,237
        };
    };
    public final static char baseAction[] = BaseAction.baseAction;
    public final int baseAction(int index) { return baseAction[index]; }
    public final static char lhs[] = baseAction;
    public final int lhs(int index) { return lhs[index]; };

    public interface TermCheck {
        public final static byte termCheck[] = {0,
            0,1,2,3,4,5,6,7,8,9,
            10,11,12,13,14,15,16,17,18,19,
            20,21,22,23,24,25,26,27,28,29,
            30,31,32,33,34,35,36,37,38,39,
            40,41,42,43,44,45,46,47,48,49,
            50,51,52,53,54,55,56,57,58,59,
            60,61,62,63,64,65,66,67,68,69,
            70,71,72,73,0,75,76,77,78,79,
            80,81,82,83,84,85,86,87,88,89,
            90,91,92,93,94,95,96,97,98,99,
            100,101,0,1,2,3,4,5,6,7,
            8,9,10,11,12,13,14,15,16,17,
            18,19,20,21,22,23,24,25,26,27,
            28,29,30,31,32,33,34,35,36,37,
            38,39,40,41,42,43,44,45,46,47,
            48,49,50,51,52,53,54,55,56,57,
            58,59,60,61,62,63,64,65,66,67,
            68,69,70,71,72,73,0,0,0,77,
            78,79,80,81,82,83,84,85,86,87,
            88,89,90,91,92,93,94,95,96,97,
            98,99,100,101,102,0,1,2,3,4,
            5,6,7,8,9,10,11,12,13,14,
            15,16,17,18,19,20,21,22,23,24,
            25,26,27,28,29,30,31,32,33,34,
            35,36,37,38,39,40,41,42,43,44,
            45,46,47,48,49,50,51,52,53,54,
            55,56,57,58,59,60,61,62,63,64,
            65,66,67,68,69,70,71,72,73,0,
            75,76,77,78,79,80,81,82,83,84,
            85,86,87,88,89,90,91,92,0,1,
            2,3,4,5,6,7,8,9,10,0,
            0,13,14,15,16,17,18,19,20,21,
            22,23,24,25,26,27,28,29,30,31,
            32,33,34,35,36,37,38,39,40,41,
            42,43,44,45,46,47,48,49,50,51,
            52,53,54,55,56,57,58,59,60,61,
            62,63,64,65,66,0,68,0,1,2,
            3,4,5,6,7,8,9,10,0,0,
            70,0,0,74,0,0,0,0,0,11,
            12,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,69,0,0,0,0,0,
            0,0,0,0,0,67,0,0,0,0,
            0,72,71,75,76,73,0,0,74,74,
            74,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0
        };
    };
    public final static byte termCheck[] = TermCheck.termCheck;
    public final int termCheck(int index) { return termCheck[index]; }

    public interface TermAction {
        public final static char termAction[] = {0,
            237,269,269,269,269,269,269,269,269,269,
            269,269,269,269,269,269,269,269,269,269,
            269,269,269,269,269,269,269,269,269,269,
            269,269,269,269,269,269,269,269,269,269,
            269,269,269,269,269,269,269,269,269,269,
            269,269,269,269,269,269,269,269,269,269,
            269,269,269,269,269,269,269,269,269,269,
            269,269,269,269,31,264,264,263,269,269,
            269,269,269,269,269,269,269,269,269,269,
            269,269,269,269,269,269,269,269,269,269,
            269,269,30,271,271,271,271,271,271,271,
            271,271,271,271,271,271,271,271,271,271,
            271,271,271,271,271,271,271,271,271,271,
            271,271,271,271,271,271,271,271,271,271,
            271,271,271,271,271,271,271,271,271,271,
            271,271,271,271,271,271,271,271,271,271,
            271,271,271,271,271,271,271,271,271,271,
            271,271,271,271,271,271,237,237,237,271,
            271,271,271,271,271,271,271,271,271,271,
            271,271,271,271,271,271,271,271,271,271,
            271,271,271,271,271,237,233,233,233,233,
            233,233,233,233,233,233,234,234,232,232,
            232,232,232,232,232,232,232,232,232,232,
            232,232,232,232,232,232,232,232,232,232,
            232,232,232,232,232,232,232,232,232,232,
            232,232,232,232,232,232,232,232,232,232,
            232,232,232,232,232,232,232,232,232,232,
            232,232,234,232,227,211,244,230,231,237,
            234,234,219,253,262,255,238,250,251,248,
            249,242,229,258,256,246,247,252,17,417,
            417,417,417,417,417,417,417,417,417,237,
            23,416,416,416,416,416,416,416,416,416,
            416,416,416,416,416,416,416,416,416,416,
            416,416,416,416,416,416,416,416,416,416,
            416,416,416,416,416,416,416,416,416,416,
            416,416,416,416,416,416,416,416,416,416,
            416,416,416,416,416,8,416,28,339,339,
            339,339,339,339,339,339,339,339,29,6,
            261,22,20,236,178,101,176,237,237,414,
            414,237,237,237,237,237,237,237,237,237,
            237,237,237,237,237,237,237,237,237,237,
            237,237,237,237,237,237,237,237,237,237,
            237,237,237,237,237,237,237,237,237,237,
            237,237,237,237,241,237,237,237,237,237,
            237,237,237,237,237,414,237,237,237,237,
            237,240,239,414,414,270,237,237,17,28,
            29
        };
    };
    public final static char termAction[] = TermAction.termAction;
    public final int termAction(int index) { return termAction[index]; }
    public final int asb(int index) { return 0; }
    public final int asr(int index) { return 0; }
    public final int nasb(int index) { return 0; }
    public final int nasr(int index) { return 0; }
    public final int terminalIndex(int index) { return 0; }
    public final int nonterminalIndex(int index) { return 0; }
    public final int scopePrefix(int index) { return 0;}
    public final int scopeSuffix(int index) { return 0;}
    public final int scopeLhs(int index) { return 0;}
    public final int scopeLa(int index) { return 0;}
    public final int scopeStateSet(int index) { return 0;}
    public final int scopeRhs(int index) { return 0;}
    public final int scopeState(int index) { return 0;}
    public final int inSymb(int index) { return 0;}
    public final String name(int index) { return null; }
    public final int originalState(int state) { return 0; }
    public final int asi(int state) { return 0; }
    public final int nasi(int state) { return 0; }
    public final int inSymbol(int state) { return 0; }

    /**
     * assert(! goto_default);
     */
    public final int ntAction(int state, int sym) {
        return baseAction[state + sym];
    }

    /**
     * assert(! shift_default);
     */
    public final int tAction(int state, int sym) {
        int i = baseAction[state],
            k = i + sym;
        return termAction[termCheck[k] == sym ? k : i];
    }
    public final int lookAhead(int la_state, int sym) {
        int k = la_state + sym;
        return termAction[termCheck[k] == sym ? k : la_state];
    }
}
