Eclipse Users:

    Checkout the latest version of LPG from SourceForge using CVS at the location
    :pserver:anonymous@lpg.cvs.sourceforge.net:/cvsroot/lpg
    To make it easy, check out all the packages. Among other things, this will setup
    an LPG launcher for you in the tool box (Round Green circle with white arrow and
    the little red tool box next to it).
    
    To run LPG on the cncParser.g file, simply highlight it, go to to the toolbox drop-down
    menu and select LPG.
    
    Note that the CnC LPG parser requires the lpg.runtime package (lpg.runtime.java folder).
    So, if you create a Java project for it don't forget to add a (Java build path) dependence
    on it to lpg.runtime.java.
    
    Also, you might want to check out the IMP plugin. It contains an IDE for LPG
    that makes it easier to edit LPG input files. You can download it from here:
   
        http://download.eclipse.org/technology/imp/updates
   
    If you are unable to download it right away, it might be because your environment
    does not yet have some other plugins ("Buckminster core" and "Buckminster optional")
    that IMP depends on. Download them too.

CnC Parser:

    Only the input files (cncParser.g, cncLexer.gi cncKWLexer.gi, CnCGenerator.java, Option.java,
    Main.java) can be modified. The others are generated when LPG is run with cncParser.g as
    input.
    
