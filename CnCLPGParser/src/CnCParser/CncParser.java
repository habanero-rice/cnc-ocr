
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser;

import CnCParser.Ast.*;
import lpg.runtime.*;

public class CncParser implements RuleAction
{
    private PrsStream prsStream = null;
    
    private boolean unimplementedSymbolsWarning = false;

    private static ParseTable prsTable = new CncParserprs();
    public ParseTable getParseTable() { return prsTable; }

    private DeterministicParser dtParser = null;
    public DeterministicParser getParser() { return dtParser; }

    private void setResult(Object object) { dtParser.setSym1(object); }
    public Object getRhsSym(int i) { return dtParser.getSym(i); }

    public int getRhsTokenIndex(int i) { return dtParser.getToken(i); }
    public IToken getRhsIToken(int i) { return prsStream.getIToken(getRhsTokenIndex(i)); }
    
    public int getRhsFirstTokenIndex(int i) { return dtParser.getFirstToken(i); }
    public IToken getRhsFirstIToken(int i) { return prsStream.getIToken(getRhsFirstTokenIndex(i)); }

    public int getRhsLastTokenIndex(int i) { return dtParser.getLastToken(i); }
    public IToken getRhsLastIToken(int i) { return prsStream.getIToken(getRhsLastTokenIndex(i)); }

    public int getLeftSpan() { return dtParser.getFirstToken(); }
    public IToken getLeftIToken()  { return prsStream.getIToken(getLeftSpan()); }

    public int getRightSpan() { return dtParser.getLastToken(); }
    public IToken getRightIToken() { return prsStream.getIToken(getRightSpan()); }

    public int getRhsErrorTokenIndex(int i)
    {
        int index = dtParser.getToken(i);
        IToken err = prsStream.getIToken(index);
        return (err instanceof ErrorToken ? index : 0);
    }
    public ErrorToken getRhsErrorIToken(int i)
    {
        int index = dtParser.getToken(i);
        IToken err = prsStream.getIToken(index);
        return (ErrorToken) (err instanceof ErrorToken ? err : null);
    }

    public void reset(ILexStream lexStream)
    {
        prsStream = new PrsStream(lexStream);
        dtParser.reset(prsStream);

        try
        {
            prsStream.remapTerminalSymbols(orderedTerminalSymbols(), prsTable.getEoftSymbol());
        }
        catch(NullExportedSymbolsException e) {
        }
        catch(NullTerminalSymbolsException e) {
        }
        catch(UnimplementedTerminalsException e)
        {
            if (unimplementedSymbolsWarning) {
                java.util.ArrayList unimplemented_symbols = e.getSymbols();
                System.out.println("The Lexer will not scan the following token(s):");
                for (int i = 0; i < unimplemented_symbols.size(); i++)
                {
                    Integer id = (Integer) unimplemented_symbols.get(i);
                    System.out.println("    " + CncParsersym.orderedTerminalSymbols[id.intValue()]);               
                }
                System.out.println();
            }
        }
        catch(UndefinedEofSymbolException e)
        {
            throw new Error(new UndefinedEofSymbolException
                                ("The Lexer does not implement the Eof symbol " +
                                 CncParsersym.orderedTerminalSymbols[prsTable.getEoftSymbol()]));
        }
    }
    
    public CncParser()
    {
        try
        {
            dtParser = new DeterministicParser(prsStream, prsTable, (RuleAction) this);
        }
        catch (NotDeterministicParseTableException e)
        {
            throw new Error(new NotDeterministicParseTableException
                                ("Regenerate CncParserprs.java with -NOBACKTRACK option"));
        }
        catch (BadParseSymFileException e)
        {
            throw new Error(new BadParseSymFileException("Bad Parser Symbol File -- CncParsersym.java. Regenerate CncParserprs.java"));
        }
    }

    public CncParser(ILexStream lexStream)
    {
        this();
        reset(lexStream);
    }

    public int numTokenKinds() { return CncParsersym.numTokenKinds; }
    public String[] orderedTerminalSymbols() { return CncParsersym.orderedTerminalSymbols; }
    public String getTokenKindName(int kind) { return CncParsersym.orderedTerminalSymbols[kind]; }            
    public int getEOFTokenKind() { return prsTable.getEoftSymbol(); }
    public IPrsStream getIPrsStream() { return prsStream; }

    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     *
     */
    public PrsStream getPrsStream() { return prsStream; }

