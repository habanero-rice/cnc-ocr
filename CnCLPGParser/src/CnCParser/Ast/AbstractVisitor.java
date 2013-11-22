
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser.Ast;

import lpg.runtime.*;

public abstract class AbstractVisitor implements Visitor
{
    public abstract void unimplementedVisitor(String s);

    public boolean preVisit(IAst element) { return true; }

    public void postVisit(IAst element) {}

    public boolean visit(AstToken n) { unimplementedVisitor("visit(AstToken)"); return true; }
    public void endVisit(AstToken n) { unimplementedVisitor("endVisit(AstToken)"); }

    public boolean visit(statementList n) { unimplementedVisitor("visit(statementList)"); return true; }
    public void endVisit(statementList n) { unimplementedVisitor("endVisit(statementList)"); }

    public boolean visit(terminated_declaration n) { unimplementedVisitor("visit(terminated_declaration)"); return true; }
    public void endVisit(terminated_declaration n) { unimplementedVisitor("endVisit(terminated_declaration)"); }

    public boolean visit(terminated_relation n) { unimplementedVisitor("visit(terminated_relation)"); return true; }
    public void endVisit(terminated_relation n) { unimplementedVisitor("endVisit(terminated_relation)"); }

    public boolean visit(StepExecution n) { unimplementedVisitor("visit(StepExecution)"); return true; }
    public void endVisit(StepExecution n) { unimplementedVisitor("endVisit(StepExecution)"); }

    public boolean visit(StepPrescription n) { unimplementedVisitor("visit(StepPrescription)"); return true; }
    public void endVisit(StepPrescription n) { unimplementedVisitor("endVisit(StepPrescription)"); }

    public boolean visit(instanceList n) { unimplementedVisitor("visit(instanceList)"); return true; }
    public void endVisit(instanceList n) { unimplementedVisitor("endVisit(instanceList)"); }

    public boolean visit(item_declaration n) { unimplementedVisitor("visit(item_declaration)"); return true; }
    public void endVisit(item_declaration n) { unimplementedVisitor("endVisit(item_declaration)"); }

    public boolean visit(item_instance n) { unimplementedVisitor("visit(item_instance)"); return true; }
    public void endVisit(item_instance n) { unimplementedVisitor("endVisit(item_instance)"); }

    public boolean visit(item_definition n) { unimplementedVisitor("visit(item_definition)"); return true; }
    public void endVisit(item_definition n) { unimplementedVisitor("endVisit(item_definition)"); }

    public boolean visit(PointerType n) { unimplementedVisitor("visit(PointerType)"); return true; }
    public void endVisit(PointerType n) { unimplementedVisitor("endVisit(PointerType)"); }

    public boolean visit(tag_declaration n) { unimplementedVisitor("visit(tag_declaration)"); return true; }
    public void endVisit(tag_declaration n) { unimplementedVisitor("endVisit(tag_declaration)"); }

    public boolean visit(tag_instance n) { unimplementedVisitor("visit(tag_instance)"); return true; }
    public void endVisit(tag_instance n) { unimplementedVisitor("endVisit(tag_instance)"); }

    public boolean visit(tag_definition n) { unimplementedVisitor("visit(tag_definition)"); return true; }
    public void endVisit(tag_definition n) { unimplementedVisitor("endVisit(tag_definition)"); }

    public boolean visit(tag_componentList n) { unimplementedVisitor("visit(tag_componentList)"); return true; }
    public void endVisit(tag_componentList n) { unimplementedVisitor("endVisit(tag_componentList)"); }

    public boolean visit(tag_type n) { unimplementedVisitor("visit(tag_type)"); return true; }
    public void endVisit(tag_type n) { unimplementedVisitor("endVisit(tag_type)"); }

    public boolean visit(tag_component n) { unimplementedVisitor("visit(tag_component)"); return true; }
    public void endVisit(tag_component n) { unimplementedVisitor("endVisit(tag_component)"); }

    public boolean visit(aritm_expr n) { unimplementedVisitor("visit(aritm_expr)"); return true; }
    public void endVisit(aritm_expr n) { unimplementedVisitor("endVisit(aritm_expr)"); }

    public boolean visit(aritm_term n) { unimplementedVisitor("visit(aritm_term)"); return true; }
    public void endVisit(aritm_term n) { unimplementedVisitor("endVisit(aritm_term)"); }

    public boolean visit(aritm_factor n) { unimplementedVisitor("visit(aritm_factor)"); return true; }
    public void endVisit(aritm_factor n) { unimplementedVisitor("endVisit(aritm_factor)"); }

