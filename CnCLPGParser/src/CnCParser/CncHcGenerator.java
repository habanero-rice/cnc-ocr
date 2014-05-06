/**
 * This file is part of the CNC-C implementation and
 * distributed under the Modified BSD License. 
 * See LICENSE for details.
 */

package CnCParser;

import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import CnCParser.Ast.AbstractVisitor;
import CnCParser.Ast.Iaritm_expr;
import CnCParser.Ast.Iinstance;
import CnCParser.Ast.Iitem_type;
import CnCParser.Ast.PointerType;
import CnCParser.Ast.StepExecution;
import CnCParser.Ast.StepPrescription;
import CnCParser.Ast.aritm_factor;
import CnCParser.Ast.instanceList;
import CnCParser.Ast.item_definition;
import CnCParser.Ast.item_instance;
import CnCParser.Ast.statementList;
import CnCParser.Ast.step_component;
import CnCParser.Ast.step_componentList;
import CnCParser.Ast.step_affinity;
import CnCParser.Ast.step_affinityList;
import CnCParser.Ast.step_instance;
import CnCParser.Ast.step_instance_aff;
import CnCParser.Ast.step_instance_affList;
import CnCParser.Ast.tag_component;
import CnCParser.Ast.tag_componentList;
import CnCParser.Ast.tag_definition;
import CnCParser.Ast.tag_instance;
import CnCParser.Ast.tag_type;

public class CncHcGenerator extends AbstractVisitor 
{
	Map<String, ArrayList<String>> tag_steps = new LinkedHashMap<String, ArrayList<String>>(); // List of steps prescribed by each tag
	
	Map<String, Iitem_type> all_items = new LinkedHashMap<String, Iitem_type>(); //all ItemCollections names and their types
	Map<String, tag_type_local> all_tags = new LinkedHashMap<String, tag_type_local>(); // all TagCollections names and their types
	Map<String, step_info_local> steps_identifiers = new LinkedHashMap<String, step_info_local>();//all CPU StepCollections and their associated information (inputs, outputs, affinites...)
	List<String> steps_name_list = new ArrayList<String>();
	Map<String, String> step_no_gets = new LinkedHashMap<String, String>();//code computing how many dependences each step waits on.
	step_info_local environment = null;
	StringBuilder envOutFunc = new StringBuilder();
	
	String GET = "CNC_GET";
	String default_err = "Unable to generate code without this information";
	String fullAutoUserDefined = "_userDefined";
	String mainUsesGraphOutputs = "useGraphOutputs";
	private static final String cudaTail = "_kernelCaller";

	String filename; // the name of the file containing the CnC program we are compiling
	String dir ="";
	boolean affinity_enabled = false; 
	boolean all_tag_functions_present = true;
	
	boolean fullauto;
	StringBuilder user_written_alloc_methods_buffer;
	StringBuilder user_written_step_methods_buffer;
	StringBuilder user_written_main_uses_data_buffer;

