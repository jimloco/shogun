/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2011 Heiko Strathmann
 * Copyright (C) 2011 Berlin Institute of Technology and Max-Planck-Society
 */

#ifndef __MODELSELECTION_H_
#define __MODELSELECTION_H_

#include <shogun/base/SGObject.h>
#include <shogun/evaluation/MachineEvaluation.h>
#include <shogun/modelselection/ModelSelectionOutput.h>

namespace shogun
{

class CModelSelectionParameters;
class CParameterCombination;

/**
 * @brief Abstract base class for model selection.
 * Takes a parameter tree which specifies parameters for model selection,
 * and a cross-validation instance and searches for the best combination of
 * parameters in the abstract method select_model(), which has to be implemented
 * in concrete sub-classes.
 */
class CModelSelection: public CSGObject
{
public:
	/** constructor
	 * @param model_parameters parameter tree with model parameters to optimize
	 * @param cross_validation cross-validation instance to use for evaluation
	 * of a certain combination of parameters
	 */
	CModelSelection(CModelSelectionParameters* model_parameters,
			CMachineEvaluation* machine_eval);

	/** destructor */
	virtual ~CModelSelection();

	/**
	 * abstract method to select model
	 *
	 * @param print_state if true, the current combination is printed
	 * @return best combination of model parameters
	 */
	virtual CParameterCombination* select_model(bool print_state=false)=0;

	/** set model selection output */
	void set_ms_output(CModelSelectionOutput* ms_output);

private:

	/*Initializer*/
	void init();

protected:
	/** model parameters */
	CModelSelectionParameters* m_model_parameters;
	/** cross validation */
	CMachineEvaluation* m_machine_eval;
	/** output */
	CModelSelectionOutput* m_ms_output;
};

}

#endif /* __MODELSELECTION_H_ */
