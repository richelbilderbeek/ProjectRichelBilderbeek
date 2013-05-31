/*
 *  SimulationFile.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Thu Jun 16 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

///Class SimulationFile manages a single Simulation's parameters.
///It is closely linked with file I/O: if you set a value of the
///parameter, this is always saved to disk immediatly.
///Getting the values has not file I/O side-effects. 

#ifndef __SIMULATIONFILE_H
#define __SIMULATIONFILE_H

#include <memory>
#include <string>
#include <fstream>
#include "ParameterSets.h"
#include "Enumerations.h"
#include "HelperFunctions.h"



class SimulationFile
{
	private:
	ParameterSetSimulation mParameters;

	std::string mFileName;
	std::string mVersionName1;
	std::string mVersionName2;
	std::string mCurrentVersionName;

	std::string enumDstring, enumFstring, enumGstring, enumMstring, enumNstring;
	std::string enumPstring, enumQstring, enumRstring, enumWstring;
	std::string enumReproductionModeString;
	
	//Different file readers
	void readFromFile0();
	void readFromFile1();
	void readFromFile2();

	//Converters
	void stringsToEnums();
	void enumsToStrings();	

	//Debugging
	int mFlag;
	void cout(const std::string& logMessage = ".") const;
	void dot(const std::string& errorMessage = ".") const;

	public:
	SimulationFile(const std::string& fileName = "defaultSimFile.txt", const bool& overWrite = false);
	void showUser() const;

	//Setters, formula's
	void setD(const EnumD&);
	void setF(const EnumF&);
	void setG(const EnumG&);
	void setM(const EnumM&);
	void setN(const EnumN&);
	void setP(const EnumP&);
	void setQ(const EnumQ&);
	void setR(const EnumR&);
	void setW(const EnumW&);
	//Setters, parameters of functions
	void setDparams(const ParameterSetD&);
	void setFparams(const ParameterSetF&);
	void setGparams(const ParameterSetG&);
	void setMparams(const ParameterSetM&);
	void setNparams(const ParameterSetN&);
	void setPparams(const ParameterSetP&);
	void setQparams(const ParameterSetQ&);
	void setRparams(const ParameterSetR&);
	void setWParams(const ParameterSetW&);
	//Setters, other parameters
	void setOutputFileName(const std::string&);
	void setSeed(const unsigned int&);
	void setMaxTime(const unsigned int&); 
	void setStartPopSize(const unsigned int&);
	void setStartResources(const double&);
	void setBodySizeAdult(const double&);
	void setConstA(const double&);
	void setConstB(const double&);
	void setConstC(const double&);
	void setReproductionMode(const EnumReproductionMode &);

	//----------------------------------------------------------------------------------
	//
	// COMPUTER GENERATED CODE
	// SimulationFile
	//
	//----------------------------------------------------------------------------------
	//  COMPUTER GENERATED CODE
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


	//Setter, debug
	void setFlag(const int&);

	//Getters
	ParameterSetSimulation getParameterSetSimulation() const { return mParameters; }
	ParameterSetSimulation getParameters() const { return mParameters; }
	EnumReproductionMode getReproductionMode() const { return mParameters.reproductionMode; }
	std::string getFileName() const { return mFileName; }
	std::string getOutputFileName() const { return mParameters.outputFileName; }
	int getFlag() const { return mFlag; }

	//File I/O
	void writeToFile();
	void readFromFile();	
	
	void coutAll() const;	
};



#endif //#ifndef __SIMULATIONFILE_H



