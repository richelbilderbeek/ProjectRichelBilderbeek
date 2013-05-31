/*
 *  Experiment.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Fri Jun 17 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#include "Experiment.h"
//----------------------------------------------------------------------------------
Experiment::Experiment(const OptionsFile& optionsFile) :
	mOptionsFile(optionsFile)
{
	//How RAII can you get?
}
//----------------------------------------------------------------------------------
void Experiment::execute() const
{
	clock_t timeStart = clock();

	#ifdef NDEBUG
		std::cout << "Starting experiment in NO DEBUG mode" << std::endl;
	#else
		std::cout << "Starting experiment in DEBUG mode" << std::endl;
	#endif
	const unsigned int nSims = mOptionsFile.getNsimFiles();
	std::vector<std::vector<EnumConclusion> > conclusions(nSims);
	std::vector<MeasurementsTable> measurements(nSims);
	std::vector<SimulationFile> simFile(nSims);
	for(unsigned int i=0; i<nSims; ++i)
	{
		std::cout << "\n\nSTARTING SIMULATION "<<i<<"/"<<nSims<<"\n\n";
		simFile[i]=mOptionsFile.getSimFile(i);
		const std::auto_ptr<Simulation> pSimulation(new Simulation(mOptionsFile,simFile[i]));
		pSimulation->execute(measurements[i],conclusions[i]);
	}
	
	for(unsigned int i=0; i<nSims; ++i) 
	{
		std::cout << "\n\nDRAWING CONCLUSIONS "<<i<<"/"<<nSims<<"\n\n";
		drawConclusions(measurements[i],conclusions[i]);
		coutConclusions(conclusions[i]);
	}
	
	//Saving measurements in output file
	if (mOptionsFile.getDoWriteOutputFile()==true) 
	{
		for (unsigned int i=0; i<nSims; ++i)
		{
			const std::string outputFile = mOptionsFile.getOutputFileName(i);
			measurements[i].saveToSingleFile(outputFile);
			measurements[i].saveToMultipleFiles(outputFile);
		}
	}

	clock_t timeEnd = clock();
	std::cout << "Simulation took " << (difftime(timeEnd,timeStart) / CLK_TCK) << " seconds." << std::endl;
	std::cout << "Program ended..." << std::endl;
	
	//Plotting output graphically
	if (mOptionsFile.getDoPlot()==true) plotMeasurementsTable(measurements);

}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