    public boolean visit(step_declaration n) { unimplementedVisitor("visit(step_declaration)"); return true; }
    public void endVisit(step_declaration n) { unimplementedVisitor("endVisit(step_declaration)"); }

    public boolean visit(step_instance n) { unimplementedVisitor("visit(step_instance)"); return true; }
    public void endVisit(step_instance n) { unimplementedVisitor("endVisit(step_instance)"); }

    public boolean visit(step_componentList n) { unimplementedVisitor("visit(step_componentList)"); return true; }
    public void endVisit(step_componentList n) { unimplementedVisitor("endVisit(step_componentList)"); }

    public boolean visit(step_component n) { unimplementedVisitor("visit(step_component)"); return true; }
    public void endVisit(step_component n) { unimplementedVisitor("endVisit(step_component)"); }

    public boolean visit(t_type n) { unimplementedVisitor("visit(t_type)"); return true; }
    public void endVisit(t_type n) { unimplementedVisitor("endVisit(t_type)"); }

    public boolean visit(step_instance_affList n) { unimplementedVisitor("visit(step_instance_affList)"); return true; }
    public void endVisit(step_instance_affList n) { unimplementedVisitor("endVisit(step_instance_affList)"); }

    public boolean visit(step_instance_aff n) { unimplementedVisitor("visit(step_instance_aff)"); return true; }
    public void endVisit(step_instance_aff n) { unimplementedVisitor("endVisit(step_instance_aff)"); }

    public boolean visit(step_affinityList n) { unimplementedVisitor("visit(step_affinityList)"); return true; }
    public void endVisit(step_affinityList n) { unimplementedVisitor("endVisit(step_affinityList)"); }

    public boolean visit(step_affinity n) { unimplementedVisitor("visit(step_affinity)"); return true; }
    public void endVisit(step_affinity n) { unimplementedVisitor("endVisit(step_affinity)"); }

    public boolean visit(step_instance_environment n) { unimplementedVisitor("visit(step_instance_environment)"); return true; }
    public void endVisit(step_instance_environment n) { unimplementedVisitor("endVisit(step_instance_environment)"); }

    public boolean visit(attributeList n) { unimplementedVisitor("visit(attributeList)"); return true; }
    public void endVisit(attributeList n) { unimplementedVisitor("endVisit(attributeList)"); }

    public boolean visit(VariableAttribute n) { unimplementedVisitor("visit(VariableAttribute)"); return true; }
    public void endVisit(VariableAttribute n) { unimplementedVisitor("endVisit(VariableAttribute)"); }

    public boolean visit(IntegerAttribute n) { unimplementedVisitor("visit(IntegerAttribute)"); return true; }
    public void endVisit(IntegerAttribute n) { unimplementedVisitor("endVisit(IntegerAttribute)"); }

    public boolean visit(StringAttribute n) { unimplementedVisitor("visit(StringAttribute)"); return true; }
    public void endVisit(StringAttribute n) { unimplementedVisitor("endVisit(StringAttribute)"); }

    public boolean visit(item_type0 n) { unimplementedVisitor("visit(item_type0)"); return true; }
    public void endVisit(item_type0 n) { unimplementedVisitor("endVisit(item_type0)"); }

    public boolean visit(item_type1 n) { unimplementedVisitor("visit(item_type1)"); return true; }
    public void endVisit(item_type1 n) { unimplementedVisitor("endVisit(item_type1)"); }

    public boolean visit(item_type2 n) { unimplementedVisitor("visit(item_type2)"); return true; }
    public void endVisit(item_type2 n) { unimplementedVisitor("endVisit(item_type2)"); }