    /**
     * @deprecated replaced by {@link #getIPrsStream()}
     *
     */
    public PrsStream getParseStream() { return prsStream; }

    public Ast parser()
    {
        return parser(null, 0);
    }
        
    public Ast parser(Monitor monitor)
    {
        return parser(monitor, 0);
    }
        
    public Ast parser(int error_repair_count)
    {
        return parser(null, error_repair_count);
    }
        
    public Ast parser(Monitor monitor, int error_repair_count)
    {
        dtParser.setMonitor(monitor);

        try
        {
            return (Ast) dtParser.parse();
        }
        catch (BadParseException e)
        {
            prsStream.reset(e.error_token); // point to error token

            DiagnoseParser diagnoseParser = new DiagnoseParser(prsStream, prsTable);
            diagnoseParser.diagnose(e.error_token);
        }

        return null;
    }

    //
    // Additional entry points, if any
    //
    

    public void ruleAction(int ruleNumber)
    {
        switch (ruleNumber)
        {

            //
            // Rule 1:  graph ::= statements
            //
            case 1:
                break;
            //
            // Rule 2:  statements ::= statement
            //
            case 2: {
                setResult(
                    new statementList((Istatement)getRhsSym(1), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 3:  statements ::= statements statement
            //
            case 3: {
                ((statementList)getRhsSym(1)).addElement((Istatement)getRhsSym(2));
                break;
            }
            //
            // Rule 4:  statement ::= terminated_declaration
            //
            case 4:
                break;
            //
            // Rule 5:  statement ::= terminated_relation
            //
            case 5:
                break;
            //
            // Rule 6:  terminated_declaration ::= declaration ;
            //
            case 6: {
                setResult(
                    new terminated_declaration(getLeftIToken(), getRightIToken(),
                                               (Ideclaration)getRhsSym(1))
                );
                break;
            }
            //
            // Rule 7:  declaration ::= item_declaration
            //
            case 7:
                break;
            //
            // Rule 8:  declaration ::= tag_declaration
            //
            case 8:
                break;
            //
            // Rule 9:  declaration ::= step_declaration
            //
            case 9:
                break;
            //
            // Rule 10:  terminated_relation ::= relation ;
            //
            case 10: {
                setResult(
                    new terminated_relation(getLeftIToken(), getRightIToken(),
                                            (Irelation)getRhsSym(1))
                );
                break;
            }
            //
            // Rule 11:  relation ::= step_execution
            //
            case 11:
                break;
            //
            // Rule 12:  relation ::= step_prescription
            //
            case 12:
                break;
            //
            // Rule 13:  step_execution ::= instance_list$inputList -> step_instance
            //
            case 13: {
                setResult(
                    new StepExecution(CncParser.this, getLeftIToken(), getRightIToken(),
                                      (instanceList)getRhsSym(1),
                                      (Istep_instance)getRhsSym(3),
                                      (instanceList)null)
                );
                break;
            }
            //
            // Rule 14:  step_execution ::= instance_list$inputList -> step_instance -> instance_list$outputList
            //
            case 14: {
                setResult(
                    new StepExecution(CncParser.this, getLeftIToken(), getRightIToken(),
                                      (instanceList)getRhsSym(1),
                                      (Istep_instance)getRhsSym(3),
                                      (instanceList)getRhsSym(5))
                );
                break;
            }
            //
            // Rule 15:  step_execution ::= step_instance <- instance_list$inputList
            //
            case 15: {
                setResult(
                    new StepExecution(CncParser.this, getLeftIToken(), getRightIToken(),
                                      (instanceList)getRhsSym(3),
                                      (Istep_instance)getRhsSym(1),
                                      (instanceList)null)
                );
                break;
            }
            //
            // Rule 16:  step_execution ::= instance_list$outputList <- step_instance
            //
            case 16: {
                setResult(
                    new StepExecution(CncParser.this, getLeftIToken(), getRightIToken(),
                                      (instanceList)null,
                                      (Istep_instance)getRhsSym(3),
                                      (instanceList)getRhsSym(1))
                );
                break;
            }
            //
            // Rule 17:  step_execution ::= instance_list$outputList <- step_instance <- instance_list$inputList
            //
            case 17: {
                setResult(
                    new StepExecution(CncParser.this, getLeftIToken(), getRightIToken(),
                                      (instanceList)getRhsSym(5),
                                      (Istep_instance)getRhsSym(3),
                                      (instanceList)getRhsSym(1))
                );
                break;
            }
            //
            // Rule 18:  step_execution ::= step_instance -> instance_list$outputList
            //
            case 18: {
                setResult(
                    new StepExecution(CncParser.this, getLeftIToken(), getRightIToken(),
                                      (instanceList)null,
                                      (Istep_instance)getRhsSym(1),
                                      (instanceList)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 19:  step_prescription ::= tag_instance :: step_instance_list
            //
            case 19: {
                setResult(
                    new StepPrescription(getLeftIToken(), getRightIToken(),
                                         (tag_instance)getRhsSym(1),
                                         (step_instance_affList)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 20:  instance_list ::= instance
            //
            case 20: {
                setResult(
                    new instanceList((Iinstance)getRhsSym(1), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 21:  instance_list ::= instance_list , instance
            //
            case 21: {
                ((instanceList)getRhsSym(1)).addElement((Iinstance)getRhsSym(3));
                break;
            }
            //
            // Rule 22:  instance ::= item_instance
            //
            case 22:
                break;
            //
            // Rule 23:  instance ::= tag_instance
            //
            case 23:
                break;
            //
            // Rule 24:  item_declaration ::= item_instance attribute_list_opt
            //
            case 24: {
                setResult(
                    new item_declaration(getLeftIToken(), getRightIToken(),
                                         (item_instance)getRhsSym(1),
                                         (attributeList)getRhsSym(2))
                );
                break;
            }
            //
            // Rule 25:  item_instance ::= [ item_definition tag_description_opt ]
            //
            case 25: {
                setResult(
                    new item_instance(getLeftIToken(), getRightIToken(),
                                      (item_definition)getRhsSym(2),
                                      (tag_componentList)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 26:  item_definition ::= item_type T_NAME$name
            //
            case 26: {
                setResult(
                    new item_definition(getLeftIToken(), getRightIToken(),
                                        (Iitem_type)getRhsSym(1),
                                        new AstToken(getRhsIToken(2)))
                );
                break;
            }
            //
            // Rule 27:  item_definition ::= T_NAME$name
            //
            case 27: {
                setResult(
                    new item_definition(getLeftIToken(), getRightIToken(),
                                        (Iitem_type)null,
                                        new AstToken(getRhsIToken(1)))
                );
                break;
            }
            //
            // Rule 28:  item_type ::= T_NAME
            //
            case 28: {
                setResult(
                    new item_type0(getRhsIToken(1))
                );
                break;
            }
            //
            // Rule 29:  item_type ::= T_UNSIGNED T_NAME
            //
            case 29: {
                setResult(
                    new item_type1(getLeftIToken(), getRightIToken())
                );
                break;
            }
            //
            // Rule 30:  item_type ::= T_STRUCT T_NAME
            //
            case 30: {
                setResult(
                    new item_type2(getLeftIToken(), getRightIToken())
                );
                break;
            }
            //
            // Rule 31:  item_type ::= item_type *
            //
            case 31: {
                setResult(
                    new PointerType(getLeftIToken(), getRightIToken(),
                                    (Iitem_type)getRhsSym(1))
                );
                break;
            }
            //
            // Rule 32:  tag_declaration ::= tag_instance attribute_list_opt
            //
            case 32: {
                setResult(
                    new tag_declaration(getLeftIToken(), getRightIToken(),
                                        (tag_instance)getRhsSym(1),
                                        (attributeList)getRhsSym(2))
                );
                break;
            }
            //
            // Rule 33:  tag_instance ::= < tag_definition tag_description_opt >
            //
            case 33: {
                setResult(
                    new tag_instance(getLeftIToken(), getRightIToken(),
                                     (tag_definition)getRhsSym(2),
                                     (tag_componentList)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 34:  tag_definition ::= tag_type T_NAME$name
            //
            case 34: {
                setResult(
                    new tag_definition(getLeftIToken(), getRightIToken(),
                                       (Itag_type)getRhsSym(1),
                                       new AstToken(getRhsIToken(2)))
                );
                break;
            }
            //
            // Rule 35:  tag_definition ::= T_NAME$name
            //
            case 35: {
                setResult(
                    new tag_definition(getLeftIToken(), getRightIToken(),
                                       (Itag_type)null,
                                       new AstToken(getRhsIToken(1)))
                );
                break;
            }
            //
            // Rule 36:  tag_description_opt ::= tag_description
            //
            case 36:
                break;
            //
            // Rule 37:  tag_description_opt ::= $Empty
            //
            case 37: {
                setResult(
                    new tag_componentList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 38:  tag_type ::= t_type
            //
            case 38: {
                setResult(
                    new tag_type(getLeftIToken(), getRightIToken(),
                                 (t_type)getRhsSym(1),
                                 (AstToken)null,
                                 (Itag_type)null)
                );
                break;
            }
            //
            // Rule 39:  tag_type ::= t_type [ T_NUMBER$dim ]
            //
            case 39: {
                setResult(
                    new tag_type(getLeftIToken(), getRightIToken(),
                                 (t_type)getRhsSym(1),
                                 new AstToken(getRhsIToken(3)),
                                 (Itag_type)null)
                );
                break;
            }
            //
            // Rule 40:  tag_type ::= tag_type . t_type
            //
            case 40: {
                setResult(
                    new tag_type(getLeftIToken(), getRightIToken(),
                                 (t_type)getRhsSym(3),
                                 (AstToken)null,
                                 (Itag_type)getRhsSym(1))
                );
                break;
            }
            //
            // Rule 41:  tag_description ::= : tag_component_list
            //
            case 41: {
                setResult((tag_componentList)getRhsSym(2));
                break;
            }
            //
            // Rule 42:  tag_component_list ::= tag_component
            //
            case 42: {
                setResult(
                    new tag_componentList((Itag_component)getRhsSym(1), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 43:  tag_component_list ::= tag_component_list , tag_component
            //
            case 43: {
                ((tag_componentList)getRhsSym(1)).addElement((Itag_component)getRhsSym(3));
                break;
            }
            //
            // Rule 44:  tag_component ::= t_type aritm_expr$expression
            //
            case 44: {
                setResult(
                    new tag_component(getLeftIToken(), getRightIToken(),
                                      (t_type)getRhsSym(1),
                                      (Iaritm_expr)getRhsSym(2),
                                      (Iaritm_expr)null,
                                      (Iaritm_expr)null)
                );
                break;
            }
            //
            // Rule 45:  tag_component ::= aritm_expr$expression
            //
            case 45: {
                setResult(
                    new tag_component(getLeftIToken(), getRightIToken(),
                                      (t_type)null,
                                      (Iaritm_expr)getRhsSym(1),
                                      (Iaritm_expr)null,
                                      (Iaritm_expr)null)
                );
                break;
            }
            //
            // Rule 46:  tag_component ::= { aritm_expr$start_range .. aritm_expr$stop_range }
            //
            case 46: {
                setResult(
                    new tag_component(getLeftIToken(), getRightIToken(),
                                      (t_type)null,
                                      (Iaritm_expr)null,
                                      (Iaritm_expr)getRhsSym(2),
                                      (Iaritm_expr)getRhsSym(4))
                );
                break;
            }
            //
            // Rule 47:  aritm_expr ::= aritm_expr$first +$operand aritm_term$second
            //
            case 47: {
                setResult(
                    new aritm_expr(getLeftIToken(), getRightIToken(),
                                   (Iaritm_expr)getRhsSym(1),
                                   new AstToken(getRhsIToken(2)),
                                   (Iaritm_term)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 48:  aritm_expr ::= aritm_expr$first -$operand aritm_term$second
            //
            case 48: {
                setResult(
                    new aritm_expr(getLeftIToken(), getRightIToken(),
                                   (Iaritm_expr)getRhsSym(1),
                                   new AstToken(getRhsIToken(2)),
                                   (Iaritm_term)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 49:  aritm_expr ::= aritm_term$second
            //
            case 49: {
                setResult(
                    new aritm_expr(getLeftIToken(), getRightIToken(),
                                   (Iaritm_expr)null,
                                   (AstToken)null,
                                   (Iaritm_term)getRhsSym(1))
                );
                break;
            }
            //
            // Rule 50:  aritm_term ::= aritm_term$first *$operand aritm_factor$second
            //
            case 50: {
                setResult(
                    new aritm_term(CncParser.this, getLeftIToken(), getRightIToken(),
                                   (Iaritm_term)getRhsSym(1),
                                   new AstToken(getRhsIToken(2)),
                                   (aritm_factor)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 51:  aritm_term ::= aritm_term$first /$operand aritm_factor$second
            //
            case 51: {
                setResult(
                    new aritm_term(CncParser.this, getLeftIToken(), getRightIToken(),
                                   (Iaritm_term)getRhsSym(1),
                                   new AstToken(getRhsIToken(2)),
                                   (aritm_factor)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 52:  aritm_term ::= aritm_factor$second
            //
            case 52: {
                setResult(
                    new aritm_term(CncParser.this, getLeftIToken(), getRightIToken(),
                                   (Iaritm_term)null,
                                   (AstToken)null,
                                   (aritm_factor)getRhsSym(1))
                );
                break;
            }
            //
            // Rule 53:  aritm_factor ::= T_NAME$name
            //
            case 53: {
                setResult(
                    new aritm_factor(CncParser.this, getLeftIToken(), getRightIToken(),
                                     new AstToken(getRhsIToken(1)),
                                     (Iaritm_expr)null,
                                     (AstToken)null)
                );
                break;
            }
            //
            // Rule 54:  aritm_factor ::= T_NAME$name [ aritm_expr$index ]
            //
            case 54: {
                setResult(
                    new aritm_factor(CncParser.this, getLeftIToken(), getRightIToken(),
                                     new AstToken(getRhsIToken(1)),
                                     (Iaritm_expr)getRhsSym(3),
                                     (AstToken)null)
                );
                break;
            }
            //
            // Rule 55:  aritm_factor ::= T_NUMBER$val
            //
            case 55: {
                setResult(
                    new aritm_factor(CncParser.this, getLeftIToken(), getRightIToken(),
                                     (AstToken)null,
                                     (Iaritm_expr)null,
                                     new AstToken(getRhsIToken(1)))
                );
                break;
            }
            //
            // Rule 56:  step_declaration ::= step_instance attribute_list_opt
            //
            case 56: {
                setResult(
                    new step_declaration(getLeftIToken(), getRightIToken(),
                                         (Istep_instance)getRhsSym(1),
                                         (attributeList)getRhsSym(2))
                );
                break;
            }
            //
            // Rule 57:  step_instance ::= ($step_type T_NAME$name step_description_opt )
            //
            case 57: {
                setResult(
                    new step_instance(getLeftIToken(), getRightIToken(),
                                      new AstToken(getRhsIToken(1)),
                                      new AstToken(getRhsIToken(2)),
                                      (step_componentList)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 58:  step_instance ::= {$step_type T_NAME$name step_description_opt }
            //
            case 58: {
                setResult(
                    new step_instance(getLeftIToken(), getRightIToken(),
                                      new AstToken(getRhsIToken(1)),
                                      new AstToken(getRhsIToken(2)),
                                      (step_componentList)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 59:  step_description_opt ::= step_description
            //
            case 59:
                break;
            //
            // Rule 60:  step_description_opt ::= $Empty
            //
            case 60: {
                setResult(
                    new step_componentList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 61:  step_description ::= : step_component_list
            //
            case 61: {
                setResult((step_componentList)getRhsSym(2));
                break;
            }
            //
            // Rule 62:  step_component_list ::= step_component
            //
            case 62: {
                setResult(
                    new step_componentList((step_component)getRhsSym(1), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 63:  step_component_list ::= step_component_list , step_component
            //
            case 63: {
                ((step_componentList)getRhsSym(1)).addElement((step_component)getRhsSym(3));
                break;
            }
            //
            // Rule 64:  step_component ::= t_type T_NAME$name
            //
            case 64: {
                setResult(
                    new step_component(getLeftIToken(), getRightIToken(),
                                       (t_type)getRhsSym(1),
                                       new AstToken(getRhsIToken(2)),
                                       (AstToken)null,
                                       (AstToken)null)
                );
                break;
            }
            //
            // Rule 65:  step_component ::= T_NAME$name
            //
            case 65: {
                setResult(
                    new step_component(getLeftIToken(), getRightIToken(),
                                       (t_type)null,
                                       new AstToken(getRhsIToken(1)),
                                       (AstToken)null,
                                       (AstToken)null)
                );
                break;
            }
            //
            // Rule 66:  step_component ::= { T_NAME$start_range .. T_NAME$end_range }
            //
            case 66: {
                setResult(
                    new step_component(getLeftIToken(), getRightIToken(),
                                       (t_type)null,
                                       (AstToken)null,
                                       new AstToken(getRhsIToken(2)),
                                       new AstToken(getRhsIToken(4)))
                );
                break;
            }
            //
            // Rule 67:  t_type ::= T_NAME
            //
            case 67: {
                setResult(
                    new t_type(getRhsIToken(1))
                );
                break;
            }
            //
            // Rule 68:  step_instance_list ::= step_instance_aff
            //
            case 68: {
                setResult(
                    new step_instance_affList((step_instance_aff)getRhsSym(1), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 69:  step_instance_list ::= step_instance_list , step_instance_aff
            //
            case 69: {
                ((step_instance_affList)getRhsSym(1)).addElement((step_instance_aff)getRhsSym(3));
                break;
            }
            //
            // Rule 70:  step_instance_aff ::= ($step_type T_NAME$name step_description_aff_opt )
            //
            case 70: {
                setResult(
                    new step_instance_aff(getLeftIToken(), getRightIToken(),
                                          new AstToken(getRhsIToken(1)),
                                          new AstToken(getRhsIToken(2)),
                                          (step_affinityList)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 71:  step_instance_aff ::= {$step_type T_NAME$name step_description_aff_opt }
            //
            case 71: {
                setResult(
                    new step_instance_aff(getLeftIToken(), getRightIToken(),
                                          new AstToken(getRhsIToken(1)),
                                          new AstToken(getRhsIToken(2)),
                                          (step_affinityList)getRhsSym(3))
                );
                break;
            }
            //
            // Rule 72:  step_description_aff_opt ::= step_description_aff
            //
            case 72:
                break;
            //
            // Rule 73:  step_description_aff_opt ::= $Empty
            //
            case 73: {
                setResult(
                    new step_affinityList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 74:  step_description_aff ::= @ step_affinity_list
            //
            case 74: {
                setResult((step_affinityList)getRhsSym(2));
                break;
            }
            //
            // Rule 75:  step_affinity_list ::= step_affinity
            //
            case 75: {
                setResult(
                    new step_affinityList((step_affinity)getRhsSym(1), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 76:  step_affinity_list ::= step_affinity_list , step_affinity
            //
            case 76: {
                ((step_affinityList)getRhsSym(1)).addElement((step_affinity)getRhsSym(3));
                break;
            }
            //
            // Rule 77:  step_affinity ::= T_NAME$name = T_NUMBER$val
            //
            case 77: {
                setResult(
                    new step_affinity(getLeftIToken(), getRightIToken(),
                                      new AstToken(getRhsIToken(1)),
                                      new AstToken(getRhsIToken(3)))
                );
                break;
            }
            //
            // Rule 78:  step_instance ::= T_ENV
            //
            case 78: {
                setResult(
                    new step_instance_environment(getRhsIToken(1))
                );
                break;
            }
            //
            // Rule 79:  attribute_list_opt ::= $Empty
            //
            case 79: {
                setResult(
                    new attributeList(getLeftIToken(), getRightIToken(), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 80:  attribute_list ::= attribute
            //
            case 80: {
                setResult(
                    new attributeList((Iattribute)getRhsSym(1), true /* left recursive */)
                );
                break;
            }
            //
            // Rule 81:  attribute_list ::= attribute_list , attribute
            //
            case 81: {
                ((attributeList)getRhsSym(1)).addElement((Iattribute)getRhsSym(3));
                break;
            }
            //
            // Rule 82:  attribute ::= T_NAME$name = T_NAME$value
            //
            case 82: {
                setResult(
                    new VariableAttribute(getLeftIToken(), getRightIToken(),
                                          new AstToken(getRhsIToken(1)),
                                          new AstToken(getRhsIToken(3)))
                );
                break;
            }
            //
            // Rule 83:  attribute ::= T_NAME$name = T_NUMBER$value
            //
            case 83: {
                setResult(
                    new IntegerAttribute(getLeftIToken(), getRightIToken(),
                                         new AstToken(getRhsIToken(1)),
                                         new AstToken(getRhsIToken(3)))
                );
                break;
            }
            //
            // Rule 84:  attribute ::= T_NAME$name = T_QUOTEDVAL$value
            //
            case 84: {
                setResult(
                    new StringAttribute(getLeftIToken(), getRightIToken(),
                                        new AstToken(getRhsIToken(1)),
                                        new AstToken(getRhsIToken(3)))
                );
                break;
            }
    
            default:
                break;
        }
        return;
    }
}

