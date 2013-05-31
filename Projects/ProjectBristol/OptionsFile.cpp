/*
 *  OptionsFile.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Thu Jun 16 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#include "OptionsFile.h"
//----------------------------------------------------------------------------------
OptionsFile::OptionsFile(const std::string& fileName) :
	mFileName(fileName),
	mUsesSimFile(0)
	
{
	if (fileExists(mFileName)==true)
	{
		readFromFile();
		return;
	}
	//File does not exist, fill with default values and write
	//
	mOptionsFileParameters.doPlot = false;
	mOptionsFileParameters.doWriteOutputFile = true;
	mOptionsFileParameters.showYearSummary = false;
	
	SimulationFile defaultSimFile;
	mSimulationFile.push_back(defaultSimFile);
	//mSimulationFile.push_back(SimulationFile());

	writeToFile();
}
//----------------------------------------------------------------------------------
OptionsFile::~OptionsFile()
{
	writeToFile();
}
//----------------------------------------------------------------------------------
void OptionsFile::readFromFile()
{
	std::ifstream fileInput(mFileName.c_str());
	assert(fileInput.is_open()==true);
	unsigned int nSimulationFiles;	
	std::vector<std::string> simulationFileName;
	
	fileInput 
		>> mUsesSimFile
		>> mOptionsFileParameters.doPlot
		>> mOptionsFileParameters.doWriteOutputFile
		>> mOptionsFileParameters.showYearSummary
		>> nSimulationFiles
		;
	
	simulationFileName.resize(nSimulationFiles);
	for (unsigned int i=0; i<nSimulationFiles; ++i)
	{
		fileInput >> simulationFileName[i];
	}
	
	mSimulationFile.clear();
	for (unsigned int i=0; i<nSimulationFiles; ++i)
	{
		SimulationFile temp(simulationFileName[i]);
		mSimulationFile.push_back(temp);
	}
	assert(mSimulationFile.size()==nSimulationFiles);
	fileInput.close();
}
//----------------------------------------------------------------------------------
///Writes all members to disk. Does NOT do so for SimFile's.
void OptionsFile::writeToFile() const
{
	std::ofstream fileOutput(mFileName.c_str());
	assert(fileOutput.is_open()==true);
	const unsigned int nSimulationFiles = mSimulationFile.size();	
	std::vector<std::string> simulationFileName;
	
	fileOutput
		<< mUsesSimFile << '\n'
		<< mOptionsFileParameters.doPlot << '\n'
		<< mOptionsFileParameters.doWriteOutputFile << '\n'
		<< mOptionsFileParameters.showYearSummary << '\n'
		<< nSimulationFiles << '\n'
		;
		
	simulationFileName.resize(nSimulationFiles);
	for (unsigned int i=0; i<nSimulationFiles; ++i)
	{
		fileOutput << mSimulationFile[i].getFileName() << '\n';
	}

	fileOutput.close();
}
//----------------------------------------------------------------------------------
std::vector<std::string> OptionsFile::getSimulationFileNames() const
{
	const unsigned int nFileNames = mSimulationFile.size();
	std::vector<std::string> simulationFileName(nFileNames);
	for (unsigned int i=0; i<nFileNames; ++i)
	{
		simulationFileName[i] = mSimulationFile[i].getFileName();
	}
	if (nFileNames==0) simulationFileName.push_back("< None >");
	return simulationFileName;
}
//----------------------------------------------------------------------------------
void OptionsFile::showUser() const
{
	std::cout 
		<< "\n\tShowing Option File '" << mFileName << "':"
		<< "\n\t"
		<< "\n\tUsing Simulation File: " << (mUsesSimFile==-1 ? "all." : "#"+itoa(mUsesSimFile)+".")
		<< "\n\tPlot results at end of simulation: " << (mOptionsFileParameters.doPlot ? "yes." : "no.")
		<< "\n\tShow year summary: " << (mOptionsFileParameters.showYearSummary ? "yes." : "no." )
		<< "\n\tWrite results to file at end of simulation: " << (mOptionsFileParameters.doWriteOutputFile ? "yes." : "no.")
		<< std::endl;

	std::vector<std::string> simFileName = getSimulationFileNames();
	const unsigned int nSimFileNames = simFileName.size();
	for (unsigned int i=0; i<nSimFileNames; ++i)
	{
		std::cout << "\tSimulation file #" << i << ": " << simFileName[i] << std::endl;
	}
	std::cout << std::endl;
}
//----------------------------------------------------------------------------------
///Shows the SimFile with index 'index' (brilliant naming).
///Index -1 denotes to show all SimFiles.
void OptionsFile::showSimFile(const int& index) const
{
	assert(index>=-1 && index<static_cast<int>(mSimulationFile.size()));
	if (index!=-1) 
	{
		mSimulationFile[index].showUser();
	}
	else
	{
		const unsigned int nSimFiles = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFiles; ++i) mSimulationFile[i].showUser();
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::addSimFile(const std::string& fileName)
{
	mSimulationFile.push_back(SimulationFile(fileName));
	writeToFile();
}
//----------------------------------------------------------------------------------
///Removess the SimFile with index 'index' (brilliant naming).
///Index -1 denotes to show all SimFiles.
void OptionsFile::removeSimFile(const int& index)
{
	assert(index>=-1 && index<static_cast<int>(mSimulationFile.size()));
	if (index!=-1) 
	{
		std::cout << "\n\tRemoving Simulation File '" << mSimulationFile.at(index).getFileName()
			<< "' from Options File.\n\n";
		mSimulationFile.erase(mSimulationFile.begin()+index);
	}
	else
	{
		std::cout << "\n\tRemoving all Simulation Files from Options File.\n\n";
		mSimulationFile.resize(0);
	}
	writeToFile();
}
//----------------------------------------------------------------------------------
void OptionsFile::setPlotting(const bool& doPlot)
{
	mOptionsFileParameters.doPlot = doPlot;
	std::cout 
		<< "\n\tTurned plotting " 
		<< (mOptionsFileParameters.doPlot == true ? "on" : "off")
		<< ".\n\n";
	writeToFile();
}
//----------------------------------------------------------------------------------
void OptionsFile::setWriteOutputFile(const bool& doWriteOutputFile)
{
	mOptionsFileParameters.doWriteOutputFile = doWriteOutputFile;
	std::cout 
		<< "\n\tTurned writing to output file " 
		<< (mOptionsFileParameters.doWriteOutputFile == true ? "on" : "off")
		<< ".\n\n";
	writeToFile();
}
//----------------------------------------------------------------------------------
void OptionsFile::setShowYearSummary(const bool& showYearSummary)
{
	mOptionsFileParameters.showYearSummary = showYearSummary;
	std::cout 
		<< "\n\tTurned showing a year summary " 
		<< (mOptionsFileParameters.showYearSummary == true ? "on" : "off")
		<< ".\n\n";
	writeToFile();
}
//----------------------------------------------------------------------------------
void OptionsFile::setUsesSimFile(const int& index)
{
	if (index==-1)
	{   //'all'
		mUsesSimFile = index;
		std::cout << "\n\tSet files in focus to 'all'.\n\n";
	}
	else if (index > -1 && index < static_cast<int>(mSimulationFile.size()))
	{   //Valid index
		mUsesSimFile = index;
		std::cout << "\n\tSet files in focus to '" << mUsesSimFile << "'.\n\n";
	}
	else
	{   //Invalid index
		std::cout 
			<< "\n\tIndex '" << index << "' is out of range."
			<< "\n\tPlease give an index from 0 to (not including)" << mSimulationFile.size()
			<< "\n"
			<< std::endl;
		return;
	}
	
	writeToFile();
}
//----------------------------------------------------------------------------------
void OptionsFile::setOutputFileName(const std::string& fileName)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		const unsigned int nSimFile = mSimulationFile.size();
		const std::string fileNameNoExt = stripExtension(fileName);
		const std::string fileNameExt = getExtension(fileName);
		assert(stripExtension("test.txt")=="test");
		assert(getExtension("test.txt")=="txt");
		
		std::cout << "\n\tSetting 'simulation output file' of all Simulation Files." ;
		for (unsigned int i=0; i<nSimFile; ++i) 
		{
			const std::string newFileName = fileNameNoExt + itoa(i) + "." + fileNameExt;
			std::cout << "\n\t    Setting 'simulation output file' of simulation file #"
				<< i << " to " << newFileName;
			mSimulationFile[i].setOutputFileName(newFileName);
		}
		std::cout << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setOutputFileName(fileName);
		std::cout << "\n\tSet 'simulation output file' of Simulation File #" << mUsesSimFile << " to " << fileName << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setSeed(const int& seed)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's seed to 'seed'
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setSeed(seed);
		std::cout << "\n\tSet 'seed' of all Simulation Files to " << seed << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setSeed(seed);
		std::cout << "\n\tSet 'seed' of Simulation File #" << mUsesSimFile << " to " << seed << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setSimTime(const int& simTime)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setMaxTime(simTime);
		std::cout << "\n\tSet 'simulation running time' of all Simulation Files to " << simTime << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setMaxTime(simTime);
		std::cout << "\n\tSet 'simulation running time' of Simulation File #" << mUsesSimFile << " to " << simTime << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setStartPopSize(const unsigned int& popSize)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setStartPopSize(popSize);
		std::cout << "\n\tSet 'starting population size' of all Simulation Files to " << popSize << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setStartPopSize(popSize);
		std::cout << "\n\tSet 'starting population size' of Simulation File #" << mUsesSimFile << " to " << popSize << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setStartResources(const double& resources)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setStartResources(resources);
		std::cout << "\n\tSet 'starting resources' of all Simulation Files to " << resources << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setStartResources(resources);
		std::cout << "\n\tSet 'starting resources' of Simulation File #" << mUsesSimFile << " to " << resources << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setBodySizeAdult(const double& bodySize)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setBodySizeAdult(bodySize);
		std::cout << "\n\tSet 'body size of adult' of all Simulation Files to " << bodySize << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setBodySizeAdult(bodySize);
		std::cout << "\n\tSet 'body size of adult' of Simulation File #" << mUsesSimFile << " to " << bodySize << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setConstA(const double& constA)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setConstA(constA);
		std::cout << "\n\tSet 'constant A' of all Simulation Files to " << constA << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setConstA(constA);
		std::cout << "\n\tSet SimFile time of Simulation File #" << mUsesSimFile << " to " << constA << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setConstB(const double& constB)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setConstB(constB);
		std::cout << "\n\tSet 'constant B' of all Simulation Files to " << constB << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setConstB(constB);
		std::cout << "\n\tSet 'constant B' of Simulation File #" << mUsesSimFile << " to " << constB << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setConstC(const double& constC)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setConstC(constC);
		std::cout << "\n\tSet 'constant A' of all Simulation Files to " << constC << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setConstC(constC);
		std::cout << "\n\tSet SimFile time of Simulation File #" << mUsesSimFile << " to " << constC << "\n\n";
	}
}
//----------------------------------------------------------------------------------
void OptionsFile::setReproductionMode(const EnumReproductionMode& enumReproductionMode)
{
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1)
	{   //Set all SimFile's time to 'simTime'
		//std::for_each(mSimulationFile.begin(),mSimulationFile.end(), std::mem_fun(&SimulationFile::setReproductionMode(enumReproductionMode));
		const unsigned int nSimFile = mSimulationFile.size();
		for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setReproductionMode(enumReproductionMode);
		std::cout << "\n\tSet 'reproduction mode' of all Simulation Files to " 
			<< enumReproductionModeToString(enumReproductionMode) << "\n\n";
	}
	else
	{
		mSimulationFile[mUsesSimFile].setReproductionMode(enumReproductionMode);
		std::cout << "\n\tSet SimFile time of Simulation File #" << mUsesSimFile 
			<< " to " << enumReproductionModeToString(enumReproductionMode) << "\n\n";
	}
}
//----------------------------------------------------------------------------------
ParameterSetSimulation OptionsFile::getParameterSetSimulation() const
{
	assert(mSimulationFile.size()>0);
	assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));
	
	if (mUsesSimFile==-1) return mSimulationFile[0].getParameterSetSimulation();
	else return mSimulationFile[mUsesSimFile].getParameterSetSimulation();
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------



















































