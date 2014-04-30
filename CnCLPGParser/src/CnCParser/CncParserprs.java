
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser;

public class CncParserprs implements lpg.runtime.ParseTable, CncParsersym {
    public final static int ERROR_SYMBOL = 32;
    public final int getErrorSymbol() { return ERROR_SYMBOL; }

    public final static int SCOPE_UBOUND = 0;
    public final int getScopeUbound() { return SCOPE_UBOUND; }

    public final static int SCOPE_SIZE = 1;
    public final int getScopeSize() { return SCOPE_SIZE; }

    public final static int MAX_NAME_LENGTH = 19;
    public final int getMaxNameLength() { return MAX_NAME_LENGTH; }

    public final static int NUM_STATES = 88;
    public final int getNumStates() { return NUM_STATES; }

    public final static int NT_OFFSET = 32;
    public final int getNtOffset() { return NT_OFFSET; }

    public final static int LA_STATE_OFFSET = 379;
    public final int getLaStateOffset() { return LA_STATE_OFFSET; }

    public final static int MAX_LA = 1;
    public final int getMaxLa() { return MAX_LA; }

    public final static int NUM_RULES = 86;
    public final int getNumRules() { return NUM_RULES; }

    public final static int NUM_NONTERMINALS = 44;
    public final int getNumNonterminals() { return NUM_NONTERMINALS; }

    public final static int NUM_SYMBOLS = 76;
    public final int getNumSymbols() { return NUM_SYMBOLS; }

    public final static int SEGMENT_SIZE = 8192;
    public final int getSegmentSize() { return SEGMENT_SIZE; }

    public final static int START_STATE = 87;
    public final int getStartState() { return START_STATE; }

    public final static int IDENTIFIER_SYMBOL = 0;
    public final int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

    public final static int EOFT_SYMBOL = 28;
    public final int getEoftSymbol() { return EOFT_SYMBOL; }

    public final static int EOLT_SYMBOL = 9;
    public final int getEoltSymbol() { return EOLT_SYMBOL; }

    public final static int ACCEPT_ACTION = 292;
    public final int getAcceptAction() { return ACCEPT_ACTION; }

    public final static int ERROR_ACTION = 293;
    public final int getErrorAction() { return ERROR_ACTION; }

    public final static boolean BACKTRACK = false;
    public final boolean getBacktrack() { return BACKTRACK; }

    public final int getStartSymbol() { return lhs(0); }
    public final boolean isValidForParser() { return CncParsersym.isValidForParser; }


    public interface IsNullable {
        public final static byte isNullable[] = {0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,1,0,0,0,0,0,0,0,0,
            0,0,1,0,0,0,1,0,0,0,
            1,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0
        };
    };
    public final static byte isNullable[] = IsNullable.isNullable;
    public final boolean isNullable(int index) { return isNullable[index] != 0; }

    public interface ProsthesesIndex {
        public final static byte prosthesesIndex[] = {0,
            32,31,16,18,19,14,27,30,15,20,
            4,5,6,7,8,9,10,11,12,13,
            22,26,29,33,34,35,37,38,39,40,
            42,2,3,17,21,23,24,25,28,36,
            41,1,43,44
        };
    };
    public final static byte prosthesesIndex[] = ProsthesesIndex.prosthesesIndex;
    public final int prosthesesIndex(int index) { return prosthesesIndex[index]; }