	public CncHcGenerator(String filename_, String dir_, boolean fullauto_){
		super();
		File f = new File(filename_);
		filename = f.getName();
		if(dir_ != null){
			File d = new File(dir_);
			if(d.exists() && d.isDirectory())
				dir = dir_;
			else
				System.out.println("Warning: directory "+dir_+" does not exist. Generating files in current directory.");
		}
		fullauto = fullauto_;
		if(fullauto){
			user_written_alloc_methods_buffer = new StringBuilder();
			user_written_step_methods_buffer = new StringBuilder();
			user_written_main_uses_data_buffer = new StringBuilder();
		}
		environment = new step_info_local("env");
		//environment.init = true;
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Helper classes definitions
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	private class tag_type_local{
		String tagtype;
		Integer dim;
		tag_type_local(String t, Integer d){ tagtype = t; dim = d; }
	}

	private class step_info_local{
		String step_name;
		StringBuilder prototype_withtypes, prototype_withouttypes;
		step_componentList identifiers; //keep the names of the first encounter; second encounter - match/change the names to the first
		String prescribing_tag;
		Map<String, InputCollectionLocal> inputs;
		Map<String, OutputCollectionLocal> outputs;
		Map<String, TagCollectionLocal> tags;
		step_affinityList affinityList = null;
		boolean init = false;
		public step_info_local(String step_name){
			this.step_name = step_name;
			inputs = new LinkedHashMap<String, InputCollectionLocal>();
			outputs = new LinkedHashMap<String, OutputCollectionLocal>();
			tags = new LinkedHashMap<String, TagCollectionLocal>();
			prototype_withtypes = new StringBuilder(); 
			prototype_withouttypes = new StringBuilder();
		}
	}

	private class CollectionLocal{
		String name;
		LinkedList<LinkedList<TagFunctionLocal>> tag_functions;
		public CollectionLocal(String name_){
			name = name_;
			tag_functions = new LinkedList<LinkedList<TagFunctionLocal>>();
		}
	}

	private class InputCollectionLocal extends CollectionLocal{
		public InputCollectionLocal(String name){ super(name); }
	}

	private class OutputCollectionLocal extends CollectionLocal{
		public OutputCollectionLocal(String name){ super(name); }
	}

	private class TagCollectionLocal extends CollectionLocal{
		public TagCollectionLocal(String name){ super(name); }
	}

	private class TagFunctionLocal{
		private String type;
		public TagFunctionLocal(String t) { if (null == t) t = "int"; else setType(t); }
		public void setType(String type) {
			this.type = type;
		}
	}

	private class RangeLocal extends TagFunctionLocal{
		public AritmExpressionLocal start, stop;
		public RangeLocal(String t) { super (t); }
		public RangeLocal(String t, Iaritm_expr expr1, Iaritm_expr expr2) { 
			super (t); 
			start = new AritmExpressionLocal(t, expr1);
			stop = new AritmExpressionLocal(t, expr2);
		}
		public String toString(){ return "("+start.toString()+", "+stop.toString()+")"; }
	}

	private class AritmExpressionLocal extends TagFunctionLocal{
		Iaritm_expr expression;
		public AritmExpressionLocal(String t) { super (t); }
		public AritmExpressionLocal(String t, Iaritm_expr expr1) {
			super(t);
			expression = expr1;
		}
		public String toString(){ return expression.toString(); }
	}

	private class TagFunctionVisitor extends AbstractVisitor {
		LinkedList<TagFunctionLocal> tag_functionList;
		step_componentList scList, scList_old;
		boolean different;
		public TagFunctionVisitor(step_componentList scList, step_componentList scList_old){
			this.scList = scList; this.scList_old = scList_old;
			different = false;
			if(scList != null)
				for (int i = 0; i < scList.size(); i++){
					step_component tc = (step_component) scList.getstep_componentAt(i);
					step_component tc_o = (step_component) scList_old.getstep_componentAt(i);
					if(!tc.toString().equals(tc_o.toString())){
						different = true; break;
					}
				}
			tag_functionList = new LinkedList<TagFunctionLocal>();
		}

		public boolean visit(tag_componentList tcList){
			for (int i = 0; i < tcList.size(); i++){
				tag_component tc = (tag_component) tcList.gettag_componentAt(i);
				TagFunctionLocal tfl;
				String tagtype = (tc.gett_type() == null)? "int" : tc.gett_type().toString();
				if(tc.getexpression() != null)
					tfl = new AritmExpressionLocal(tagtype, tc.getexpression());
				else //range
					tfl = new RangeLocal(tagtype, tc.getstart_range(), tc.getstop_range());
				tag_functionList.add(tfl);
			}
			return different;
		}

		public boolean visit(aritm_factor a_f){
			if (a_f.getname() != null && scList != null){
				String name = a_f.getname().toString();
				for (int i = 0; i < scList.size(); i++){
					step_component tc = (step_component) scList.getstep_componentAt(i);
					step_component tc_o = (step_component) scList_old.getstep_componentAt(i);
					if(tc.getname() != null && tc.getname().toString().equals(name))
						a_f.setNewName(tc_o.getname().toString()); 
					if(tc.getstart_range() != null && tc.getstart_range().toString().equals(name))
						a_f.setNewName(tc_o.getstart_range().toString());
					if(tc.getend_range() != null && tc.getend_range().toString().equals(name))
						a_f.setNewName(tc_o.getend_range().toString());
				}
			}
			return false;
		}

		public void unimplementedVisitor(String s) {}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Visiting methods
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 * Visit StepPrescription rule and add all the steps to the list of steps prescribed by this tag. Also store affinities.
	 */
	public boolean visit(StepPrescription n)
	{
		tag_instance tag = n.gettag_instance();
		step_instance_affList step_instance_list = n.getstep_instance_list();

		tag_componentList tag_description_opt = tag.gettag_description_opt();
		if(tag_description_opt != null && tag_description_opt.size() > 0) 
			System.err.println("Step Prescription warning: tags should not have tag functions when precribing a step. Tag function will be ignored.\n");

		String tag_name = tag.gettag_definition().getname().toString();
		ArrayList<String> step_list = tag_steps.get(tag_name);
		if (step_list == null)
			step_list = new ArrayList<String>();

		Map<String, step_info_local> steps_identifiers_local;
		for (int i = 0; i < step_instance_list.size(); i++){
			step_instance_aff si = (step_instance_aff) step_instance_list.getstep_instance_affAt(i);
			String si_name = si.getname().toString();
			step_list.add(si_name);
			steps_identifiers_local = steps_identifiers;
			step_info_local si_local = steps_identifiers_local.get(si_name);
			if(si_local == null){
				// TODO - this is my ad-hoc way of handling env (there should be a better way)
				if (si.getname().toString().equals("env")) {
					si_local = environment;
				}
				else {
					si_local = new step_info_local(si_name);
					steps_identifiers_local.put(si_name, si_local);
				}
				step_affinityList sAffList = si.getstep_description_aff_opt();
				if(sAffList.size() > 0){
					si_local.affinityList = sAffList;
					affinity_enabled = true;
				}
			}
		}
		tag_steps.put(tag_name, step_list); // update list of step names
		return false; // done with this node ... don't bother to traverse its children
	}

	/**
	 * Visit the tag_definition ensure format is type [dim] tag_name. Save tag information.
	 */
	public boolean visit(tag_definition n) {
		tag_type type = (tag_type) n.gettag_type();
		String tagtype = (type != null) ? type.gett_type() + "" : "int";

		Integer dim;
		if(type.getdim() != null)
			dim = Integer.parseInt(type.getdim().toString());
		else {
			System.err.println(" Tag Definition error: tags should have dimension in the form [dim] following the type. Unable to generate code without this information\n");
			dim = -1;
			System.exit(1);
		}

		tag_type_local combined_type = new tag_type_local(tagtype, dim);
		this.all_tags.put(n.getname().toString(), combined_type);

		return false;
	}

	/**
	 * Visit the item_definition and check the type. Save item information.
	 */
	public boolean visit(item_definition n) {
		Iitem_type type = n.getitem_type();
		if(type == null){
			System.err.println(" Item Definition error: items should have a type. " +
					default_err + "\n");
			System.exit(1);
		}
		else
			all_items.put(n.getname().toString(), type);
		return false;
	}

	/**
	 * Visit StepExecution rule and gather information about steps, items read and written and tag written
	 */
	public boolean visit(StepExecution n){
		step_info_local si_local;
		instanceList inputList = n.getinputList(), outputList = n.getoutputList();
		step_componentList scList=null, scList_old=null;
		if (n.getstep_instance() instanceof step_instance) {
			step_instance si = (step_instance) n.getstep_instance();
			String si_name = si.getname().toString();
			
			Map<String, step_info_local> steps_identifiers_local;
			steps_identifiers_local = steps_identifiers;

			scList = si.getstep_description_opt();
			scList_old = scList;
			if(scList.size() == 0){
				System.err.println(" Step Execution warning: Steps should have a list of names (preferably with types as well) " +
						"representing the format of the tag prescribing them.\n" +
						default_err + 
						"\nYou, the user, will have to write by hand what I cannot generate (e.g. the get functions in Common.c).\n"+
						"Please provide accurate tag functions to avoid this."+
						"\n");
				all_tag_functions_present = false;
			}

			// TODO - this is my ad-hoc way of handling env (there should be a better way)
			if (si.getname().toString().equals("env")) {
				si_local = environment;
			}
			else {
				si_local = steps_identifiers_local.get(si_name);
			}
			if(si_local == null || si_local.init == false){
				if(si_local == null){
					si_local = new step_info_local(si_name);
					steps_identifiers_local.put(si_name, si_local);
				}
				si_local.identifiers = scList;
				si_local.init = true;
			}
			else{ //if previous scList exists, store old one in scList_old
				//make sure they are the same, else print error
				scList_old = si_local.identifiers;
				if(scList_old.size() != scList.size()) { 
					System.err.println(" Step Execution error: Found step ("+si_name+") with tag functions of different sizes. Cannot generate code with this contradiction. Translator will exit\n ");
					System.exit(1);
				}
			}
		}
		else //NOTE: Currently we allow env rules to not have tag functions.
			si_local = environment;

		// get all the input collections
		for (int i = 0; i < inputList.size(); i++){				
			Iinstance instance = inputList.getinstanceAt(i);
			if (instance instanceof item_instance){
				String instanceName = ((item_instance) instance).getitem_definition().getname().toString();

				InputCollectionLocal input = si_local.inputs.get(instanceName);
				if(input == null){
					input = new InputCollectionLocal(instanceName);
					si_local.inputs.put(instanceName, input);
				}			
				tag_componentList tc_List = ((item_instance) instance).gettag_description_opt();
				if(tc_List.size() == 0 && si_local != environment){
					System.err.println(" Step Execution warning: Inputs should have a list of tag functions representing the format of the tag prescribing them. " +
							default_err + "\n");
					all_tag_functions_present = false;
				}
				else{
					TagFunctionVisitor tf_v = new TagFunctionVisitor(scList, scList_old);
					tc_List.accept(tf_v);
					input.tag_functions.add(tf_v.tag_functionList);
				}
			}
			else if (instance instanceof tag_instance){
				System.err.println(" Step Execution warning: Tag collections cannot be used as inputs in CnC. Translator will ignore these.\n");
			}
		}

		// get all the output collections
		for (int i = 0; i < outputList.size(); i++){
			Iinstance instance = outputList.getinstanceAt(i);
			if (instance instanceof item_instance){
				String instanceName = ((item_instance) instance).getitem_definition().getname().toString();

				OutputCollectionLocal output = si_local.outputs.get(instanceName);
				if(output == null){
					output = new OutputCollectionLocal(instanceName);
					si_local.outputs.put(instanceName, output);
				}			
				tag_componentList tc_List = ((item_instance) instance).gettag_description_opt();
				if(tc_List.size() == 0 && si_local != environment){
					System.err.println(" Step Execution warning: Outputs should have a list of tag functions representing the format of the tag prescribing them. " +
							default_err + "\n");
					all_tag_functions_present = false;
				}
				else{
					TagFunctionVisitor tf_v = new TagFunctionVisitor(scList, scList_old);
					tc_List.accept(tf_v);
					output.tag_functions.add(tf_v.tag_functionList);
				}

			} else if (instance instanceof tag_instance){
				String instanceName = ((tag_instance) instance).gettag_definition().getname().toString();

				TagCollectionLocal tag = si_local.tags.get(instanceName);
				if(tag == null){
					tag = new TagCollectionLocal(instanceName);
					si_local.tags.put(instanceName, tag);
				}			
				tag_componentList tc_List = ((tag_instance) instance).gettag_description_opt();
				if(tc_List.size() == 0 && si_local != environment){
					System.err.println(" Step Execution warning: Tags should have a list of tag functions representing the format of the tag prescribing them. " +
							default_err + "\n");
					all_tag_functions_present = false;
				}
				else{
					TagFunctionVisitor tf_v = new TagFunctionVisitor(scList, scList_old);
					tc_List.accept(tf_v);
					tag.tag_functions.add(tf_v.tag_functionList);
				}
			}
		}
		return false; // done with this node ... don bother to traverse its children
	}

	//
	// At the very end, we have all the information to generate the HC source code
	//
	public void endVisit(statementList n)
	{
		//Generate step stubs, common.c and common.h
		generateSteps();
		
		//Generate the Context structure: context.h
		generateContextH();

		//Generate the Context init function: context.c
		generateContextC();

		//Generate the step constants and declarations: dispatch.h
		generateDispatchH();
		
		//Generate the prescribe function: dispatch.c (must follow generation of common.c)
		generateDispatchC();

		//Generate a stub for main
		generateMainStubHC();

		//Generate makefile for building all the generated files with the runtime.
		generateMakefile();
	}

	/**
	 * Generate the Context structure: Context.h
	 */
	private void generateContextH() {

		try {
			PrintStream stream_contexth = new PrintStream(new File(dir + "Context.h"));
			printHeader(stream_contexth);
			stream_contexth.println("#ifndef _CONTEXT");
			stream_contexth.println("#define _CONTEXT");
			stream_contexth.println();
			stream_contexth.println("#include \"Dispatch.h\"");
			stream_contexth.println();
			
			// Step function types
			stream_contexth.println("typedef void (*StepDependenceFunction)(char *, struct Context *);");	
			stream_contexth.println();	
			stream_contexth.println("typedef struct {");	
			stream_contexth.println("\tStepDependenceFunction depf;");
			stream_contexth.println("\tcncHandle_t taskTemplate;");
			stream_contexth.println("} StepFunctionInfo;");
			stream_contexth.println();	

			//Generate "struct Context"
			stream_contexth.println("typedef struct Context {");	
			for (String item_collection_name : all_items.keySet()) {
				stream_contexth.println("\tItemCollectionEntry ** "+item_collection_name +";");
			}
			for (String step_name : steps_name_list) {
				stream_contexth.printf("\tStepFunctionInfo %s;%n", step_name);
			}
			stream_contexth.println("\tocrGuid_t cncEnvOutTag;");
			stream_contexth.println("} Context;");
			stream_contexth.println();
			
			stream_contexth.println("");
			stream_contexth.println();

			// Generate item collection entry types
			for (Map.Entry<String, Iitem_type> item_coll : all_items.entrySet()) {
				String collName = item_coll.getKey();
				String collType = prettyType(item_coll.getValue().toString().trim());
				stream_contexth.printf("typedef struct { %sitem; cncHandle_t handle; } %sItem;%n", collType, collName);
			}
			stream_contexth.println();

			// Generate item instance creation function prototypes
			writeItemCreators(stream_contexth, true);
			stream_contexth.println();

			//Generate "initGraph" and "deleteGraph" function prototypes
			stream_contexth.println("Context *initGraph();");
			stream_contexth.println("void deleteGraph(Context *CnCGraph);");
			stream_contexth.println();
			stream_contexth.println("void setEnvOutTag(char *outTag, Context *context);");
			stream_contexth.println();
			stream_contexth.println("#endif /*_CONTEXT*/");
			stream_contexth.println();
		}
		catch (IOException ie)
		{
			System.err.println(ie.getMessage());
			ie.printStackTrace();
		}
	}

	private void writeItemCreators(PrintStream out, boolean prototypesOnly) {
		for (Map.Entry<String, Iitem_type> item_coll : all_items.entrySet()) {
			String collName = item_coll.getKey();
			String collType = item_coll.getValue().toString().trim() + "*";
			String countArg = ", size_t count";
			String timesCount = "*count";
			// Must use pointer types when allocating data blocks
			if (!(item_coll.getValue() instanceof PointerType)) {
				collType += "*";
				countArg = timesCount = "";
			}
			collType = prettyType(collType);
			out.printf("cncHandle_t cncCreateItem_%s(%sitem%s)", collName, collType, countArg);
			// End function prototype or write function body
			if (prototypesOnly) {
				out.println(";");
			}
			else {
				out.println(" {");
				out.println("\tcncHandle_t handle;");
				out.print("\tCREATE_ITEM_INSTANCE(&handle, (void**)item, ");
				out.printf("sizeof(**item)%s);%n", timesCount);
				out.println("\treturn handle;");
				out.println("}");
				out.println();
			}
		}
	}

	/**
	 * Generate method to initialize and delete the context: context.c
	 */
	private void generateContextC() {
		try {
			PrintStream stream_contextc = new PrintStream(new File(dir + "Context.c"));
			printHeader(stream_contextc);
			// TODO - Should be using OCR macros instead of cnc_mm.h
			stream_contextc.println("#include \"cnc_mm.h\"");
			stream_contextc.println("#include \"Context.h\"");
			stream_contextc.println("#include <string.h>");
			stream_contextc.println();
			
			//Generate "initGraph" method
			stream_contextc.println("Context *initGraph()");
			stream_contextc.println("{"); 
			stream_contextc.println("\tint i;");
			stream_contextc.println("\tContext *CnCGraph = (Context*) cnc_malloc (1 * sizeof(Context));\n");
			stream_contextc.println();
			StringBuilder sb = new StringBuilder();
			for (String item_collection_name : all_items.keySet()) {
				stream_contextc.println("\tCnCGraph->"+item_collection_name +" = (ItemCollectionEntry**) cnc_malloc (TABLE_SIZE * sizeof(ItemCollectionEntry*));");
				sb.append("CnCGraph->"+item_collection_name + "[i] = ");
			}
			stream_contextc.println();
			stream_contextc.println("\tfor(i=0; i<TABLE_SIZE; i++){");
			stream_contextc.println("\t\t" + sb.toString() + " NULL;");
			stream_contextc.println("\t}");
			stream_contextc.println();
			for (String step_name : steps_name_list) {
				stream_contextc.printf("\tCnCGraph->%s.depf = %s_dependencies;%n", step_name, step_name);
				stream_contextc.printf("\tocrEdtTemplateCreate(&CnCGraph->%s.taskTemplate, %s_gets, 2, %s);%n",
				                       step_name, step_name, "EDT_PARAM_UNK");
			}
			stream_contextc.println();
			stream_contextc.println("\tocrEventCreate(&(CnCGraph->cncEnvOutTag), OCR_EVENT_ONCE_T, true);");
			stream_contextc.println();
			stream_contextc.println("\treturn CnCGraph;");
			stream_contextc.println("}");
			stream_contextc.println();
			
			// Generate item instance creation functions
			writeItemCreators(stream_contextc, false);

			//Generate "deleteGraph" method
			stream_contextc.println("void deleteGraph(Context *CnCGraph)");
			stream_contextc.println("{"); 
			for (String item_collection_name : all_items.keySet()) {
				stream_contextc.println("\tcnc_free(CnCGraph->"+item_collection_name +");");
			}
			stream_contextc.println();
			stream_contextc.println("\tcnc_free(CnCGraph);");
			stream_contextc.println("}");
			stream_contextc.println();
			stream_contextc.println("void setEnvOutTag(char *tag, Context *context) {");
			stream_contextc.println("\tchar *tagPtr;");
			stream_contextc.println("\tocrGuid_t tagGuid;");
			stream_contextc.println("\tCREATE_ITEM_INSTANCE(&tagGuid, (void**)&tagPtr, strlen(tag));");
			stream_contextc.println("\tstrcpy(tagPtr, tag);");
			stream_contextc.println("\tocrEventSatisfy(context->cncEnvOutTag, tagGuid);");
			stream_contextc.println("}");
		}
		catch (IOException ie)
		{
			System.err.println(ie.getMessage());
			ie.printStackTrace();
		}
	}

	/**
	 * Generate the step constants and declarations: dispatch.h
	 */
	private void generateDispatchH() {	
		try {
			PrintStream stream_dispatchh= new PrintStream(new File(dir + "Dispatch.h"));
			printHeader(stream_dispatchh);
			stream_dispatchh.println("#ifndef _CNC_STEPS_H");
			stream_dispatchh.println("#define _CNC_STEPS_H");
			stream_dispatchh.println();
			stream_dispatchh.println("#include \"DataDriven.h\"");
			stream_dispatchh.println();

			stream_dispatchh.println("struct Context;");	
			stream_dispatchh.println();	

			//Generate "xxx_gets" and "xxx_dependencies" function prototypes
			for (String step_name : steps_name_list) {
				stream_dispatchh.println("ocrGuid_t " + step_name + "_gets(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]);");
				stream_dispatchh.println("void " + step_name + "_dependencies(char *tag, struct Context *context);");
			}
			stream_dispatchh.println();
			
			if(fullauto){
				stream_dispatchh.println(user_written_alloc_methods_buffer.toString());
				stream_dispatchh.println();
				stream_dispatchh.println(user_written_step_methods_buffer.toString());
				if(user_written_main_uses_data_buffer != null)
					stream_dispatchh.println(user_written_main_uses_data_buffer.toString());
				stream_dispatchh.println();
			}
			
			stream_dispatchh.println("#endif /*_CNC_STEPS_H*/");
			stream_dispatchh.println();
			stream_dispatchh.close();
		}
		catch (IOException ie)
		{
			System.err.println(ie.getMessage());
			ie.printStackTrace();
		}
	}

	/**
	 * Generate the dispatch and prescribe functions: Dispatch.c
	 */
	private void generateDispatchC() {
		try {
			PrintStream stream_dispatchhc = new PrintStream(new File(dir + "Dispatch.c"));
			printHeader(stream_dispatchhc);
			stream_dispatchhc.println("#include \"Dispatch.h\"");
			stream_dispatchhc.println("#include \"Context.h\"");
			stream_dispatchhc.println("#include <string.h>");
			stream_dispatchhc.println("#include <assert.h>");
			stream_dispatchhc.println("#include <stdio.h>");
			stream_dispatchhc.println();
			
			// Application entry point
			stream_dispatchhc.println("ocrGuid_t cncEnvInEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {");
			stream_dispatchhc.println("\t// Unpack argc and argv (passed thru from mainEdt)");
			stream_dispatchhc.println("\tu64 *packedArgs = depv[0].ptr;");
			stream_dispatchhc.println("\tint i, argc = packedArgs[0];");
			stream_dispatchhc.println("\tchar *argBytes = (char*)packedArgs;");
			stream_dispatchhc.println("\tchar **argv = MALLOC(sizeof(char*)*argc);");
			stream_dispatchhc.println("\tfor (i=0; i<argc; i++) argv[i] = argBytes+packedArgs[i+1];");
			stream_dispatchhc.println("\t// Run user's cncEnvIn function");
			stream_dispatchhc.println("\tcncEnvIn(argc, argv, (Context*)paramv[0]);");
			stream_dispatchhc.println("\tFREE(argv);");
			stream_dispatchhc.println("\treturn NULL_GUID;");
			stream_dispatchhc.println("}");
			stream_dispatchhc.println();
			stream_dispatchhc.println("ocrGuid_t cncEnvOutEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {");
			stream_dispatchhc.println("\t// Pull the tag");
			stream_dispatchhc.println("\tchar *stepTag = depv[0].ptr;");
			stream_dispatchhc.println("\t// Schedule user's ocrEnvOut function");
			stream_dispatchhc.println("\tcncEnvOut_dependencies(stepTag, (Context*)paramv[0]);");
			stream_dispatchhc.println("\treturn NULL_GUID;");
			stream_dispatchhc.println("}");
			stream_dispatchhc.println();
			stream_dispatchhc.println("ocrGuid_t cncEnvFreeEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {");
			stream_dispatchhc.println("\t// Execution is finished at this point");
			stream_dispatchhc.println("\tdeleteGraph((Context*)paramv[0]);");
			stream_dispatchhc.println("\tocrShutdown();");
			stream_dispatchhc.println("\treturn NULL_GUID;");
			stream_dispatchhc.println("}");
			stream_dispatchhc.println();
			stream_dispatchhc.println("ocrGuid_t mainEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {");
			stream_dispatchhc.println("\tContext *context = initGraph();");
			stream_dispatchhc.println("\t// Create ocrEnvInEdt as a finish EDT");
			stream_dispatchhc.println("\tocrGuid_t inEdtGuid, graphDoneGuid, templGuid;");
			stream_dispatchhc.println("\tocrEdtTemplateCreate(&templGuid, cncEnvInEdt, 1, 1);");
			stream_dispatchhc.println("\tocrEdtCreate(&inEdtGuid, templGuid,");
			stream_dispatchhc.println("\t\t/*paramc=*/EDT_PARAM_DEF, /*paramv=*/(u64*)&context,");
			stream_dispatchhc.println("\t\t/*depc=*/EDT_PARAM_DEF, /*depv=*/NULL,");
			stream_dispatchhc.println("\t\t/*properties=*/EDT_PROP_FINISH,");
			stream_dispatchhc.println("\t\t/*affinity=*/NULL_GUID, /*outEvent=*/&graphDoneGuid);");
			stream_dispatchhc.println("\tocrEdtTemplateDestroy(templGuid);");
			stream_dispatchhc.println("\t// Create ocrEnvOutEdt as a finish EDT waiting on EnvIn");
			stream_dispatchhc.println("\tocrGuid_t outEdtGuid, outputDoneGuid;");
			stream_dispatchhc.println("\tocrGuid_t outDeps[] = { context->cncEnvOutTag, graphDoneGuid };");
			stream_dispatchhc.println("\tocrEdtTemplateCreate(&templGuid, cncEnvOutEdt, 1, 2);");
			stream_dispatchhc.println("\tocrEdtCreate(&outEdtGuid, templGuid,");
			stream_dispatchhc.println("\t\t/*paramc=*/EDT_PARAM_DEF, /*paramv=*/(u64*)&context,");
			stream_dispatchhc.println("\t\t/*depc=*/EDT_PARAM_DEF, /*depv=*/outDeps,");
			stream_dispatchhc.println("\t\t/*properties=*/EDT_PROP_FINISH,");
			stream_dispatchhc.println("\t\t/*affinity=*/NULL_GUID, /*outEvent=*/&outputDoneGuid);");
			stream_dispatchhc.println("\tocrEdtTemplateDestroy(templGuid);");
			stream_dispatchhc.println("\t// Create ocrEnvFreeEdt waiting on EnvOut");
			stream_dispatchhc.println("\tocrGuid_t freeEdtGuid;");
			stream_dispatchhc.println("\tocrEdtTemplateCreate(&templGuid, cncEnvFreeEdt, 1, 1);");
			stream_dispatchhc.println("\tocrEdtCreate(&freeEdtGuid, templGuid,");
			stream_dispatchhc.println("\t\t/*paramc=*/EDT_PARAM_DEF, /*paramv=*/(u64*)&context,");
			stream_dispatchhc.println("\t\t/*depc=*/EDT_PARAM_DEF, /*depv=*/&outputDoneGuid,");
			stream_dispatchhc.println("\t\t/*properties=*/EDT_PROP_NONE,");
			stream_dispatchhc.println("\t\t/*affinity=*/NULL_GUID, /*outEvent=*/NULL);");
			stream_dispatchhc.println("\tocrEdtTemplateDestroy(templGuid);");
			stream_dispatchhc.println("\t// start EnvIn now that the deps are all set up");
			stream_dispatchhc.println("\tocrAddDependence(depv[0].guid, inEdtGuid, 0, DB_DEFAULT_MODE);");
			stream_dispatchhc.println("\treturn NULL_GUID;");
			stream_dispatchhc.println("}");
			stream_dispatchhc.println();
		}
		catch (IOException ie){
			System.err.println(ie.getMessage());
			ie.printStackTrace();
		}
	}

	/**
	 * Generate a stub for the Main file
	 */
	private void generateMainStubHC() {
		try {
			//fill in additional info for steps:		
			for(String tag_name : tag_steps.keySet()){
				ArrayList<String> list_of_steps = tag_steps.get(tag_name);
				if(list_of_steps != null)
				for(int j = 0; j < list_of_steps.size(); j++){
					String step_name = (String)list_of_steps.get(j);
					step_info_local sil = steps_identifiers.get(step_name);
					if(sil != null) sil.prescribing_tag = tag_name;
				}
			}

			//Generate "Main" method
			File file_mainhc = new File(dir + "Main.c");
			if(!file_mainhc.exists()){
				PrintStream stream_mainhc = new PrintStream(file_mainhc);
				stream_mainhc.println();
				stream_mainhc.println("   /***** AUTO-GENERATED FILE from file " + filename + " - only generated if file does not exist (on running cncocr_t the first time) - feel free to edit *****/");
				stream_mainhc.println();
				stream_mainhc.println("#include \"Context.h\"");
				stream_mainhc.println();
				stream_mainhc.println("void cncEnvIn(int argc, char **argv, Context *context) {");

				//use "environment" variable to generate as accurate as possible suggestion code for items Put and steps prescribed
				String e_out="Ai", e_in="Ai";
				if(environment.outputs.size() > 0){
					e_out = environment.outputs.keySet().iterator().next();
				}
				
				StringBuilder buffer_step = new StringBuilder();
				int global_index = 0;
				global_index = GenerateOutputAndTagData(environment, buffer_step, global_index, "\t");
				if(buffer_step.length()>0)
					stream_mainhc.print(buffer_step.toString());
				else{
					stream_mainhc.println("\t/* Suggested code for writting items from environment:");
					stream_mainhc.println("\tvoid *val;\n");
					stream_mainhc.printf ("\tcncHandle_t valHandle = cncItemCreate_%s(&val);%n%n", e_out);
					stream_mainhc.println("\tchar *in_tag = createTag(3, i, j, k);\n");
					stream_mainhc.println("\tPut(valHandle, in_tag, context->"+e_out+");");
					stream_mainhc.println("\tCNC_PRESCRIBE(stepName, in_tag, context);\n\t*/");
				}


				List<Object> envIds = (List<Object>)environment.identifiers.getList();
				stream_mainhc.println("\t/*");
				stream_mainhc.printf("\tchar *envOutTag = createTag(%s", envIds.size());
				for (Object id : envIds) stream_mainhc.printf(", %s", id);
				stream_mainhc.println(");");
				stream_mainhc.println("\tsetEnvOutTag(envOutTag, context);");
				stream_mainhc.println("\t*/");
				stream_mainhc.println("}");
				stream_mainhc.println();

				stream_mainhc.println("void cncEnvOut("+envOutFunc+") {");
				stream_mainhc.println("\t/* Do stuff with your outputs */");
				stream_mainhc.println("}");
			}
		} catch (IOException ie){
			System.err.println(ie.getMessage());
			ie.printStackTrace();
		}
	}

	/**
	 * Generate a stub with what the step definitions should look like, considering the dependencies specified int the input file
	 * Additionally, generate files Common.c and Common.h. These need to be edited ONLY IF tag functions are NOT present in the cnc graph file
	 */
	private void generateSteps() {
		try {
			
			//Generate simultaneously files Common.c, Common.h and StepName.c
			File file_commonhc = new File (dir + "Common.c");
			PrintStream stream_commonhc = new PrintStream(file_commonhc);
			StringBuilder buffer_commonhc = new StringBuilder();
			buffer_commonhc.append("\n");
			buffer_commonhc.append("	/***** AUTO-GENERATED FILE. Do not modify unless tag functions are missing and the code generated as suggestion is in comment. *****/\n");
			buffer_commonhc.append("	/***** WARNING: this file WILL BE OVERWRITTEN on each call of cncocr_t " + filename + " *****/\n");
			buffer_commonhc.append("\n");
			buffer_commonhc.append("#include \"Common.h\"\n\n");

			File file_commonh = new File (dir + "Common.h");
			PrintStream stream_commonh = new PrintStream(file_commonh);
			StringBuilder buffer_commonh = new StringBuilder();
			buffer_commonh.append("\n");
			buffer_commonh.append("	/***** AUTO-GENERATED FILE. Do not modify unless tag functions are missing and the code generated as suggestion is in comment. *****/\n");
			buffer_commonh.append("	/***** WARNING: this file WILL BE OVERWRITTEN on each call of cncocr_t " + filename + " *****/\n");
			buffer_commonh.append("\n");
			buffer_commonh.append("#ifndef _COMMON_H\n");
			buffer_commonh.append("#define _COMMON_H\n");
			buffer_commonh.append("#include \"Dispatch.h\"\n\n");
			buffer_commonh.append("#include \"Context.h\"\n\n");

			buffer_commonh.append("void cncEnvIn(int argc, char **argv, Context *context);\n");
			generateStepHelpers("cncEnvOut", environment, 0, buffer_commonh, buffer_commonhc, envOutFunc);
			steps_name_list.add("cncEnvOut");
			steps_name_list.addAll(steps_identifiers.keySet());

			// Generate step's function stub
			File file_step;
			for (String step_name : steps_identifiers.keySet()) {
				Map<String, step_info_local> steps_identifiers_local = steps_identifiers;
				file_step = new File(dir + step_name+".c");

				boolean gen = true;
				PrintStream stream_step = null;
				if(file_step.exists())
					gen = false;
				else	
					stream_step = new PrintStream(file_step);
				StringBuilder buffer_step = new StringBuilder();
				step_info_local sil = steps_identifiers_local.get(step_name);
				StringBuilder function_definition = new StringBuilder();

				int global_index = generateStepHelpers(step_name, sil, 0, buffer_commonh, buffer_commonhc, function_definition);

				buffer_step.append("\n");
				buffer_step.append("#include \"Common.h\"\n");
		
				if(gen){
					buffer_step.append("void " + step_name + "( " + function_definition + "){\n");	
					if(!all_tag_functions_present){
						//generated suggested user code based on the cnc graph file
						if(sil.outputs.size()>0){
							buffer_step.append("\t/* Put output values into one or more of these output item collections: "+sil.outputs.keySet().toString()+"\n");
							buffer_step.append("\t   Function prototype: Put(item_to_put, item_tag, item_collection);\n");
							buffer_step.append("\t   Sample:\n");
							buffer_step.append("\t   /////////////////////////////////////////////////////////////////////////////////////\n");
							buffer_step.append("\t   double **data_to_put;\n");
							buffer_step.append("\t   // fill in data_to_put;\n");
							buffer_step.append("\t   char *newTag = createTag(3, i, j, k);\n");
							buffer_step.append("\t   Put(data_to_put, newTag, context->" + sil.outputs.keySet().iterator().next() + ");\n");
							buffer_step.append("\t   /////////////////////////////////////////////////////////////////////////////////////\n");
							buffer_step.append("\t*/\n\n");
						}
						if(sil.tags.size()>0){
							HashSet<String>  local_steps_prescribed = new HashSet<String>();
							for(String tag_step_name : sil.tags.keySet()){
								local_steps_prescribed.addAll(tag_steps.get(tag_step_name)) ;
							}
							if(local_steps_prescribed.size()>0){
								buffer_step.append("\t/* This step was defined to put the following tags: "+sil.tags.keySet().toString()+"\n");
								buffer_step.append("\t   So this step should prescribe one or more of the following steps: "+local_steps_prescribed.toString()+"\n");
								buffer_step.append("\t   Function prototype: CNC_PRESCRIBE(stepName, step_tag, context);\n");
								buffer_step.append("\t   Sample:\n");
								buffer_step.append("\t   /////////////////////////////////////////////////////////////////////////////////////\n");
								buffer_step.append("\t   char *newTag = createTag(3, i, j, k);\n");
								buffer_step.append("\t   CNC_PRESCRIBE("+local_steps_prescribed.iterator().next()+", newTag, context);\n");
								buffer_step.append("\t   /////////////////////////////////////////////////////////////////////////////////////\n");
								buffer_step.append("\t*/\n\n");
							}
						}
					}
					else{
						global_index = GenerateOutputAndTagData(sil, buffer_step, global_index, "\t");
					}
					buffer_step.append("}\n\n");
					stream_step.println(buffer_step.toString());
					stream_step.close();
				}
			}
			buffer_commonh.append("#endif /*_COMMON_H */");
			stream_commonh.println(buffer_commonh.toString());
			stream_commonh.close();
			stream_commonhc.println(buffer_commonhc.toString());
			stream_commonhc.close();
		}
		catch (IOException ie)
		{
			System.err.println(ie.getMessage());
			ie.printStackTrace();
		}
	}
	
	private int generateStepHelpers(String step_name, step_info_local sil, int global_index, StringBuilder buffer_commonh, StringBuilder buffer_commonhc, StringBuilder function_definition) {

		// GETS
		buffer_commonhc.append("/*\n" + step_name + " gets implementation\n*/\n");
		buffer_commonhc.append("ocrGuid_t " + step_name + "_gets(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]){\n\n");
		
		buffer_commonh.append("void " + step_name + "( ");
		
		if(all_tag_functions_present){
			LinkedList<StringBuilder> prototypeList = new LinkedList<StringBuilder>();
			global_index = GenerateInputData(GET, sil, buffer_commonhc, step_name, prototypeList);
			function_definition.append(prototypeList.get(0).toString());
			buffer_commonh.append(function_definition+" );\n");
			buffer_commonhc.append("\t" + step_name + "( " + prototypeList.get(1).toString() + " );\n");
			
			String tmp = prototypeList.get(0).toString();
			sil.prototype_withtypes.append(tmp.substring(0,tmp.lastIndexOf(",")));
			tmp = prototypeList.get(1).toString();
			sil.prototype_withouttypes.append(tmp.substring(0,tmp.lastIndexOf(",")));
		}
		else{
			function_definition.append(" ... ");
			buffer_commonh.append(function_definition+" );\n");
			buffer_commonhc.append("\t/* call __registerConsumer is (tag, context->item_coll, ocrGuid_t, dep_index++); for each dep added\n");
			buffer_commonhc.append("\t   then call the step: */\n\n");
			buffer_commonhc.append("\t" + step_name + "( " + " ... " + ");\n");
		}
		buffer_commonhc.append("\treturn NULL_GUID;\n");
		buffer_commonhc.append("}\n\n");

		// DEPS
		buffer_commonhc.append("/*\n" + step_name + " dependency adding implementation\n*/\n");
		buffer_commonhc.append("void " + step_name + "_dependencies(char *tag, Context *context){\n");
		if(all_tag_functions_present){
			GenerateInputData("__registerConsumer", sil, buffer_commonhc, step_name, null);
		}
		else{
			buffer_commonhc.append("/* The function prototype for __registerConsumer is (tag, context->item_coll, ocrGuid_t, dep_index)*/\n");
			buffer_commonhc.append("/* Note: All gets MUST be mentioned as dependencies in OCR */\n");
		}
		buffer_commonhc.append("}\n\n");

		return global_index;
	}


	private void generateMakefile()
	{
		try{
			// Step list (updatable)
			{
				File file = new File(dir + "steplist.mk");
				PrintStream out = new PrintStream(file);
				out.print("STEP_SRCS=");
				for (String step_name : steps_identifiers.keySet()) {
					out.print(step_name + ".c ");
				}
				out.println();
				out.close();
			}
			// Makefile (only need to generate once)
			File file = new File(dir + "Makefile");
			if(!file.exists())
			{
				PrintStream out = new PrintStream(file);
				StringBuilder sb = new StringBuilder();
				out.println("TARGET="+filename.replaceAll("[.]cnc$", ".exec"));
				out.println("CFLAGS=-g -I$(CNCOCR_HOME)/include -I$(OCR_HOME)/include -D__OCR__");
				out.println();
				out.println("include steplist.mk");
				out.println("SRCS=Main.c Common.c Context.c Dispatch.c $(STEP_SRCS)");
				out.println("OBJS=$(patsubst %.c,%.o,$(SRCS))");
				out.println();
				out.println("# include header globally for user-defined types");
				out.println("#CFLAGS+=-include user_types.h");
				out.println();
				out.println("compile: $(TARGET)");
				out.println();
				//out.println("# invoke translator to auto-generate code");
				//out.println("gen: "+filename);
				//out.println("\tcncocr_t $<");
				//out.println();
				out.println("# building source files");
				out.println("%.o: %.c");
				out.println("\tgcc $(CFLAGS) -c $<");
				out.println();

				String linking_compiler = "gcc";	

				out.println("# linking - creating the executable");
				out.println("$(TARGET): $(OBJS)");
				out.println("\t"+linking_compiler+" -L\"$(OCR_HOME)/lib\" \\");
				out.println("\t	-L\"$(CNCOCR_HOME)/lib\" \\");
				out.println("\t	$(OBJS) \\");
				out.println("\t	-locr -lcncocr -o$@");
				out.println();
				out.println("# delete binaries");
				out.println("clean:");
				out.println("\trm -f $(OBJS) $(TARGET)");
				out.println();
				out.println("# delete binaries and scaffolding files");
				out.println("squeaky: clean");
				out.println("\trm {Context,Dispatch,Common}.[ch] steplist.mk");
			}
		}catch(Exception e){ System.err.println("Unable to write makefile"); }
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Helpers for generating steps (methods for Inputs)
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	private int GenerateInputData(String function_name, step_info_local sil, StringBuilder out, String step_name, LinkedList<StringBuilder> prototypeList){
		StringBuilder prototype1 = new StringBuilder();
		StringBuilder prototype2 = new StringBuilder();
		LinkedList<StringBuilder> prototypeListIn = new LinkedList<StringBuilder>();

		String tagNameOCR="tag";
		if(function_name==GET){
			out.append("\tContext *context = (Context*)paramv[1];\n");
			tagNameOCR="(char*)paramv[0]";
		}
		int global_index = 0;
		String indextype;
		if(sil.prescribing_tag != null){
			tag_type_local lttl = all_tags.get(sil.prescribing_tag);
			if(lttl == null){
				System.out.println("Tag not found! Tag name is " + sil.prescribing_tag + " ...exiting");
				System.exit(1);
			}
			indextype = prettyType(lttl.tagtype);
			assert(sil != null);
			if(sil.identifiers == null){
				System.err.println("Step "+step_name+" is missing its tag info (never used?)\n");
				System.exit(1);
			}
			else if(lttl.dim != sil.identifiers.size()){
				System.err.println("Step "+step_name+" is prescribed by a tag item with different size\n");
				System.exit(1);
			}
		}
		else
			indextype = "int ";

		//identifier can be a range now, get them separately
		if (sil.identifiers == null) {
			System.err.print("ERROR: Missing tag function for ");
			if (sil == environment) System.out.println("environment");
			else System.out.printf("step %s%n", step_name);
			System.exit(-1);
		}
		int size = sil.identifiers.size();
		int counter = 0;
		for(int sili = 0; sili < size; sili++){
			step_component sc = (step_component) sil.identifiers.getstep_componentAt(counter);
			if(sc.getname() != null){
				out.append("\t" + indextype + sc.getname() + " = getTag("+tagNameOCR+", "+sili+");\n");
				prototype1.append(indextype + sc.getname() +", ");
				prototype2.append(sc.getname()+", ");
			}
			else{
				out.append("\t" + indextype + sc.getstart_range() + " = getTag("+tagNameOCR+", "+sili+");\n");
				prototype1.append(indextype + sc.getstart_range() +", ");
				prototype2.append(sc.getstart_range()+", ");
				sili++;
				out.append("\t" + indextype + sc.getend_range() + " = getTag("+tagNameOCR+", "+sili+");\n");
				prototype1.append(indextype + sc.getend_range() +", ");
				prototype2.append(sc.getend_range()+", ");
				size++;
			}
			counter ++;
		}

		if(function_name != GET) {
			out.append("\n\tocrGuid_t edt_guid;\n");
			out.append("\tu64 args[] = { (u64)"+tagNameOCR+", (u64)context };\n");
			out.append("\tocrEdtCreate(&edt_guid, context->"+step_name+".taskTemplate,\n");
			out.append("\t\t/*paramc=*/EDT_PARAM_DEF, /*paramv=*/args,\n");
			out.append("\t\t/*depc=*/0"+step_no_gets.get(step_name)+", /*depv=*/NULL,\n");
			out.append("\t\t/*properties=*/EDT_PROP_NONE,\n");
			out.append("\t\t/*affinity=*/NULL_GUID, /*outEvent=*/NULL);\n");
		}

		out.append("\n\tint edt_index=0;\n");
		
		StringBuilder number_of_gets = new StringBuilder();
		for (String input_name : sil.inputs.keySet()){
			InputCollectionLocal icl = sil.inputs.get(input_name);
			LinkedList<LinkedList<TagFunctionLocal>> lltfl = icl.tag_functions;
			for(int iltfl=0; iltfl < lltfl.size(); iltfl ++){
				LinkedList<TagFunctionLocal> ltfl = lltfl.get(iltfl);
				generateTagCodeIn(out, input_name, ltfl, global_index++, function_name, prototypeListIn, "\t");

				prototype1.append( prototypeListIn.get(0).toString() + ", " );
				prototype2.append( prototypeListIn.get(1).toString() + ", " );
				number_of_gets.append(" + " + prototypeListIn.get(2).toString());
				prototypeListIn.clear();
			}
		}
		if(function_name == GET) {
			step_no_gets.put(step_name, number_of_gets.toString());
		}

		if(prototypeList != null){
			prototype1.append("Context *context");
			prototype2.append("context");
			prototypeList.add(prototype1);
			prototypeList.add(prototype2);
		}

		return global_index;
	}

	private void generateTagCodeIn(StringBuilder out, String input_name, LinkedList<TagFunctionLocal> ltfl, int index, String function_name, LinkedList<StringBuilder> prototypeList, String initial_indent){
		boolean isGetFunction = function_name.equals(GET);
		StringBuilder prototype1 = new StringBuilder();
		StringBuilder prototype2 = new StringBuilder();
		StringBuilder number_of_gets = new StringBuilder();
		Iitem_type itemtype = all_items.get(input_name);
		if(itemtype == null){
			System.out.println("Item not found! Input name is " + input_name+ " ...exiting");
			System.exit(1);
		}
		String lindex = "_i";
		StringBuilder tabs = new StringBuilder(initial_indent);
		StringBuilder for_index = new StringBuilder();
		int no_ranges = 0;
		StringBuilder ilist = new StringBuilder();
		StringBuilder indexlist = new StringBuilder();
		StringBuilder forloops = new StringBuilder();
		StringBuilder endforloops = new StringBuilder();
		String collEntryType = input_name+"Item";

		StringBuilder stars = new StringBuilder();
		LinkedList<StringBuilder> alloc_list = new LinkedList<StringBuilder>();
		alloc_list.add(new StringBuilder());
		StringBuilder alloc = new StringBuilder();
		String alloc_endforloops = "";

		String previousfor = "";
		String previousrange = "";
		for(int i=0; i<ltfl.size(); i++){
			TagFunctionLocal tfl = ltfl.get(i);
			if(tfl instanceof RangeLocal){
				String lindex_i = lindex + i;
				stars.append("*");
				alloc_list.get(no_ranges).append(previousfor);
				alloc_list.get(no_ranges).append(tabs + input_name + index + for_index + " = ");
				previousrange = ((RangeLocal)tfl).stop.toString()+" - "+((RangeLocal)tfl).start.toString();
				number_of_gets.append("("+previousrange+")*");
				StringBuilder sbl = new StringBuilder(") * (" + previousrange + ") );\n");
				alloc_list.add(sbl);
				alloc_endforloops = endforloops.toString();

				no_ranges++;
				ilist.append(lindex_i + " + " + ((RangeLocal)tfl).start.toString());
				for_index.append("[" + lindex_i + "]");
				if(indexlist.length()>0) indexlist.append(", ");
				indexlist.append(lindex_i);
				previousfor = tabs + "for("+lindex_i+" = 0; "+lindex_i+" < "+previousrange+"; "+lindex_i+"++){\n";
				forloops.append(previousfor);
				endforloops.insert(0, tabs + "}\n");
				tabs.append("\t");
			}
			else{
				ilist.append(((AritmExpressionLocal)tfl).toString());
				number_of_gets.append("1*");
			}
			if (i!= ltfl.size()-1)
				ilist.append(", ");
		}
		number_of_gets.deleteCharAt(number_of_gets.length()-1);

		out.append("\n");
		if(no_ranges>0){
			out.append(initial_indent+"int "+indexlist+";\n");
		}

		//Note: CAN have a range of a collection of itemtype and not reference type.	
		String newinput_name = "", newinput_type="";
		String stars_s = stars.toString();
		String deref = (itemtype instanceof PointerType) ? "" : "*"; // Dereference non-pointer data
		String other_for_index = for_index.toString();
		if(isGetFunction) {
			newinput_name = input_name + index;
			newinput_type = prettyType(itemtype.toString() + deref);
			// Declare the entry
			String collEntryTypePretty = prettyType(collEntryType+stars);
			out.append(initial_indent + collEntryTypePretty + input_name + index + ";\n");
			prototype1.append(collEntryTypePretty + newinput_name);
			prototype2.append(newinput_name);
			// GET: Range
			if(no_ranges > 0){
				for(int i = 0; i < alloc_list.size()-1; i++){
					alloc.append(alloc_list.get(i).toString() + "malloc ( sizeof(" + collEntryType);
					stars_s = stars_s.substring(1);
					alloc.append(stars_s);
				}
				alloc.append(alloc_list.getLast());
				out.append(alloc.toString()+"\n");
				out.append(alloc_endforloops);
			}
		}

		out.append(forloops); // START FOR NEST

		// GET: Copy pointer value from ocrEdtDep_t struct
		if(isGetFunction) {
			out.append(String.format("%s%s%s.item = %s(%s)depv[edt_index].ptr;\n",
									 tabs, newinput_name, other_for_index, deref, newinput_type));
			out.append(String.format("%s%s%s.handle = depv[edt_index++].guid;\n",
									 tabs, newinput_name, other_for_index));
		}
		// step_dependencies: add dependencies (register) using tags
		else {
			out.append(tabs + "char *tag"+ input_name + index + " = createTag(" + ltfl.size() + ", " + ilist + ");\n");
			out.append(tabs + function_name +"( tag"+ input_name + index +", context->" +input_name + ", edt_guid, edt_index++);\n");
		}

		out.append(endforloops); // END FOR NEST

		if(prototypeList != null){
			prototypeList.add(prototype1);
			prototypeList.add(prototype2);
			prototypeList.add(number_of_gets);
		}
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Helpers for generating steps (methods for Outputs and Tags)
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	private int GenerateOutputAndTagData(step_info_local sil, StringBuilder buffer_step, int global_index, String initial_indent){
		if(!fullauto && sil.outputs.keySet().size()>0)
			buffer_step.append(initial_indent+"/* This is suggested code for outputs (Put calls)- fix namings to match the data got if tag functions are missing or dependent on the inputs\n");
		StringBuilder collectPutCalls = new StringBuilder(); 
		for (String output_name : sil.outputs.keySet()){
			OutputCollectionLocal ocl = sil.outputs.get(output_name);
			LinkedList<LinkedList<TagFunctionLocal>> lltfl = ocl.tag_functions;
			for(int iltfl=0; iltfl < lltfl.size(); iltfl ++){
				LinkedList<TagFunctionLocal> ltfl = lltfl.get(iltfl);
				generateTagCodeOut(buffer_step, output_name, ltfl, global_index++, initial_indent, collectPutCalls, sil);
			}
		}
		if(fullauto && sil!= environment){
			if(sil != null && sil.affinityList != null && affinity_enabled && sil.affinityList.size()>0){
				String device_name = sil.affinityList.getstep_affinityAt(0).getname().toString().toLowerCase();
				String device_place = deviceHCPlace(device_name);
				if(! isDeviceName(device_name)){
					System.err.println("Error: The devices for which the affinity can be specified are: "+getDevices());
					System.exit(1);
				}
				
				buffer_step.append("\tif(current_place() == "+device_place+"){\n");
				buffer_step.append("\t\t"+sil.step_name+"_"+device_name+"("+sil.prototype_withouttypes+");\n\t}\n");
				user_written_step_methods_buffer.append("void " + sil.step_name+"_"+device_name+"("+sil.prototype_withtypes+");\n");
				
				for(int i=1; i<sil.affinityList.size(); i++){
					device_name = sil.affinityList.getstep_affinityAt(i).getname().toString().toLowerCase();
					device_place = deviceHCPlace(device_name);
					if(! isDeviceName(device_name)){
						System.err.println("Error: The devices for which the affinity can be specified are: "+getDevices());
						System.exit(1);
					}
					buffer_step.append("\telse if(current_place() == "+device_place+"){\n");
					buffer_step.append("\t\t"+sil.step_name+"_"+device_name+"("+sil.prototype_withouttypes+");\n\t}\n");
					user_written_step_methods_buffer.append("void " + sil.step_name+"_"+device_name+"("+sil.prototype_withtypes+");\n");
					
				}
			}
			else{
				buffer_step.append("\t"+sil.step_name+"_"+"cpu"+"("+sil.prototype_withouttypes+");\n");
				user_written_step_methods_buffer.append("void " + sil.step_name+"_"+"cpu"+"("+sil.prototype_withtypes+");\n");
			}
		}
		buffer_step.append(collectPutCalls);
		if(!fullauto && sil.outputs.keySet().size()>0)
			buffer_step.append(initial_indent+"*/\n");
		
		
		if(!fullauto && sil.tags.keySet().size()>0)
			buffer_step.append(initial_indent + "/* This is suggested code for enabled steps (prescribe calls) - fix namings to match the data got if tag functions are missing or dependent on the inputs\n");
		for (String tag_name : sil.tags.keySet()){
			ArrayList<String> step_list = tag_steps.get(tag_name);
			LinkedList<String> steps_prescribed = new LinkedList<String>();
			if (step_list != null){
				for (int j = 0; j < step_list.size(); j++)
				{
					String si_name = (String) step_list.get(j);
					if(!steps_prescribed.contains(si_name))
						steps_prescribed.add(si_name);
				}

				TagCollectionLocal tcl = sil.tags.get(tag_name);
				LinkedList<LinkedList<TagFunctionLocal>> lltfl = tcl.tag_functions;
				for(int iltfl=0; iltfl < lltfl.size(); iltfl ++){
					LinkedList<TagFunctionLocal> ltfl = lltfl.get(iltfl);
					generateTagCodeTag(buffer_step, tag_name, ltfl, global_index++, steps_prescribed, initial_indent);
				}
			}
		}
		if(!fullauto && sil.tags.keySet().size()>0)
			buffer_step.append(initial_indent+"*/\n");
		return global_index;
	}

	private void generateTagCodeOut(StringBuilder out, String output_name, LinkedList<TagFunctionLocal> ltfl, int index, String initial_indent, StringBuilder puts, step_info_local sil){
		String lindex = "_index"+index+"_";
		StringBuilder tabs = new StringBuilder(initial_indent);
		StringBuilder ranges = new StringBuilder();
		StringBuilder for_index = new StringBuilder();
		int no_ranges = 0;
		StringBuilder ilist = new StringBuilder();
		StringBuilder indexlist = new StringBuilder();
		StringBuilder forloops = new StringBuilder();
		StringBuilder endforloops = new StringBuilder();
		for(int i=0; i<ltfl.size(); i++){
			TagFunctionLocal tfl = ltfl.get(i);
			if(tfl instanceof RangeLocal){
				ranges.append("[" + ((RangeLocal)tfl).stop.toString() +"-"+ ((RangeLocal)tfl).start.toString()+"]");
				no_ranges++;
				ilist.append(lindex + i + " + "+((RangeLocal)tfl).start.toString());
				for_index.append("[" + lindex + i + "]");
				if(indexlist.length()>0) indexlist.append(", ");
				indexlist.append(lindex + i);
				forloops.append(tabs + "for("+lindex+i+" = 0; "+lindex+i+" < "+((RangeLocal)tfl).stop.toString()+" - "+((RangeLocal)tfl).start.toString()+"; "+lindex+i+"++){\n");
				endforloops.insert(0, tabs + "}\n");
				tabs.append("\t");
			}
			else
				ilist.append(((AritmExpressionLocal)tfl).toString());
			if (i!= ltfl.size()-1)
				ilist.append(", ");
		}

		if(no_ranges>0)
			out.append(initial_indent+"int "+indexlist+";\n");

		//Note: CAN have a range of a collection of itemtype and not reference type.	
		Iitem_type itemtype = all_items.get(output_name);
		String itemTypePretty = prettyType(itemtype);
		if(itemtype == null){
			System.out.println("Item not found! Output name is " + output_name+ " ...exiting");
			System.exit(1);
		}
		StringBuilder extra_stars = new StringBuilder();
		String comment_on_stars = "";
		String itemTypePrettyStars = prettyType(itemTypePretty+extra_stars);
		if(no_ranges > 0){
			comment_on_stars = "//extra \"*\" added for: "+ranges;
			for(int i=0; i<no_ranges;i++){
				extra_stars.append("*");
			}
		}
		if(!(itemtype instanceof PointerType)){
			if(!fullauto)
				out.append(initial_indent + prettyType(itemTypePretty+"*") + output_name + index + ranges + ";\n");
			else{
				out.append(initial_indent + prettyType(itemTypePrettyStars+"*") + output_name + index + ";" + comment_on_stars +"\n" );
				sil.prototype_withtypes.append(", " + prettyType(itemTypePrettyStars+"*") + output_name + index);
				sil.prototype_withouttypes.append(", " + output_name + index);
			}
		}
		else if(!fullauto)
			out.append(initial_indent + itemTypePretty + output_name + index + ranges + ";\n");
		else{
			out.append(initial_indent + itemTypePrettyStars + output_name + index + ";" + comment_on_stars +"\n" );
			sil.prototype_withtypes.append(", " + itemTypePrettyStars + output_name + index);
			sil.prototype_withouttypes.append(", " + output_name + index);
		}
		
		
		if(fullauto){
			out.append(initial_indent + output_name+index+fullAutoUserDefined+"(&"+output_name+index+");\n"); //outside Put loops
			user_written_alloc_methods_buffer.append("void "+output_name+index+fullAutoUserDefined+"("+itemtype+"*");
			user_written_alloc_methods_buffer.append(extra_stars.toString());
			if(!(itemtype instanceof PointerType))
				user_written_alloc_methods_buffer.append("*");
			user_written_alloc_methods_buffer.append(" "+output_name+");\n");
			
		}
		puts.append(forloops);
		String itemCount = (itemtype instanceof PointerType) ? ", 1" : "";
		puts.append(String.format("%scncHandle_t %s%s_handle = "+
					              "cncCreateItem_%s(&%s%s%s%s);%n"+
		                          "%s// TODO: *%s%s%s = ???;%n",
		                          tabs, output_name, index,
								  output_name, output_name, index, for_index, itemCount,
		                          tabs, output_name, index, for_index));
		puts.append(tabs + "char *tag"+ output_name + index + " = createTag(" + ltfl.size() + ", " + ilist + ");\n");
		puts.append(tabs + "Put(" + output_name + index + "_handle" + ", tag"+ output_name + index +", context->" +output_name + ");\n");
		puts.append(endforloops);
		puts.append("\n");
	}

	private void generateTagCodeTag(StringBuilder out, String input_name, LinkedList<TagFunctionLocal> ltfl, int index, LinkedList<String> steps_prescribed, String initial_indent){
		String lindex = "_index"+index+"_";
		StringBuilder tabs = new StringBuilder(initial_indent);
		StringBuilder ranges = new StringBuilder();
		StringBuilder for_index = new StringBuilder();
		int no_ranges = 0;
		StringBuilder ilist = new StringBuilder();
		StringBuilder indexlist = new StringBuilder();
		StringBuilder forloops = new StringBuilder();
		StringBuilder endforloops = new StringBuilder();
		for(int i=0; i<ltfl.size(); i++){
			TagFunctionLocal tfl = ltfl.get(i);
			if(tfl instanceof RangeLocal){
				ranges.append("[" + ((RangeLocal)tfl).stop.toString() +"-"+ ((RangeLocal)tfl).start.toString()+"]");
				no_ranges++;
				ilist.append(lindex + i);
				for_index.append("[" + lindex + i + "]");
				if(indexlist.length()>0) indexlist.append(", ");
				indexlist.append(lindex + i);
				forloops.append(tabs + "for("+lindex+i+" = " + ((RangeLocal)tfl).start.toString() + "; "+lindex+i+" < "+((RangeLocal)tfl).stop.toString()+"; "+lindex+i+"++){\n");
				endforloops.insert(0, tabs + "}\n");
				tabs.append("\t");
			}
			else
				ilist.append(((AritmExpressionLocal)tfl).toString());
			if (i!= ltfl.size()-1)
				ilist.append(", ");
		}

		if(no_ranges>0)
			out.append(initial_indent + "int "+indexlist+";\n");

		out.append(forloops);
		out.append(tabs + "char *tag"+ input_name + index + " = createTag(" + ltfl.size() + ", " + ilist + ");\n");
		for(String step_name : steps_prescribed){
			out.append(tabs + "CNC_PRESCRIBE(" + step_name + ", tag"+ input_name + index +", context);\n");
		}
		out.append(endforloops);
		out.append("\n");	
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Print the common header in every file we generate
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void printHeader(PrintStream out){
		out.println();
		out.println("   // ***** AUTO-GENERATED FILE FROM " + filename + ", DO NOT MODIFY!  *****//");
		out.println();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Helpers for getting devices
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	public static boolean isDeviceName(String s){
		return s.equalsIgnoreCase("CPU") || s.equalsIgnoreCase("GPU") || s.equalsIgnoreCase("FPGA");
	}

	public static String getDevices(){
		return " CPU, GPU, FPGA";
	}

	public static String deviceUserPlace(String s){
		if(s.equalsIgnoreCase("GPU"))
			return "(gpu_pl)";
		if(s.equalsIgnoreCase("FPGA"))
			return "(fpga_pl)";
		if(s.equalsIgnoreCase("CPU"))
			return "(cpuroot_pl)";
		return "";
	}
	
	public static String deviceHCPlace(String s){
		if(s.equalsIgnoreCase("GPU"))
			return "NVGPU_PLACE";
		if(s.equalsIgnoreCase("FPGA"))
			return "FPGA_PLACE";
		if(s.equalsIgnoreCase("CPU"))
			return "MEM_PLACE";
		return "";
	}
	public void unimplementedVisitor(String s) {}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Other helpers
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	public static String prettyType(Object rawType) {
		String[] parts = typeParts(rawType.toString());
		return String.format("%s %s", parts[0], parts[1]);
	}

	public static String prettyCastType(Object rawType) {
		String[] parts = typeParts(rawType.toString());
		return parts[0] + parts[1];
	}

	public static String[] typeParts(String rawTypeStr) {
		return new String[] {
			rawTypeStr.replaceAll("[*]", "").trim(),
			rawTypeStr.replaceAll("[^*]", "")
		};
	}
}

