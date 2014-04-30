
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser.Ast;

import lpg.runtime.*;

public interface Visitor extends IAstVisitor
{
    boolean visit(Ast n);
    void endVisit(Ast n);

    boolean visit(AstToken n);
    void endVisit(AstToken n);

    boolean visit(statementList n);
    void endVisit(statementList n);

    boolean visit(terminated_declaration n);
    void endVisit(terminated_declaration n);

    boolean visit(terminated_relation n);
    void endVisit(terminated_relation n);

    boolean visit(StepExecution n);
    void endVisit(StepExecution n);

    boolean visit(StepPrescription n);
    void endVisit(StepPrescription n);

    boolean visit(instanceList n);
    void endVisit(instanceList n);

    boolean visit(item_declaration n);
    void endVisit(item_declaration n);

    boolean visit(item_instance n);
    void endVisit(item_instance n);

    boolean visit(item_definition n);
    void endVisit(item_definition n);

    boolean visit(PointerType n);
    void endVisit(PointerType n);

    boolean visit(tag_declaration n);
    void endVisit(tag_declaration n);

    boolean visit(tag_instance n);
    void endVisit(tag_instance n);

    boolean visit(tag_definition n);
    void endVisit(tag_definition n);

    boolean visit(tag_componentList n);
    void endVisit(tag_componentList n);

    boolean visit(tag_type n);
    void endVisit(tag_type n);

    boolean visit(tag_component n);
    void endVisit(tag_component n);

    boolean visit(aritm_expr n);
    void endVisit(aritm_expr n);

    boolean visit(aritm_term n);
    void endVisit(aritm_term n);

    boolean visit(aritm_factor n);
    void endVisit(aritm_factor n);

    boolean visit(step_declaration n);
    void endVisit(step_declaration n);

    boolean visit(step_instance n);
    void endVisit(step_instance n);

    boolean visit(step_componentList n);
    void endVisit(step_componentList n);

    boolean visit(step_component n);
    void endVisit(step_component n);

    boolean visit(t_type n);
    void endVisit(t_type n);

    boolean visit(step_instance_affList n);
    void endVisit(step_instance_affList n);

    boolean visit(step_instance_aff n);
    void endVisit(step_instance_aff n);

    boolean visit(step_affinityList n);
    void endVisit(step_affinityList n);

    boolean visit(step_affinity n);
    void endVisit(step_affinity n);

    boolean visit(step_instance_environment n);
    void endVisit(step_instance_environment n);

    boolean visit(attributeList n);
    void endVisit(attributeList n);

    boolean visit(VariableAttribute n);
    void endVisit(VariableAttribute n);

    boolean visit(IntegerAttribute n);
    void endVisit(IntegerAttribute n);

    boolean visit(StringAttribute n);
    void endVisit(StringAttribute n);

    boolean visit(item_type0 n);
    void endVisit(item_type0 n);

    boolean visit(item_type1 n);
    void endVisit(item_type1 n);

    boolean visit(item_type2 n);
    void endVisit(item_type2 n);

    boolean visit(step_instance_name0 n);
    void endVisit(step_instance_name0 n);

    boolean visit(step_instance_name1 n);
    void endVisit(step_instance_name1 n);

}


