
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

    public final static int LA_STATE_OFFSET = 373;
    public final int getLaStateOffset() { return LA_STATE_OFFSET; }

    public final static int MAX_LA = 1;
    public final int getMaxLa() { return MAX_LA; }

    public final static int NUM_RULES = 84;
    public final int getNumRules() { return NUM_RULES; }

    public final static int NUM_NONTERMINALS = 43;
    public final int getNumNonterminals() { return NUM_NONTERMINALS; }

    public final static int NUM_SYMBOLS = 75;
    public final int getNumSymbols() { return NUM_SYMBOLS; }

    public final static int SEGMENT_SIZE = 8192;
    public final int getSegmentSize() { return SEGMENT_SIZE; }

    public final static int START_STATE = 85;
    public final int getStartState() { return START_STATE; }

    public final static int IDENTIFIER_SYMBOL = 0;
    public final int getIdentifier_SYMBOL() { return IDENTIFIER_SYMBOL; }

    public final static int EOFT_SYMBOL = 28;
    public final int getEoftSymbol() { return EOFT_SYMBOL; }

    public final static int EOLT_SYMBOL = 9;
    public final int getEoltSymbol() { return EOLT_SYMBOL; }

    public final static int ACCEPT_ACTION = 288;
    public final int getAcceptAction() { return ACCEPT_ACTION; }

    public final static int ERROR_ACTION = 289;
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
            0,0,1,0,0,1,0,0,0,1,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0
        };
    };
    public final static byte isNullable[] = IsNullable.isNullable;
    public final boolean isNullable(int index) { return isNullable[index] != 0; }

    public interface ProsthesesIndex {
        public final static byte prosthesesIndex[] = {0,
            32,31,16,18,19,14,27,30,15,20,
            4,5,6,7,8,9,10,11,12,13,
            22,26,29,33,34,36,37,38,39,41,
            2,3,17,21,23,24,25,28,35,40,
            1,42,43
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
            3,1,1,4,1,2,4,4,1,0,
            2,1,3,2,1,5,1,1,3,4,
            4,1,0,2,1,3,3,1,0,1,
            3,3,3,3,-1,-17,-2,0,0,0,
            0,-59,-3,0,-4,0,0,0,0,0,
            0,0,0,0,0,-72,0,0,-13,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,-39,
            0,0,-66,0,0,-5,0,0,-19,0,
            0,0,0,0,0,-20,-10,-8,0,0,
            0,0,0,-46,0,0,0,0,0,0,
            -47,-6,-34,0,0,0,0,0,-14,0,
            -60,0,0,0,-55,0,0,-57,0,0,
            0,0,0,0,0,0,-18,-21,0,-67,
            0,0,-80,0,0,-25,-26,0,0,0,
            0,0,-61,-73,0,0,-64,-76,0,0,
            0,0,-15,0,-7,-9,-11,0,0,-87,
            -16,0,0,-12,0,0,0,-40,0,0,
            0,0,0,-22,0,-68,0,0,-69,0,
            -23,-24,-27,-28,-29,-30,-31,0,-32,0,
            -33,-35,-36,-37,-38,-41,-42,-43,-44,-45,
            -48,-49,-50,-51,-52,-53,-54,-56,-58,-62,
            -63,-65,-70,-71,-74,-75,-77,-78,-79,-81,
            -82,-83,-84,-85,-86,-88,0
        };
    };
    public final static byte baseCheck[] = BaseCheck.baseCheck;
    public final int baseCheck(int index) { return baseCheck[index]; }
    public final static byte rhs[] = baseCheck;
    public final int rhs(int index) { return rhs[index]; };

    public interface BaseAction {
        public final static char baseAction[] = {
            31,31,32,32,11,11,12,14,14,14,
            13,18,18,19,19,19,19,19,19,20,
            6,6,4,4,15,5,34,34,35,35,
            35,35,16,3,36,36,21,21,37,37,
            37,22,38,38,23,23,23,8,8,8,
            2,2,2,1,1,1,17,9,9,24,
            24,25,39,39,26,26,26,7,33,33,
            27,27,28,28,29,40,40,30,9,10,
            42,42,43,43,43,1,82,2,216,20,
            217,93,65,10,215,93,2,4,5,224,
            7,8,9,95,11,12,87,52,280,3,
            251,59,216,20,217,93,87,109,215,69,
            3,4,5,224,7,8,9,95,11,12,
            25,52,267,25,52,267,66,178,268,57,
            178,268,23,20,22,253,57,8,107,23,
            20,22,254,42,57,242,43,23,20,22,
            270,57,103,27,23,20,22,271,265,57,
            264,154,23,21,22,87,52,267,87,52,
            267,197,243,273,188,241,275,82,110,62,
            87,52,267,87,52,267,65,110,279,276,
            72,285,261,154,87,52,281,27,166,255,
            36,252,59,14,264,41,50,100,260,36,
            166,14,247,68,105,56,32,24,130,257,
            249,277,72,63,55,40,87,51,75,87,
            50,62,112,76,116,118,78,111,282,120,
            76,122,121,126,127,123,135,134,137,139,
            64,144,147,149,151,153,36,68,84,145,
            156,157,160,40,162,92,163,164,168,42,
            89,96,170,20,171,45,175,289,289
        };
    };
    public final static char baseAction[] = BaseAction.baseAction;
    public final int baseAction(int index) { return baseAction[index]; }
    public final static char lhs[] = baseAction;
    public final int lhs(int index) { return lhs[index]; };

    public interface TermCheck {
        public final static byte termCheck[] = {0,
            0,0,0,3,4,3,4,0,1,0,
            10,2,10,0,14,0,14,4,18,0,
            18,12,13,10,0,1,0,1,4,28,
            4,18,8,26,27,0,1,0,3,0,
            0,0,23,8,0,6,7,6,7,0,
            6,7,12,13,0,11,0,16,9,3,
            21,0,1,0,0,0,1,0,4,15,
            14,22,5,19,10,0,1,0,1,16,
            5,0,5,0,17,24,0,1,0,6,
            7,0,0,5,8,0,15,6,7,0,
            5,9,0,1,0,17,0,1,9,0,
            0,0,17,9,3,0,1,0,1,0,
            0,0,0,13,15,0,0,2,2,0,
            1,12,11,0,0,2,0,1,0,1,
            20,19,8,0,0,2,0,1,0,1,
            0,1,0,0,2,0,0,2,2,0,
            16,0,0,0,3,0,1,0,1,0,
            0,2,0,11,0,0,0,0,25,0,
            21,11,8,20,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0
        };
    };
    public final static byte termCheck[] = TermCheck.termCheck;
    public final int termCheck(int index) { return termCheck[index]; }

    public interface TermAction {
        public final static char termAction[] = {0,
            289,289,1,147,136,147,136,289,246,289,
            162,169,162,289,148,289,148,136,367,289,
            367,221,213,162,289,266,289,263,175,288,
            262,367,344,245,244,53,67,289,190,289,
            79,289,286,67,289,204,106,204,106,23,
            204,106,139,146,67,335,289,343,79,147,
            193,289,323,289,289,289,86,49,258,35,
            148,196,239,35,259,289,315,27,28,314,
            320,60,28,45,236,228,289,274,48,204,
            106,44,289,239,344,47,163,204,106,22,
            239,299,289,187,289,236,289,234,79,37,
            16,38,236,295,256,289,319,289,318,13,
            289,289,289,154,130,18,15,169,169,289,
            356,161,347,19,289,92,289,171,289,203,
            346,322,269,61,289,207,289,272,65,67,
            289,353,41,73,133,17,14,169,169,289,
            328,53,289,289,190,289,283,289,284,74,
            289,220,289,360,289,289,289,289,208,289,
            278,355,366,359
        };
    };
    public final static char termAction[] = TermAction.termAction;
    public final int termAction(int index) { return termAction[index]; }

    public interface Asb {
        public final static byte asb[] = {0,
            11,4,6,50,56,56,48,56,46,21,
            47,50,10,28,13,13,1,34,28,28,
            37,52,55,54,14,40,60,56,56,58,
            63,49,104,25,72,66,66,83,17,56,
            19,66,56,56,98,28,28,70,56,69,
            56,81,74,90,18,94,18,98,14,31,
            43,66,66,25,87,17,18,18,18,85,
            89,18,18,94,104,56,72,56,96,18,
            90,90,70,100,104,102,56,19
        };
    };
    public final static byte asb[] = Asb.asb;
    public final int asb(int index) { return asb[index]; }

    public interface Asr {
        public final static byte asr[] = {0,
            11,15,0,28,0,12,13,2,0,28,
            3,14,18,10,4,0,4,1,8,0,
            1,26,27,0,1,4,0,3,14,0,
            11,25,0,20,15,0,19,15,0,16,
            15,0,20,25,0,22,2,13,12,9,
            0,19,15,3,24,1,0,15,16,1,
            5,0,9,13,0,9,2,0,1,11,
            2,20,0,1,8,5,6,7,17,3,
            16,2,19,0,6,7,21,0,3,11,
            21,5,17,2,19,6,7,16,0,23,
            0,6,7,11,0
        };
    };
    public final static byte asr[] = Asr.asr;
    public final int asr(int index) { return asr[index]; }

    public interface Nasb {
        public final static byte nasb[] = {0,
            1,16,16,16,16,16,44,25,44,22,
            44,16,11,31,15,15,7,7,20,20,
            35,16,16,16,37,35,16,16,16,16,
            16,16,16,28,16,16,16,16,17,40,
            16,16,16,16,16,20,20,16,16,16,
            16,16,16,16,18,16,18,16,9,33,
            33,16,16,39,16,17,18,48,48,16,
            16,18,18,16,16,42,16,16,16,18,
            16,16,16,16,16,16,46,16
        };
    };
    public final static byte nasb[] = Nasb.nasb;
    public final int nasb(int index) { return nasb[index]; }

    public interface Nasr {
        public final static byte nasr[] = {0,
            32,5,3,9,18,0,24,0,27,0,
            5,3,18,11,9,0,7,2,0,6,
            0,35,34,0,7,36,0,7,39,0,
            4,0,28,0,21,0,33,0,26,7,
            0,40,0,10,0,30,0,1,0
        };
    };
    public final static byte nasr[] = Nasr.nasr;
    public final int nasr(int index) { return nasr[index]; }

    public interface TerminalIndex {
        public final static byte terminalIndex[] = {0,
            30,5,11,13,17,20,21,31,1,9,
            14,2,3,6,8,12,22,26,7,10,
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
            0,0,51,0,0,56,57,0,0,59,
            34,35,42,45,46,47,48,50,55,58,
            0,0,0
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
            16
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
            40,3,1,0,16,0
        };
    };
    public final static byte scopeRhs[] = ScopeRhs.scopeRhs;
    public final int scopeRhs(int index) { return scopeRhs[index]; }

    public interface ScopeState {
        public final static char scopeState[] = {0,
            193,204,106,239,236,190,133,178,175,130,
            0
        };
    };
    public final static char scopeState[] = ScopeState.scopeState;
    public final int scopeState(int index) { return scopeState[index]; }

    public interface InSymb {
        public final static byte inSymb[] = {0,
            0,63,38,50,4,10,41,14,35,3,
            37,46,64,2,13,12,1,1,12,13,
            68,1,69,39,22,66,67,27,26,1,
            41,41,56,15,56,38,38,53,15,24,
            3,65,4,10,53,13,12,71,4,1,
            39,70,1,34,4,40,39,8,2,1,
            1,38,38,2,1,2,3,17,5,40,
            1,7,6,40,60,25,60,21,40,21,
            34,34,72,1,1,40,2,23
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
