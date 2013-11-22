%options variables=nt,automatic_ast=toplevel,visitor=preorder
%options ast-directory=./Ast
%options fp=CncParser
%options package=CnCParser
%options template=dtParserTemplateF.gi
%options import_terminals=cncLexer.gi

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

%Terminals

    SEMICOLON         ::= ";"
    RIGHT_ARROW       ::= "->"
    LEFT_ARROW        ::= "<-"
    COLON_COLON       ::= "::"
    COMMA             ::= ","
    LESS_THAN         ::= "<"
    GREATER_THAN      ::= ">"
    COLON             ::= ":"
    LEFT_PARENTHESIS  ::= "("
    RIGHT_PARENTHESIS ::= ")"
    LEFT_BRACKET      ::= "["
    RIGHT_BRACKET     ::= "]"
    LEFT_BRACE        ::= "{"
    RIGHT_BRACE       ::= "}"
    EQUAL             ::= "="
    AMPERSAND         ::= '&'
    STAR              ::= '*'
    DOT               ::= '.'
    DOT_DOT           ::= ".."
    PLUS        	  ::= '+'
    MINUS       	  ::= '-'
    SLASH      	 	  ::= '/'
    SHARP      	 	  ::= '#'
    ATSIGN			  ::= "@"
%End

%EOL
    ;
%End

%Start
    graph
%End

%Rules

    graph ::= statements

    statements$$statement ::= statement
                            | statements statement

    statement ::= terminated_declaration
                | terminated_relation

    terminated_declaration ::=  declaration ';'

    declaration ::= item_declaration
                  | tag_declaration
                  | step_declaration

    terminated_relation ::= relation ';'

    relation ::= step_execution
               | step_prescription

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

    step_prescription$StepPrescription ::= tag_instance :: step_instance_list
    

	-------------- Rules for describing lists of instances, which can be items or tags
    instance_list$$instance ::= instance
                              | instance_list ',' instance
	instance ::= item_instance
               | tag_instance	
	
	-------------- Rules describing items
	item_declaration ::= item_instance attribute_list_opt
	item_instance$item_instance ::= '[' item_definition tag_description_opt ']' 
    item_definition$item_definition ::= item_type T_NAME$name
                                       | T_NAME$name
	item_type ::= T_NAME
				| T_UNSIGNED  T_NAME
				| T_STRUCT  T_NAME
	item_type$PointerType   ::= item_type '*'
	
	-------------- Rules describing tags
	tag_declaration ::= tag_instance attribute_list_opt
    tag_instance$tag_instance ::= '<' tag_definition tag_description_opt '>'
	tag_definition$tag_definition ::= tag_type T_NAME$name
                                       | T_NAME$name
	tag_description_opt$$tag_component ::= tag_description
	                                     | %Empty
	tag_type$tag_type ::= t_type 
						| t_type '[' T_NUMBER$dim ']' 
						| tag_type '.' t_type
    
    -------------- Rules describing tag functions for items and tags
    tag_description$$tag_component ::= ':' tag_component_list
    tag_component_list$$tag_component ::= tag_component
                                        | tag_component_list ',' tag_component
	tag_component$tag_component ::= t_type aritm_expr$expression
									| aritm_expr$expression
									| '{' aritm_expr$start_range ".." aritm_expr$stop_range '}'
	aritm_expr$aritm_expr ::= aritm_expr$first '+'$operand aritm_term$second
							| aritm_expr$first '-'$operand aritm_term$second
							| aritm_term$second

	aritm_term$aritm_term ::= aritm_term$first '*'$operand aritm_factor$second
	 						 | aritm_term$first '/'$operand aritm_factor$second
							 | aritm_factor$second
	/.
		@Override
    	public String toString(){
    		if(_first != null)
    			return _first.toString() + _operand.toString() + _second.toString();
    		else
    			return _second.toString();
    	}
    ./
    
	aritm_factor$aritm_factor ::=  T_NAME$name
							| T_NAME$name '[' aritm_expr$index ']'
							| T_NUMBER$val
	/.
        //
        // Keep another variable, for possible name change of name
        //
        String _new_name;
        public void setNewName(String change) {
            _new_name = change;
        }
        
        @Override
	    public String toString(){
	    	StringBuilder toret =  new StringBuilder();
	    	if(_new_name != null){
	    		toret.append(_new_name);
	    		if(_index != null) toret.append("["+_index.toString()+"]");
	    	}
	    	else if(_name != null){
	    		toret.append(_name);
	    		if(_index != null) toret.append("["+_index.toString()+"]");
	    	}
	    	else if(_val != null){
	    		toret.append(_val);
	    	}
	    	//else throw an error? (grammar does not accept empty)
	    	
	    	return toret.toString();
	    }
    ./
    
    -------------- Rules describing steps
    step_declaration ::= step_instance attribute_list_opt
    step_instance$step_instance ::= '('$step_type T_NAME$name step_description_opt ')' |
    								'{'$step_type T_NAME$name step_description_opt '}'
	step_description_opt$$step_component ::= step_description
	                                     | %Empty
	

	-------------- Rules describing tag functions for steps (list of "name" used in StepExecution rules)
    step_description$$step_component ::= ':' step_component_list
    step_component_list$$step_component ::= step_component
                                        | step_component_list ',' step_component
	step_component$step_component ::= t_type T_NAME$name
									 | T_NAME$name
									 | '{' T_NAME$start_range ".." T_NAME$end_range '}'
    t_type ::= T_NAME
    
    -------------- Rules describing device affinities (list of "device=number" used in StepPrescription rules)
 	step_instance_list$$step_instance_aff ::= step_instance_aff
                                        | step_instance_list ',' step_instance_aff
	step_instance_aff$step_instance_aff ::= '('$step_type T_NAME$name step_description_aff_opt ')' |
    									'{'$step_type T_NAME$name step_description_aff_opt '}'
 	step_description_aff_opt$$step_affinity ::= step_description_aff
	                                     | %Empty
 	step_description_aff$$step_affinity ::= '@' step_affinity_list
    step_affinity_list$$step_affinity ::= step_affinity
    									| step_affinity_list ',' step_affinity
    step_affinity$step_affinity ::= T_NAME$name '=' T_NUMBER$val
    
    
    -------------- Rule defining the environment 
    step_instance$step_instance_environment ::= T_ENV 
    
-------------------------------------------------------------------------------------------
   
	-------------- Rules for attributes, currently unused
	attribute_list_opt$$attribute ::= %Empty
    --                                | attribute_list
    attribute_list$$attribute ::= attribute
                                | attribute_list ',' attribute
    attribute$VariableAttribute ::= T_NAME$name '=' T_NAME$value 
    attribute$IntegerAttribute  ::= T_NAME$name '=' T_NUMBER$value
    attribute$StringAttribute   ::= T_NAME$name '=' T_QUOTEDVAL$value
	 
	 
	-- Rule trials - obsolete
	-- step_instance$cpu_step ::= '(' T_NAME$name step_description_opt ')'
    -- step_instance$gpu_step ::= '{' T_NAME$name step_description_opt '}'
	-- t_type$ReferenceType ::= t_type '&'
    -- t_type$PointerType   ::= t_type '*' 
	-- item_type$ReferenceType ::= item_type '&' 

%End
