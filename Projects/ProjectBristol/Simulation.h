/*
 *  Simulation.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 24 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

///The function of class Simulation is to run a simulation
///
///It is initialized with an OptionsFile and a SimulationFile
///The OptionFiles is used for e.g. display options during the simulation
///The SimulationFile embodies the parameters and functions Simulation uses
///
///Technical notes:
///-Do NOT put std::auto_ptr's in a std::vector, as a std::auto_ptr's copy is not the same as the original (ref. 1)
///-Do NOT use std::auto_ptr for pointing to FunctionsSingleton, as Simulation will NOT have the responsability to delete it.
///
///Reference:
///1) Exceptional C++: 47 Engineering Puzzles, Programming Problems, and Solutions. By Herb Sutter. ISBN: 0-201-61562-2

#ifndef __SIMULATION_H
#define __SIMULATION_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "FunctionsSingleton.h"
#include "SoilMite.h"
#include "Gnuplot.h"
#include "Enumerations.h"
#include "ParameterSets.h"
#include "OptionsFile.h"
#include "SimulationFile.h"
#include "MeasurementsTable.h"

class Simulation
{
	std::vector<SoilMiteBase*> mPop;
	FunctionsSingleton * mpFunctions;
	double mResources; 
	std::vector<double> mVectorResources;
	unsigned int mMaxTime;
	//Measuring
	bool mOffspringProduced;

	//Life stages
	void changeEnvironment(const int&,MeasurementsTable&);
	void intake(MeasurementsTable&);
	void reproduction(MeasurementsTable&);
	void mortality();

	//Helpers
	void initialize(); 
	void measurePopulation(MeasurementsTable&);
	double getSumFeedRate() const;

	void checkPopSize(const std::string&) const;
	void checkResources(const double&) const;
	void cout(const std::string& logMessage) const;
	void dot(const std::string& errorMessage) const;
	EnumErrorCode mErrorCode;
	
	public:
	//Simulation(const std::string&);
	
	Simulation(const OptionsFile&, const SimulationFile&);
	void readParameters(const ParameterSetSimulation&);
	void readOptions(const OptionsFileParameters&);

	const OptionsFileParameters mOptionsFileParameters;
	
	~Simulation();
	void execute(MeasurementsTable&, std::vector<EnumConclusion>&);
};

#endif //#ifndef __SIMULATION_H
//----------------------------------------------------------------------------------