    public interface IsKeyword {
        public final static byte isKeyword[] = {0,
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
            1,1,2,1,1,2,1,1,1,2,
            1,1,3,5,3,3,5,3,3,1,
            3,1,1,2,4,2,1,1,2,2,
            2,2,4,2,1,1,0,1,4,3,
            2,1,3,2,1,5,3,3,1,3,
            3,1,1,4,1,2,1,1,4,4,
            1,0,2,1,3,2,1,5,1,1,
            3,4,4,1,0,2,1,3,3,1,
            0,1,3,3,3,3,-1,-17,-21,0,
            0,0,0,-59,-2,0,-3,0,0,0,
            0,0,0,0,0,0,0,-68,0,0,
            0,-13,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,-39,0,0,-66,0,0,-4,0,
            0,-19,0,0,0,0,0,0,-20,-87,
            -8,0,0,0,0,0,-46,0,0,0,
            0,0,0,-47,-10,-34,0,0,0,0,
            -14,0,0,0,0,0,-55,0,0,-25,
            0,-57,0,0,0,-18,-60,0,0,0,
            -61,-76,0,-67,0,0,-80,0,0,0,
            0,0,-26,-15,0,0,-5,0,-7,-6,
            0,0,0,0,-64,0,0,-12,0,0,
            0,0,0,0,0,-72,0,0,-73,0,
            0,-16,0,0,-9,-11,-40,-44,-69,0,
            0,0,-22,0,0,0,-23,-24,-27,-28,
            -29,-30,-31,-32,-33,-35,-36,-37,-38,-41,
            -42,0,-43,-45,-48,-49,-50,-51,-52,-53,
            -54,-56,-58,-62,-63,-65,-70,-71,-74,-75,
            -77,-78,-79,-81,-82,-83,-84,-85,-86,-88,
            0
        };
    };
    public final static byte baseCheck[] = BaseCheck.baseCheck;
    public final int baseCheck(int index) { return baseCheck[index]; }
    public final static byte rhs[] = baseCheck;
    public final int rhs(int index) { return rhs[index]; };

    public interface BaseAction {
        public final static char baseAction[] = {
            32,32,33,33,11,11,12,14,14,14,
            13,18,18,19,19,19,19,19,19,20,
            6,6,4,4,15,5,35,35,36,36,
            36,36,16,3,37,37,21,21,38,38,
            38,22,39,39,23,23,23,8,8,8,
            2,2,2,1,1,1,17,24,24,9,
            9,25,25,26,40,40,27,27,27,7,
            34,34,28,28,29,29,30,41,41,31,
            9,10,43,43,44,44,44,1,105,107,
            235,20,236,97,66,94,209,6,2,4,
            5,218,7,8,9,139,11,12,80,51,
            259,36,14,255,61,235,20,236,97,95,
            112,209,71,3,4,5,218,7,8,9,
            139,11,12,37,52,271,37,52,271,95,
            182,272,12,182,272,23,20,22,257,12,
            162,100,23,20,22,258,42,12,248,43,
            23,20,22,274,12,9,67,23,20,22,
            275,12,269,268,23,21,22,80,52,271,
            66,78,80,52,271,277,105,152,89,247,
            279,152,162,64,80,52,271,80,52,271,
            203,249,283,107,21,289,265,98,70,44,
            22,256,61,253,261,67,280,74,103,56,
            281,74,268,77,264,36,80,52,284,80,
            52,285,21,286,186,51,102,128,22,80,
            50,254,65,56,40,32,24,61,110,2,
            114,116,77,106,118,108,124,28,125,126,
            130,132,191,135,133,137,140,142,146,149,
            39,69,83,148,153,154,157,43,158,86,
            159,160,166,46,79,91,169,164,168,48,
            173,293,293
        };
    };
    public final static char baseAction[] = BaseAction.baseAction;
    public final int baseAction(int index) { return baseAction[index]; }
    public final static char lhs[] = baseAction;
    public final int lhs(int index) { return lhs[index]; };

    public interface TermCheck {
        public final static byte termCheck[] = {0,
            0,0,1,3,4,0,5,2,0,1,
            10,0,12,0,3,15,3,4,13,14,
            0,0,1,10,4,12,15,0,15,2,
            10,0,12,12,26,27,0,1,0,1,
            4,3,0,0,8,0,8,0,6,7,
            0,6,7,6,7,0,13,14,11,9,
            0,1,17,21,0,0,0,1,0,4,
            4,16,22,5,19,10,0,1,0,0,
            1,5,0,5,24,0,18,8,6,7,
            0,6,7,0,0,5,18,0,1,0,
            1,0,0,9,0,0,0,0,18,0,
            9,9,3,0,1,0,1,0,11,14,
            16,28,16,0,0,0,2,0,1,0,
            13,0,0,2,0,1,0,8,2,0,
            1,0,1,20,19,0,1,0,0,17,
            2,0,0,0,2,2,0,0,0,0,
            3,0,1,0,17,0,1,0,0,11,
            2,0,0,0,0,0,25,21,11,20,
            8,0,0,0,0,0,23,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0
        };
    };
    public final static byte termCheck[] = TermCheck.termCheck;
    public final int termCheck(int index) { return termCheck[index]; }

