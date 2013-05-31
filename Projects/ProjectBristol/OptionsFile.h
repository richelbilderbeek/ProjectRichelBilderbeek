/*
 *  OptionsFile.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Thu Jun 16 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

///OptionFile embodies the user options and one or more SimulationFiles.
///
///OptionsFile is used by Experiment, which runs a Simulation for every SimulationFile.
///OptionsFile is used by Simulation, which it e.g. tells to give intermediate output.
///The SimulationFiles are the biological parameters used by a Simulation.

 
#ifndef __OPTIONS_FILE
#define __OPTIONS_FILE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SimulationFile.h"
#include "HelperFunctions.h"

struct OptionsFileParameters
{
	bool doPlot;
	bool doWriteOutputFile;
	bool showYearSummary;
};

class OptionsFile
{
	public:
	OptionsFile(const std::string& fileName = "defaultOptionsFile.txt");
	~OptionsFile();
	void showUser() const;
	void showSimFile(const int&) const;
	
	void addSimFile(const std::string&);
	void removeSimFile(const int&);

	
	//Getters
	std::string getFileName() const      { return mFileName; }
	int getUsesSimFile() const           { return mUsesSimFile; }
	ParameterSetSimulation getParameterSetSimulation() const;
	bool getDoPlot() const               { return mOptionsFileParameters.doPlot; }
	bool getDoWriteOutputFile() const    { return mOptionsFileParameters.doWriteOutputFile; }
	bool getShowYearSummary() const      { return mOptionsFileParameters.showYearSummary; }
	OptionsFileParameters getOptionsFileParameters() const { return mOptionsFileParameters; }

	unsigned int getNsimFiles() const    { return mSimulationFile.size(); }
	std::string getOutputFileName(const unsigned int& index) const { return mSimulationFile[index].getOutputFileName(); }

	std::vector<std::string> getSimulationFileNames() const;
	const SimulationFile& getSimFile(const unsigned int& index) const { assert(index>=0 && index<mSimulationFile.size()); return mSimulationFile[index]; }
	std::string getSimFileName(const unsigned int& index) const { assert(index>=0 && index<mSimulationFile.size()); return mSimulationFile[index].getFileName(); }
	std::vector<SimulationFile> getSimulationFiles() const { return mSimulationFile; }

	//Setters of OptionsFile data
	void setPlotting(const bool&);
	void setWriteOutputFile(const bool&);
	void setShowYearSummary(const bool&);
	void setUsesSimFile(const int&);

	//Setters of SimFile data 
	void setOutputFileName(const std::string&);
	void setSeed(const int&);
	void setSimTime(const int&);
	void setStartPopSize(const unsigned int&);
	void setStartResources(const double&);
	void setBodySizeAdult(const double&);
	void setConstA(const double&);
	void setConstB(const double&);
	void setConstC(const double&);
	void setReproductionMode(const EnumReproductionMode&);

	//----------------------------------------------------------------------------------
	//
	// COMPUTER GENERATED CODE
	// OptionsFile
	//
	//----------------------------------------------------------------------------------
	void setDconstA(const double&);
	void setFconstA(const double&);
	void setGconstA(const double&);
	void setMconstA(const double&);
	void setNconstA(const double&);
	void setPconstA(const double&);
	void setQconstA(const double&);
	void setRconstA(const double&);
	void setWconstA(const double&);
	void setDconstB(const double&);
	void setFconstB(const double&);
	void setGconstB(const double&);
	void setMconstB(const double&);
	void setNconstB(const double&);
	void setPconstB(const double&);
	void setQconstB(const double&);
	void setRconstB(const double&);
	void setWconstB(const double&);
	void setDconstC(const double&);
	void setFconstC(const double&);
	void setGconstC(const double&);
	void setMconstC(const double&);
	void setNconstC(const double&);
	void setPconstC(const double&);
	void setQconstC(const double&);
	void setRconstC(const double&);
	void setWconstC(const double&);
	void setDconstD(const double&);
	void setFconstD(const double&);
	void setGconstD(const double&);
	void setMconstD(const double&);
	void setNconstD(const double&);
	void setPconstD(const double&);
	void setQconstD(const double&);
	void setRconstD(const double&);
	void setWconstD(const double&);
	void setDconstE(const double&);
	void setFconstE(const double&);
	void setGconstE(const double&);
	void setMconstE(const double&);
	void setNconstE(const double&);
	void setPconstE(const double&);
	void setQconstE(const double&);
	void setRconstE(const double&);
	void setWconstE(const double&);
	void setD(const EnumD&);
	void setF(const EnumF&);
	void setG(const EnumG&);
	void setM(const EnumM&);
	void setN(const EnumN&);
	void setP(const EnumP&);
	void setQ(const EnumQ&);
	void setR(const EnumR&);
	void setW(const EnumW&);






	
	private:

	const std::string mFileName;
	std::vector<SimulationFile> mSimulationFile;
	
	//Options
	int  mUsesSimFile; //-1 if 'all'
	OptionsFileParameters mOptionsFileParameters;
	
	//File I/O
	void readFromFile();
	void writeToFile() const;

};

#endif //#ifndef __OPTIONS_FILE


