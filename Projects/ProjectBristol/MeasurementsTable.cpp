/*
 *  MeasurementsTable.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue Jun 07 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#include "MeasurementsTable.h"


//----------------------------------------------------------------------------------
void MeasurementsTable::showYearLegend() const
{
	std::cout << "time" << '\t' 
		<< "PopSize" << '\t' 
		<< "Noffspring" << '\t' 
		<< "Resources" << '\t' 
		<< "MeanBodySize" << '\t' 
		<< "MeanReserves" << '\n';
}
//----------------------------------------------------------------------------------
void MeasurementsTable::showYear(const unsigned int& time) const
{
	std::cout << time << '\t' 
		<< mPopSize[time] << '\t' 
		<< mNoffspring[time] << '\t' 
		<< mResources[time] << '\t' 
		<< mMeanBodySize[time] << '\t' 
		<< mMeanReserves[time] << '\n';
}
//----------------------------------------------------------------------------------
void MeasurementsTable::showYearHorizontal(const unsigned int& time) const
{
	if (mPopSize.size()==0) 
	{ 
		std::cout << "WARNING: Measurement table is shown before any data in it!:" << std::endl; 
		return;
	}
	//assert(time<mPopSize.size());
	assert(time<=mPopSize.size());
	std::cout << "--------------------------------------------" 
		<< "\ntime: "          << time << '\n' 
		<< "PopSize: "         << mPopSize[time] << '\n' 
		<< "Noffspring: "      << mNoffspring[time] << '\n' 
		<< "Resources: "       << mResources[time] << '\n' 
		<< "MeanBodySize: "    << mMeanBodySize[time] << '\n' 
		<< "MeanReserves: "    << mMeanReserves[time] << '\n'
		<< "MeanChanceToDie: " << mMeanChanceToDie[time] << '\n'
		<< "MeanFoodIntake: "  << mMeanFoodIntake[time] << '\n' 
		<< "mMeanAllocation: "   << mMeanAllocation[time] << '\n'
		<< "mMeanFractionBiomassPerOffspringInitial: " << mMeanFractionBiomassPerOffspringInitial[time] << '\n'
		<< "mMeanFractionBiomassPerOffspring: " << mMeanFractionBiomassPerOffspring[time] << '\n';
		
}
//----------------------------------------------------------------------------------
void MeasurementsTable::saveToSingleFile(const std::string& fileName) const
{
	std::ofstream file(fileName.c_str());
	//std::cout << "Saving measurements as file '" << fileName << "'.\n";
	//std::cout << "Progress:\n";
	//std::cout << "------------------------\n";
	addVectorToFile("Population size", mPopSize,file);
	std::cout << ".";
	addVectorToFile("Amount of offspring",  mNoffspring,file);
	std::cout << ".";
	addVectorToFile("Resources",   mResources,file);
	std::cout << ".";
	addVectorToFile("Mean body size",mMeanBodySize,file);
	std::cout << ".";
	addVectorToFile("StdDev body size",mStdDevBodySize,file);
	std::cout << ".";
	addVectorToFile("Means reserves",mMeanReserves,file);
	std::cout << ".";
	addVectorToFile("Stddev reserves",mStdDevReserves,file);
	std::cout << ".";
	addVectorToFile("Mean chance to die",mMeanChanceToDie,file);
	std::cout << ".";
	addVectorToFile("StdDev chance to die",mStdDevChanceToDie,file);
	std::cout << ".";
	addVectorToFile("Mean food intake",mMeanFoodIntake,file);
	std::cout << ".";
	addVectorToFile("StdDev food intake",mStdDevFoodIntake,file);
	std::cout << ".";
	addVectorToFile("Population size Juveniles",mPopSizeJuvenile,file);
	std::cout << ".";
	addVectorToFile("Population size Adults",mPopSizeAdult,file);
	std::cout << ".";
	addVectorToFile("Mean body size Juveniles",mMeanBodySizeJuvenile,file);
	std::cout << ".";
	addVectorToFile("Mean body size Adults",mMeanBodySizeAdult,file);
	std::cout << ".";
	addVectorToFile("Mean reserves Juveniles",mMeanReservesJuvenile,file);
	std::cout << ".";
	addVectorToFile("Mean reserves Adults",mMeanReservesAdult,file);
	std::cout << ".";
	addVectorToFile("Mean chance to die Juveniles",mMeanChanceToDieJuvenile,file);
	std::cout << ".";
	addVectorToFile("Mean chance to die Adults",mMeanChanceToDieAdult,file);
	std::cout << ".";
	addVectorToFile("Mean food intake Juveniles",mMeanFoodIntakeJuvenile,file);
	std::cout << ".";
	addVectorToFile("Mean food intake Adults",mMeanFoodIntakeAdult,file);
	std::cout << ".";
	addVectorToFile("Mean allocation",mMeanAllocation,file);
	std::cout << ".";
	addVectorToFile("Mean fraction biomass per offspring Initial",mMeanFractionBiomassPerOffspringInitial,file);
	std::cout << ".";
	addVectorToFile("Mean fraction biomass per offspring After rounding off",mMeanFractionBiomassPerOffspring,file);
	std::cout << ".\nSaving done.\n";
	file.close();
}
//----------------------------------------------------------------------------------
void MeasurementsTable::saveToMultipleFiles(const std::string& fileName) const
{
	const std::string baseFileName = stripExtension(fileName); 
	vectorToFile(mPopSize     ,baseFileName+"PopSize.rda");
	vectorToFile(mResources   ,baseFileName+"Resources.rda");
	vectorToFile(mMeanBodySize,baseFileName+"BodySize.rda");
	vectorToFile(mMeanReserves,baseFileName+"Reserves.rda");
	vectorToFile(mMeanFoodIntake,baseFileName+"FoodIntake.rda");
	VectorToFile(mMeanAllocation,baseFileName+"Partition.rda");
	vectorToFile("PopSize", mPopSize, "Resources" , mResources, baseFileName+"PopResScatter.rda");
	vectorToFile("PopSize"       , mPopSize, 
	             "Resources"     , mResources,
				 "MeanBodySize"  , mMeanBodySize,
				 "MeanReserves"  , mMeanReserves,
				 "MeanFoodIntake", mMeanFoodIntake,
                 "MeanPartition" , mMeanAllocation,
				  baseFileName+"Scatter.rda");
	vectorToFile("PopSize"       , mPopSize, 
                 "MeanPartition" , mMeanAllocation,
				  baseFileName+"SubScatter.rda");
	std::cout << ".\nSaving done.\n";
}
//----------------------------------------------------------------------------------
void MeasurementsTable::addVectorToFile(const std::string& name, const std::vector<double>& myVector, std::ofstream& file) const
{
	assert(file.is_open()==true);
	const unsigned int size = myVector.size();
	file << name << '\n';
	file << "Size of vector '" << name << "':" << '\n';
	file << size << '\n';
	file << "Contents of vector '" << name << "':" << '\n';
	for (unsigned int i=0; i<size; ++i)
	{
		file <<  myVector[i] << '\n';
	}
}
//----------------------------------------------------------------------------------//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void plotMeasurementsTable(std::vector<MeasurementsTable>& tables)
{
	std::cout << "Plotting started." << std::endl;
	const unsigned int nTables = tables.size();
	std::string temp;
	Gnuplot myPlot;
	myPlot.setStyle(styleLines);
	usleep(150000); myPlot.changeWindow(0);
	for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mPopSize        ,"PopSize"        +indexToPlasticity(i));
	for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mPopSizeJuvenile,"PopSizeJuvenile"+indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mPopSizeAdult   ,"PopSizeAdult"   +indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mNoffspring     ,"Noffspring"     +indexToPlasticity(i));
	
	usleep(150000); myPlot.changeWindow(1);
	for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mResources,"Resources"+indexToPlasticity(i));
	/*
	usleep(150000); myPlot.changeWindow(2);
	for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanBodySize        ,"Mean body size"        +indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanBodySizeJuvenile,"Mean body sizeJuvenile"+indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanBodySizeAdult   ,"Mean body sizeAdult"   +indexToPlasticity(i));
	usleep(150000); myPlot.changeWindow(3);
	for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanReserves        ,"Mean reserves"        +indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanReservesJuvenile,"Mean reservesJuvenile"+indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanReservesAdult   ,"Mean reservesAdult"   +indexToPlasticity(i));
	usleep(150000); myPlot.changeWindow(4);
	for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanChanceToDie        ,"Mean chance to die"        +indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanChanceToDieJuvenile,"Mean chance to dieJuvenile"+indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanChanceToDieAdult   ,"Mean chance to dieAdult"   +indexToPlasticity(i));
	usleep(150000); myPlot.changeWindow(5);
	for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanFoodIntake,        "Mean food intake"        +indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanFoodIntakeJuvenile,"Mean food intakeJuvenile"+indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanFoodIntakeAdult,   "Mean food intakeAdult"   +indexToPlasticity(i));
	usleep(150000); myPlot.changeWindow(6);
	for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanAllocation,        "Mean allocation"        +indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanFractionBiomassPerOffspringInitial,"Mean fraction biomass per offspring initial"+indexToPlasticity(i));
	//for (unsigned int i = 0; i<nTables; ++i) myPlot.plot(tables[i].mMeanFractionBiomassPerOffspring,"Mean fraction biomass per offspring"+indexToPlasticity(i));
	*/
	usleep(150000); 
	std::cout << "Done plotting." << std::endl;
}
//----------------------------------------------------------------------------------
void drawConclusions(const MeasurementsTable& table,std::vector<EnumConclusion>& conclusions)
{

	double meanPopSize     = -1.0;
	double meanNoffspring  = -1.0;
	double meanBodySize    = -1.0;
	double meanReserves    = -1.0;
	double meanChanceToDie = -1.0;
	double meanFoodIntake  = -1.0;
	double meanAllocation  = -1.0;
	double meanFractionBiomassPerOffspringInitial = -1.0;
	double meanFractionBiomassPerOffspring        = -1.0;
	SafeMean(table.mPopSize,         meanPopSize);
	SafeMean(table.mNoffspring,      meanNoffspring);
	SafeMean(table.mMeanBodySize,    meanBodySize);
	SafeMean(table.mMeanReserves,    meanReserves);
	SafeMean(table.mMeanChanceToDie, meanChanceToDie);
	SafeMean(table.mMeanFoodIntake,  meanFoodIntake);
	SafeMean(table.mMeanAllocation,  meanAllocation);
	SafeMean(table.mMeanFractionBiomassPerOffspringInitial, meanFractionBiomassPerOffspringInitial);
	SafeMean(table.mMeanFractionBiomassPerOffspring, meanFractionBiomassPerOffspring);

	std::cout << "Mean population size: " << meanPopSize << std::endl;
	if (meanPopSize<500.0) conclusions.push_back(CcMeanPopSizeSmall);
	if (meanPopSize>1500.0) conclusions.push_back(CcMeanPopSizeLarge);
	std::cout << "Mean offspring produced: " << meanNoffspring << std::endl;
	std::cout << "Mean body size: " << meanBodySize << std::endl;
	std::cout << "Mean reserves: " << meanReserves << std::endl;
	std::cout << "Mean chance to die: " << meanChanceToDie << std::endl;
	if (meanChanceToDie < 0.001) conclusions.push_back(CcChanceToDieSmall);
	if (meanChanceToDie > 0.1) conclusions.push_back(CcChanceToDieLarge);
	std::cout << "Mean food intake: " << meanFoodIntake << std::endl;

	std::cout << "meanAllocation: " << meanAllocation << std::endl;
	std::cout << "meanFractionBiomassPerOffspringInitial: " << meanFractionBiomassPerOffspringInitial << std::endl;
	if (meanFractionBiomassPerOffspringInitial>0.99) conclusions.push_back(CcFractionBiomassPerOffspringInitialLarge);
	std::cout << "meanFractionBiomassPerOffspring: " << meanFractionBiomassPerOffspring << std::endl;

}
//----------------------------------------------------------------------------------
void interpretMeasurementsTables(const std::vector<MeasurementsTable>& table)
{
	const unsigned int size = table.size();
	std::vector<double> meanPopSize(size);
	std::vector<double> meanNoffspring(size);
	std::vector<double> meanBodySize(size);
	std::vector<double> meanReserves(size);
	std::vector<double> meanChanceToDie(size);
	std::vector<double> meanFoodIntake(size);
	std::vector<double> meanAllocation(size);
	std::vector<double> meanFractionBiomassPerOffspringInitial(size);
	std::vector<double> meanFractionBiomassPerOffspring(size);
	for(unsigned int i=0; i<size; ++i)
	{
		SafeMean(table[i].mPopSize,         meanPopSize[i]);
		SafeMean(table[i].mNoffspring,      meanNoffspring[i]);
		SafeMean(table[i].mMeanBodySize,    meanBodySize[i]);
		SafeMean(table[i].mMeanReserves,    meanReserves[i]);
		SafeMean(table[i].mMeanChanceToDie, meanChanceToDie[i]);
		SafeMean(table[i].mMeanFoodIntake,  meanFoodIntake[i]);
		SafeMean(table[i].mMeanAllocation,  meanAllocation[i]);
		SafeMean(table[i].mMeanFractionBiomassPerOffspringInitial, meanFractionBiomassPerOffspringInitial[i]);
		SafeMean(table[i].mMeanFractionBiomassPerOffspring, meanFractionBiomassPerOffspring[i]);
	}
}
//----------------------------------------------------------------------------------