    public interface TermAction {
        public final static char termAction[] = {0,
            293,293,319,165,207,293,324,171,293,252,
            210,293,373,1,165,151,165,207,232,204,
            293,293,351,210,207,373,151,18,151,171,
            210,293,373,350,251,250,293,270,53,69,
            177,194,293,81,348,293,69,293,229,226,
            23,229,226,229,226,69,142,149,339,81,
            293,327,347,197,293,293,293,267,49,263,
            266,35,180,239,35,238,27,28,48,293,
            278,28,45,239,237,44,108,348,229,226,
            47,229,226,293,293,239,108,293,88,293,
            243,22,293,303,62,16,37,293,108,38,
            81,299,260,293,323,293,322,13,353,157,
            166,292,133,293,15,293,171,293,362,293,
            164,19,293,94,293,187,63,273,215,293,
            276,67,69,352,326,293,359,293,41,318,
            136,75,17,14,171,171,293,53,293,293,
            194,293,287,293,332,293,288,293,76,366,
            150,293,293,293,293,293,192,282,361,365,
            372,293,293,293,293,293,290
        };
    };
    public final static char termAction[] = TermAction.termAction;
    public final int termAction(int index) { return termAction[index]; }

    public interface Asb {
        public final static byte asb[] = {0,
            14,7,9,53,59,46,51,59,49,24,
            50,53,13,31,16,16,1,34,31,31,
            4,55,58,57,17,43,63,59,59,61,
            66,52,107,28,75,69,69,86,20,59,
            22,69,59,46,101,31,31,73,59,72,
            59,84,77,93,21,97,21,101,17,37,
            40,69,69,28,90,20,21,21,21,88,
            92,21,21,97,107,59,75,59,99,21,
            93,93,73,103,107,105,59,22
        };
    };
    public final static byte asb[] = Asb.asb;
    public final int asb(int index) { return asb[index]; }

    public interface Asr {
        public final static byte asr[] = {0,
            11,16,0,19,16,0,28,0,13,14,
            2,0,28,3,15,12,10,4,0,4,
            1,8,0,1,26,27,0,1,4,0,
            3,15,0,20,16,0,11,25,0,20,
            25,0,17,16,0,12,1,0,22,2,
            14,13,9,0,19,16,3,24,1,0,
            16,17,1,5,0,9,14,0,9,2,
            0,1,11,2,20,0,1,8,5,6,
            7,18,3,17,2,19,0,6,7,21,
            0,3,11,21,5,18,2,19,6,7,
            17,0,23,0,6,7,11,0
        };
    };
    public final static byte asr[] = Asr.asr;
    public final int asr(int index) { return asr[index]; }

    public interface Nasb {
        public final static byte nasb[] = {0,
            1,20,20,20,20,47,45,28,45,31,
            45,20,15,37,19,19,7,7,24,24,
            9,20,20,20,39,9,20,20,20,20,
            20,20,20,34,20,20,20,20,21,50,
            20,20,20,47,20,24,24,20,20,20,
            20,20,20,20,22,20,22,20,11,41,
            41,20,20,49,20,21,22,13,13,20,
            20,22,22,20,20,43,20,20,20,22,
            20,20,20,20,20,20,26,20
        };
    };
    public final static byte nasb[] = Nasb.nasb;
    public final int nasb(int index) { return nasb[index]; }

    public interface Nasr {
        public final static byte nasr[] = {0,
            33,5,3,9,18,0,25,0,21,0,
            28,0,1,0,5,3,18,11,9,0,
            7,2,0,6,0,31,0,7,37,0,
            36,35,0,7,40,0,4,0,34,0,
            29,0,41,0,10,0,24,0,27,7,
            0
        };
    };
    public final static byte nasr[] = Nasr.nasr;
    public final int nasr(int index) { return nasr[index]; }

    public interface TerminalIndex {
        public final static byte terminalIndex[] = {0,
            30,5,11,13,17,20,21,31,1,9,
            14,26,2,3,6,8,12,22,7,10,
            19,4,15,18,24,27,28,29,16,23,
            32,33
        };
    };
    public final static byte terminalIndex[] = TerminalIndex.terminalIndex;
    public final int terminalIndex(int index) { return terminalIndex[index]; }

