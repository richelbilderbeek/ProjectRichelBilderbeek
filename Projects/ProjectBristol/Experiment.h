/*
 *  Experiment.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Fri Jun 17 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

/// Goal of this class is to do all simulations contained in an OptionsFile

#ifndef __EXPERIMENT_H
#define __EXPERIMENT_H

#include <time.h>
#include "OptionsFile.h"
#include "Simulation.h"

class Experiment
{
	public:
	Experiment(const OptionsFile&);
	void execute() const;

	private:
	const OptionsFile mOptionsFile;
};

#endif //#ifndef __EXPERIMENT_H