LPG info

    LPG accepts BNF format as input with some additional features that will be discussed later. The
    user can use one of two approaches in order to produce his AST.
    
    One approach (which was NOT used for the CnC parser) is to implement the AST classes by hand and
    generate them with the parser's help by associating action blocks of code to be executed when a
    rule is reduced.
    
    The second approach (used for CnC) is to request that LPG generate the ASTs automatically from the
    grammar specification.
    
    When LPG is instructed to automatically generate ASTs, it starts by associating each nonterminal A
    with an interface IA. The interface IA extends interface IX for each nonterminal X such that X ::= A. 
    The terminal symbols are associated with the class AstToken.
    
    Roughly speaking LPG automatically generates ASTs as follows:
    
       . a rule of the form A ::= %Empty produces null.
       . a rule of the form A ::= a, where a is a terminal symbol, produces a class that extends AstToken
       . a rule of the form A ::= B inherits the class generated for B (ok, since IA extends IB)
       . In general, a rule of the form A ::= x1, x2, ... xn, n > 1, generates a class with n private
         fields (_x1, ..., _xn) and n get functions (getx1(), ... getxn()).
      
    Note that the user can request that LPG generate fields in the AST nodes for terminal symbols only
    or nonterminal symbols only or for both. For example, in the CNC parser, we requested that LPG only
    generate fields for the nonterminals. The user can also suppress the generation of a field for a 
    symbol or force a field to be generated for a symbol that was to be ignored by properly "naming" it. 
    
    The user can specify the name to be assigned to a field or a class. However, if he does not do
    so, a default name is assigned. The rule for naming these elements is as follows:
    
       . the name of a symbol is used as the default name of the field. If there is a "conflict", an
         error is emitted and the generator stops. A conflict occurs when two or more symbols on the
         right-hand side of a rule have the same name. For example, the two occurrences of the symbol
         Statement in the right-hand side of this rule are in conflict:
         
                 Statement ::= "if" expr "then" Statement "else" Statement

         To override the name of a symbol on the right-hand side, we simply specify the new name after it
         preceded by a $. For example, 

                 Statement ::= IF expr THEN Statement$trueStatement ELSE Statement$falseStatement
                 
         produces a class with the fields: IF, expr, THEN, trueStatement, ELSE, and falseStatement.
         Note that if we had named the keywords using lower case symbols, we would have needed to override
         them also as these names conflict with keywords of the same name in Java. The user can also request
         that a field not be generated at all for a symbol by associating it with the null name. For example,
         
                 Statement ::= IF$ expr THEN$ Statement$trueStatement ELSE$ Statement$falseStatement
                 
         will produce a class with the fields: expr, trueStatement, and falseStatement.

       . If there is only a single rule associated with a nonterminal A then "A" will be the name of the
         class associated with that rule. If more than one rule is associated with a nonterminal A then
         the classes generated for these rules are named: A0, A1, A2, ... and so forth. The user can
         override the name of a class by adding a name after the left-hand side nonterminal preceded
         with $. For example, assuming that the following 3 rules are the only rules associated with
         the nonterminal "attribute":
         
             attribute ::= T_NAME$name '=' T_NAME$value 
             attribute ::= T_NAME$name '=' T_NUMBER$value
             attribute ::= T_NAME$name '=' T_QUOTEDVAL$value
         
         LPG will generate three classes for these rules that are named (in order or appearance):
         attribute0, attribute1, attribute2.
         
         The user can override these names as in the following example: 
         
             attribute$VariableAttribute ::= T_NAME$name '=' T_NAME$value 
             attribute$IntegerAttribute  ::= T_NAME$name '=' T_NUMBER$value
             attribute$StringAttribute   ::= T_NAME$name '=' T_QUOTEDVAL$value
       
    The user can also specify that a list (typed or untyped) be generated for a rule. Consider the rules:
    
        StatementList ::= %Empty
                        | StatementList Statement

    As specified (and assuming that no other rule is associated with StatementList), LPG would generate
    null for the first rule and for the second rule, it would generate a class StatementList with two
    fields called StatementList and Statement. However, the user can instruct LPG to generate a list of
    statements for these rules as follows:
    
        StatementList $ $Statement ::= %Empty
                                     | StatementList Statement
    
    In general, the left-hand side of a rule consists of three elements: the first is the nonterminal
    symbol of the grammar, the second is a $-escaped name to be associated with the class and the third
    is a $-escaped name that, if present, indicates that the class is a list and identifies the type of the
    elements of the list. (Note that the space between the names is optional). We could have written the
    rules above as follows:
    
        StatementList$$Statement ::= %Empty
                                   | StatementList Statement
                                   
    When the second element is the null-escaped symbol, it indicates that we are happy with the default
    name. If the third element is the null-escaped symbol, it indicates that the list is untyped. When
    LPG is instructed to construct a list, it looks on the right-hand side of the rule for symbols that
    are either list elements of that type or lists themselves. If the rule is the empty list, then it
    creates an empty list of the type specified. If it only finds a list on the right-hand side, then
    the left-hand side will inherit that list. If it finds a list and an element, the element is added
    to the list and the left-hand side inherits the updated list. Some Java examples follow:
    
        Interfacesopt$$InterfaceType ::= %Empty      -- create an empty list of InterfaceType
                                       | Interfaces  -- inherit the Interfaces list
        
        Interfaces$$InterfaceType ::= 'implements' InterfaceTypeList  -- inherit the InterfaceTypeList     

        InterfaceTypeList$$InterfaceType ::= InterfaceType                       -- create a singleton list of InterfaceType
                                           | InterfaceTypeList ',' InterfaceType -- Add InterfaceType element to InterfaceTypeList to obtain new list
        
        ExtendsInterfaces$$InterfaceType ::= 'extends' InterfaceTypeList -- inherit the InterfaceTypeList

    The user also has the option of merging the information from different rules into a single class and
    requesting that that class be used for all the rules involved. This is done by simply assigning the
    same class name to each of the rules in question. This approach is illustrated in the following Java
    example:
        
            Statement$IfStatement ::= IF$ ($ expr )$ Statement$trueStatement 
            Statement$ifStatement ::= IF$ ($ expr )$ Statement$trueStatement ELSE$ Statement$falseStatement

     or
     
            Statement$IfStatement ::= IF$ ($ expr )$ Statement$trueStatement 
                                    | IF$ ($ expr )$ Statement$trueStatement ELSE$ Statement$falseStatement
                                    
    In this example, LPG will generate a single class named IfStatement to be used for both rules. The
    IfStatement class will contain the fields: expr, trueStatement and falseStatement.
    
    In general, when multiple rules share the same class, if the name associated with a symbol appear on
    the the right-hand side of more than one rule then only a single field is generated with that name and
    it is shared by all the relevant symbols. If a name does not appear in all the rules then it is an
    optional name to which a null is assigned when we reduce by a rule that does not contain it. In our
    example above, since the name of the two fields expr and trueStatement appear in both rules, it is
    always assigned a real value in any instance of IfStatement (regardless of which rule triggered its
    creation). On the other hand, the falseStatement field only appears in one rule. Thus, when the rule that
    does not contain it is reduced it is assigned to null. There is no restriction is the set of symbols that
    can share a name. LPG will determine a suitable type for the merge field that is compatible with all of
    them.
    
    When in auto-generated AST mode the user can use the action blocks associated with a rule to add extra
    class member declarations (field, method, block declarations) to an AST node. He may also specify his
    own initialize() method which will be invoked by the constructor. In the CnC example, we had no need
    to add new attributes to an AST node. However, in the case of a step_execution (see example below), we
    added an initialize() method to reassign any instance list that was assigned to null by default to an
    empty list. Note also that all six rules associated with the nonterminal step_execution will share the
    same AST class: StepExecution. 
    
            step_execution$StepExecution ::= instance_list$inputList "->" step_instance
                                           | instance_list$inputList "->" step_instance "->" instance_list$outputList
                                           | step_instance "<-" instance_list$inputList
                                           | instance_list$outputList "<-" step_instance
                                           | instance_list$outputList "<-" step_instance "<-" instance_list$inputList
                                           | step_instance "->" instance_list$outputList
            /.
                //
                // If any list variable is initialized to null, we reinitialize it to the empty list.
                // Note that we don't bother computing the exact location for such a list as its only
                // purpose is to avoid a null test.
                //
                void initialize() {
                    if (_inputList == null)
                        _inputList = new instanceList(leftIToken, rightIToken, true);
                    if (_outputList == null)
                        _outputList = new instanceList(leftIToken, rightIToken, true);
                }
            ./


    In the CNC parser, we generate a preorder visitor that traverses the AST in top-down-left-to-right
    order. A concrete visitor that will visit every kind of node should implement the Visitor interface.
    (Thus, the Visitor class is a good place to look for all the nodes that are generated for a given
    grammar.) On the other hand, a concrete visitor that will only visit a subset of the nodes can extend
    the abstrtact class: AbstractVisitor, (which requires only the implementation of the method
    unimplementedVisitor()) and selectively override the visitor methods for the relevant nodes.
    
    When traversing the AST with a preorder visitor, the user can visit a node on the way down via
    the methods preVisit() (which is a generic method for all AST nodes) and visit() (which is specific
    to each kind of Ast node) and on the way back via the corresponding methods endVisit() and postVisit().
    
    In the CnC parser, we implemented a concrete visitor CncHjGenerator that extends AbstractVisitor
    to generate HJ classes for the StepPrescription and StepExecution AST nodes.  