    public interface NonterminalIndex {
        public final static byte nonterminalIndex[] = {0,
            54,53,41,43,44,39,49,52,40,0,
            36,0,0,37,0,0,0,38,0,0,
            0,0,51,55,0,0,57,58,0,0,
            60,34,35,42,45,46,47,48,50,56,
            59,0,0,0
        };
    };
    public final static byte nonterminalIndex[] = NonterminalIndex.nonterminalIndex;
    public final int nonterminalIndex(int index) { return nonterminalIndex[index]; }

    public interface ScopePrefix {
        public final static byte scopePrefix[] = {
            1
        };
    };
    public final static byte scopePrefix[] = ScopePrefix.scopePrefix;
    public final int scopePrefix(int index) { return scopePrefix[index]; }

    public interface ScopeSuffix {
        public final static byte scopeSuffix[] = {
            5
        };
    };
    public final static byte scopeSuffix[] = ScopeSuffix.scopeSuffix;
    public final int scopeSuffix(int index) { return scopeSuffix[index]; }

    public interface ScopeLhs {
        public final static byte scopeLhs[] = {
            1
        };
    };
    public final static byte scopeLhs[] = ScopeLhs.scopeLhs;
    public final int scopeLhs(int index) { return scopeLhs[index]; }

    public interface ScopeLa {
        public final static byte scopeLa[] = {
            17
        };
    };
    public final static byte scopeLa[] = ScopeLa.scopeLa;
    public final int scopeLa(int index) { return scopeLa[index]; }

    public interface ScopeStateSet {
        public final static byte scopeStateSet[] = {
            1
        };
    };
    public final static byte scopeStateSet[] = ScopeStateSet.scopeStateSet;
    public final int scopeStateSet(int index) { return scopeStateSet[index]; }

    public interface ScopeRhs {
        public final static byte scopeRhs[] = {0,
            40,3,1,0,17,0
        };
    };
    public final static byte scopeRhs[] = ScopeRhs.scopeRhs;
    public final int scopeRhs(int index) { return scopeRhs[index]; }

    public interface ScopeState {
        public final static char scopeState[] = {0,
            197,229,226,239,108,194,136,182,177,133,
            0
        };
    };
    public final static char scopeState[] = ScopeState.scopeState;
    public final int scopeState(int index) { return scopeState[index]; }

    public interface InSymb {
        public final static byte inSymb[] = {0,
            0,64,38,50,4,10,41,15,35,3,
            37,46,65,2,14,13,1,56,13,14,
            69,1,70,39,22,67,68,27,26,1,
            41,41,57,16,57,38,38,53,16,24,
            3,66,4,10,53,14,13,72,4,1,
            39,71,1,34,4,40,39,8,2,1,
            56,38,38,2,1,2,3,18,5,40,
            1,7,6,40,61,25,61,21,40,21,
            34,34,73,1,1,40,2,23
        };
    };
    public final static byte inSymb[] = InSymb.inSymb;
    public final int inSymb(int index) { return inSymb[index]; }

    public interface Name {
        public final static String name[] = {
            "",
            ";",
            "->",
            "<-",
            "::",
            ",",
            "<",
            ">",
            ":",
            "(",
            ")",
            "[",
            "]",
            "{",
            "}",
            "=",
            "&",
            "*",
            ".",
            "..",
            "+",
            "-",
            "/",
            "#",
            "@",
            "$empty",
            "T_ENV",
            "T_UNSIGNED",
            "T_STRUCT",
            "EOF_TOKEN",
            "T_NAME",
            "T_NUMBER",
            "T_QUOTEDVAL",
            "ERROR_TOKEN",
            "graph",
            "statements",
            "statement",
            "declaration",
            "relation",
            "instance_list",
            "step_instance",
            "tag_instance",
            "step_instance_list",
            "instance",
            "item_instance",
            "item_definition",
            "item_type",
            "tag_definition",
            "tag_type",
            "t_type",
            "tag_component_list",
            "tag_component",
            "aritm_expr",
            "aritm_term",
            "aritm_factor",
            "step_instance_name",
            "step_component_list",
            "step_component",
            "step_instance_aff",
            "step_affinity_list",
            "step_affinity"
        };
    };
    public final static String name[] = Name.name;
    public final String name(int index) { return name[index]; }

    public final int originalState(int state) {
        return -baseCheck[state];
    }
    public final int asi(int state) {
        return asb[originalState(state)];
    }
    public final int nasi(int state) {
        return nasb[originalState(state)];
    }
    public final int inSymbol(int state) {
        return inSymb[originalState(state)];
    }

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