    public boolean visit(Ast n)
    {
        if (n instanceof AstToken) return visit((AstToken) n);
        else if (n instanceof statementList) return visit((statementList) n);
        else if (n instanceof terminated_declaration) return visit((terminated_declaration) n);
        else if (n instanceof terminated_relation) return visit((terminated_relation) n);
        else if (n instanceof StepExecution) return visit((StepExecution) n);
        else if (n instanceof StepPrescription) return visit((StepPrescription) n);
        else if (n instanceof instanceList) return visit((instanceList) n);
        else if (n instanceof item_declaration) return visit((item_declaration) n);
        else if (n instanceof item_instance) return visit((item_instance) n);
        else if (n instanceof item_definition) return visit((item_definition) n);
        else if (n instanceof PointerType) return visit((PointerType) n);
        else if (n instanceof tag_declaration) return visit((tag_declaration) n);
        else if (n instanceof tag_instance) return visit((tag_instance) n);
        else if (n instanceof tag_definition) return visit((tag_definition) n);
        else if (n instanceof tag_componentList) return visit((tag_componentList) n);
        else if (n instanceof tag_type) return visit((tag_type) n);
        else if (n instanceof tag_component) return visit((tag_component) n);
        else if (n instanceof aritm_expr) return visit((aritm_expr) n);
        else if (n instanceof aritm_term) return visit((aritm_term) n);
        else if (n instanceof aritm_factor) return visit((aritm_factor) n);
        else if (n instanceof step_declaration) return visit((step_declaration) n);
        else if (n instanceof step_instance) return visit((step_instance) n);
        else if (n instanceof step_componentList) return visit((step_componentList) n);
        else if (n instanceof step_component) return visit((step_component) n);
        else if (n instanceof t_type) return visit((t_type) n);
        else if (n instanceof step_instance_affList) return visit((step_instance_affList) n);
        else if (n instanceof step_instance_aff) return visit((step_instance_aff) n);
        else if (n instanceof step_affinityList) return visit((step_affinityList) n);
        else if (n instanceof step_affinity) return visit((step_affinity) n);
        else if (n instanceof step_instance_environment) return visit((step_instance_environment) n);
        else if (n instanceof attributeList) return visit((attributeList) n);
        else if (n instanceof VariableAttribute) return visit((VariableAttribute) n);
        else if (n instanceof IntegerAttribute) return visit((IntegerAttribute) n);
        else if (n instanceof StringAttribute) return visit((StringAttribute) n);
        else if (n instanceof item_type0) return visit((item_type0) n);
        else if (n instanceof item_type1) return visit((item_type1) n);
        else if (n instanceof item_type2) return visit((item_type2) n);
        throw new UnsupportedOperationException("visit(" + n.getClass().toString() + ")");
    }
    public void endVisit(Ast n)
    {
        if (n instanceof AstToken) endVisit((AstToken) n);
        else if (n instanceof statementList) endVisit((statementList) n);
        else if (n instanceof terminated_declaration) endVisit((terminated_declaration) n);
        else if (n instanceof terminated_relation) endVisit((terminated_relation) n);
        else if (n instanceof StepExecution) endVisit((StepExecution) n);
        else if (n instanceof StepPrescription) endVisit((StepPrescription) n);
        else if (n instanceof instanceList) endVisit((instanceList) n);
        else if (n instanceof item_declaration) endVisit((item_declaration) n);
        else if (n instanceof item_instance) endVisit((item_instance) n);
        else if (n instanceof item_definition) endVisit((item_definition) n);
        else if (n instanceof PointerType) endVisit((PointerType) n);
        else if (n instanceof tag_declaration) endVisit((tag_declaration) n);
        else if (n instanceof tag_instance) endVisit((tag_instance) n);
        else if (n instanceof tag_definition) endVisit((tag_definition) n);
        else if (n instanceof tag_componentList) endVisit((tag_componentList) n);
        else if (n instanceof tag_type) endVisit((tag_type) n);
        else if (n instanceof tag_component) endVisit((tag_component) n);
        else if (n instanceof aritm_expr) endVisit((aritm_expr) n);
        else if (n instanceof aritm_term) endVisit((aritm_term) n);
        else if (n instanceof aritm_factor) endVisit((aritm_factor) n);
        else if (n instanceof step_declaration) endVisit((step_declaration) n);
        else if (n instanceof step_instance) endVisit((step_instance) n);
        else if (n instanceof step_componentList) endVisit((step_componentList) n);
        else if (n instanceof step_component) endVisit((step_component) n);
        else if (n instanceof t_type) endVisit((t_type) n);
        else if (n instanceof step_instance_affList) endVisit((step_instance_affList) n);
        else if (n instanceof step_instance_aff) endVisit((step_instance_aff) n);
        else if (n instanceof step_affinityList) endVisit((step_affinityList) n);
        else if (n instanceof step_affinity) endVisit((step_affinity) n);
        else if (n instanceof step_instance_environment) endVisit((step_instance_environment) n);
        else if (n instanceof attributeList) endVisit((attributeList) n);
        else if (n instanceof VariableAttribute) endVisit((VariableAttribute) n);
        else if (n instanceof IntegerAttribute) endVisit((IntegerAttribute) n);
        else if (n instanceof StringAttribute) endVisit((StringAttribute) n);
        else if (n instanceof item_type0) endVisit((item_type0) n);
        else if (n instanceof item_type1) endVisit((item_type1) n);
        else if (n instanceof item_type2) endVisit((item_type2) n);
        throw new UnsupportedOperationException("visit(" + n.getClass().toString() + ")");
    }
}

