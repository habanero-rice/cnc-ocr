
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//

package CnCParser.Ast;

import CnCParser.*;
import lpg.runtime.*;

/**
 *<b>
 *<li>Rule 13:  step_execution ::= instance_list$inputList -> step_instance
 *<li>Rule 14:  step_execution ::= instance_list$inputList -> step_instance -> instance_list$outputList
 *<li>Rule 15:  step_execution ::= step_instance <- instance_list$inputList
 *<li>Rule 16:  step_execution ::= instance_list$outputList <- step_instance
 *<li>Rule 17:  step_execution ::= instance_list$outputList <- step_instance <- instance_list$inputList
 *<li>Rule 18:  step_execution ::= step_instance -> instance_list$outputList
 *</b>
 */
public class StepExecution extends Ast implements Istep_execution
{
    private CncParser environment;
    public CncParser getEnvironment() { return environment; }

    private instanceList _inputList;
    private Istep_instance _step_instance;
    private instanceList _outputList;

    /**
     * The value returned by <b>getinputList</b> may be <b>null</b>
     */
    public instanceList getinputList() { return _inputList; }
    public Istep_instance getstep_instance() { return _step_instance; }
    /**
     * The value returned by <b>getoutputList</b> may be <b>null</b>
     */
    public instanceList getoutputList() { return _outputList; }

    public StepExecution(CncParser environment, IToken leftIToken, IToken rightIToken,
                         instanceList _inputList,
                         Istep_instance _step_instance,
                         instanceList _outputList)
    {
        super(leftIToken, rightIToken);

        this.environment = environment;
        this._inputList = _inputList;
        this._step_instance = _step_instance;
        this._outputList = _outputList;
        initialize();
    }

    public boolean equals(Object o)
    {
        if (o == this) return true;
        if (! (o instanceof StepExecution)) return false;
        if (! super.equals(o)) return false;
        StepExecution other = (StepExecution) o;
        if (_inputList == null)
            if (other._inputList != null) return false;
            else; // continue
        else if (! _inputList.equals(other._inputList)) return false;
        if (! _step_instance.equals(other._step_instance)) return false;
        if (_outputList == null)
            if (other._outputList != null) return false;
            else; // continue
        else if (! _outputList.equals(other._outputList)) return false;
        return true;
    }

    public int hashCode()
    {
        int hash = super.hashCode();
        hash = hash * 31 + (_inputList == null ? 0 : _inputList.hashCode());
        hash = hash * 31 + (_step_instance.hashCode());
        hash = hash * 31 + (_outputList == null ? 0 : _outputList.hashCode());
        return hash;
    }

    public void accept(IAstVisitor v)
    {
        if (! v.preVisit(this)) return;
        enter((Visitor) v);
        v.postVisit(this);
    }

    public void enter(Visitor v)
    {
        boolean checkChildren = v.visit(this);
        if (checkChildren)
        {
            if (_inputList != null) _inputList.accept(v);
            _step_instance.accept(v);
            if (_outputList != null) _outputList.accept(v);
        }
        v.endVisit(this);
    }

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
}


