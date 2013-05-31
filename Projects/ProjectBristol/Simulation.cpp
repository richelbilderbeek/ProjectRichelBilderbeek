/*
 *  Simulation.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 24 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */
//----------------------------------------------------------------------------------
#include "Simulation.h"

//#define EXTREME_LOGGING
//#define EXTREME_LOGGING_PLUS
//----------------------------------------------------------------------------------
Simulation::Simulation(const OptionsFile& optionsFile, const SimulationFile& simulationFile) :
	mpFunctions(FunctionsSingleton::instance()),
	mOptionsFileParameters(optionsFile.getOptionsFileParameters())
{
	simulationFile.coutAll();
	readParameters(simulationFile.getParameters());
	const unsigned int popSize = mPop.size();

	switch (simulationFile.getReproductionMode())
	{
		case enumReproductionModeFraction:
			for (unsigned int i=0; i<popSize; ++i) 
			{
				mPop[i] = new SoilMiteFraction("INIT");
				assert(mPop[i]!=NULL);
			}
			break;
		case enumReproductionModeAmount:
			for (unsigned int i=0; i<popSize; ++i) 
			{
				mPop[i] = new SoilMiteAmount("INIT");
				assert(mPop[i]!=NULL);
			}
			break;
		default: assert(!"Unknown value of: simulationFile.getReproductionMode()");
	}

}
//----------------------------------------------------------------------------------
void Simulation::readParameters(const ParameterSetSimulation& params)
{
	srand(params.seed);
	mResources = params.startingResources;
	mMaxTime = params.maxTime;
	SoilMiteBase::setBodySizeAdult(params.bodySizeAdult);
	mOffspringProduced = false;
	//Make function class ready
	mpFunctions = FunctionsSingleton::instance();
	mpFunctions->setAlpha(params.A);
	mpFunctions->setBeta(params.B);
	mpFunctions->setGamma(params.C);
	mpFunctions->setD(params.enumD, &params.paramsD);
	mpFunctions->setF(params.enumF, &params.paramsF);
	mpFunctions->setG(params.enumG, &params.paramsG);
	mpFunctions->setM(params.enumM, &params.paramsM);
	mpFunctions->setN(params.enumN, &params.paramsN);
	mpFunctions->setP(params.enumP, &params.paramsP);
	mpFunctions->setQ(params.enumQ, &params.paramsQ);
	mpFunctions->setR(params.enumR, &params.paramsR);
	mpFunctions->setW(params.enumW, &params.paramsW);
	mPop.resize(params.startingPopSize);
	#ifndef NDEBUG
	for (unsigned int i = 0; i< params.startingPopSize; ++i)
	{
		assert(mPop[i]==NULL);
	}
	#endif
}
//----------------------------------------------------------------------------------
Simulation::~Simulation()
{
	checkPopSize("Simulation::~Simulation() - #1");

	const int popSize = mPop.size();
	for(int i=0; i<popSize; ++i)
	{
		assert(mPop[i]!=NULL);
		delete mPop[i];	mPop[i]=NULL;
	}
	//The check below will give a false result...
	//This is because it checks whether the std::vector size matches
	//the Soilmites' instances...
	//checkPopSize("Simulation::~Simulation() - If you see me, than everything is good");
	mPop.resize(0);
	checkPopSize("Simulation::~Simulation() - #2");

}
//----------------------------------------------------------------------------------
//std::vector<EnumConclusion> Simulation::execute()
void Simulation::execute(MeasurementsTable& table, std::vector<EnumConclusion>& conclusions)
{

	checkPopSize("void Simulation::execute() - #1");
	std::cout << "Start of simulation, running time (timesteps): " << mMaxTime << std::endl;
	std::cout << "Starting population size: " << SoilMiteBase::getPopSize() << std::endl;

	mErrorCode = EcNoError;
	for(unsigned int time=0; time<mMaxTime && mErrorCode==EcNoError; ++time)
	{
		changeEnvironment(time,table);
		intake(table);
		reproduction(table);
		mortality();
		measurePopulation(table);
		if (mOptionsFileParameters.showYearSummary==true) table.showYearHorizontal(time);
	}

	
	checkPopSize("void Simulation::execute() - #2");
	mpFunctions->coutAll();
	std::cout << "Body size adult: " << SoilMiteBase::getBodySizeAdult() << std::endl; 

	//Some conclusions
	if (mOffspringProduced==false) conclusions.push_back(CcNoOffspringProduced);
	switch(mErrorCode)
	{
		case EcNoError: conclusions.push_back(CcNoError); break;
		case EcPopExtinct: conclusions.push_back(CcPopExtinct); break;
		case EcPopSizeTooBig: conclusions.push_back(CcPopSizeTooBig); break;
		case EcNoffspringTooBigSingleParent: conclusions.push_back(CcNoffspringTooBigSingleParent); break;
		case EcNoffspringTooBigAllParents: conclusions.push_back(CcNoffspringTooBigAllParents); break;
	}

	
}
//----------------------------------------------------------------------------------
void Simulation::changeEnvironment(const int& time,MeasurementsTable& table)
{
	if (mErrorCode!=EcNoError) return;

	dot("Current resources: "+ftoa(mResources));
	const double inflow = mpFunctions->R(mResources,time);
	dot("Inflow: "+ftoa(inflow));
	//Note: Inflow can also be negative
	mResources+=inflow;
	dot("New resources: "+ftoa(mResources));
	checkPopSize("void Simulation::changeEnvironment(const int& time)");
	const unsigned int popSize = SoilMiteBase::getPopSize();
	if (popSize==0) { mErrorCode = EcPopExtinct; return; }
	//Create a vector of bodySizes...
	std::vector<double> popBodySize(popSize);
	for (unsigned int i=0; i<popSize; ++i) popBodySize[i] = mPop[i]->getBodySize();
	mVectorResources = mpFunctions->distributeResources(popBodySize, mResources);
	assert(mVectorResources.size()==popBodySize.size());
	checkResources(mResources);
}
//----------------------------------------------------------------------------------
void Simulation::intake(MeasurementsTable& table)
{
	if (mErrorCode!=EcNoError) return;

	checkPopSize("void Simulation::intake() - #1");
	const unsigned int popSize = SoilMiteBase::getPopSize();
	
	if (popSize==0) 
	{
		std::cout << "Population went extinct" << std::endl;
		mErrorCode = EcPopExtinct;
		return;
	}
	if (popSize>100000) 
	{
		std::cout << "Population went bigger then 100,000" << std::endl;
		mErrorCode = EcPopSizeTooBig;
		return;
	}

	for (unsigned int i=0; i<popSize; ++i)
	{
		mPop[i]->intake(mVectorResources[i]);
	}

	const double foodIntake = getSumFeedRate();
	assert(foodIntake>=-0.001 && foodIntake<=mResources*1.0001);
	dot("Intake: "+ftoa(foodIntake));
	mResources-=foodIntake;
	dot("New resources: "+ftoa(mResources));
	table.mResources.push_back(mResources); //Measure

}
//----------------------------------------------------------------------------------
void Simulation::reproduction(MeasurementsTable& table)
{
	if (mErrorCode!=EcNoError) return;

	checkPopSize("void Simulation::intake() - #1");

	const unsigned int popSize = SoilMiteBase::getPopSize();
	table.mPopSize.push_back(popSize); //Measure mPopSize

	std::vector<SoilMiteBase*> offspring;

	for (unsigned int i=0; i<popSize; ++i)
	{
		EnumErrorCode error = mPop[i]->reproduce(offspring);
		if (error!=EcNoError) 
		{
			//Delete the offspring produced this far
			unsigned int nOffspring = offspring.size();
			for (unsigned int i = 0; i<nOffspring; ++i) { delete offspring[i]; offspring[i]=NULL; }
			offspring.resize(0);
			mErrorCode = error; 
			return; 
		}
	}

	//Put offspring in population
	const unsigned int nOffspring = offspring.size();
	if (nOffspring>0) mOffspringProduced =  true;
	if (nOffspring>100000) 
	{   
		mErrorCode = EcNoffspringTooBigAllParents;	
		for (unsigned int i = 0; i<nOffspring; ++i) { delete offspring[i]; offspring[i]=NULL; }
		return;	
	}

	table.mNoffspring.push_back(nOffspring); //Measuring nOffspring
	for (unsigned int i=0; i<nOffspring; ++i)
	{
		assert(offspring[i]!=NULL);
		mPop.push_back(offspring[i]);
	}

	checkPopSize("void Simulation::intake() - #2");

}
//----------------------------------------------------------------------------------
void Simulation::mortality()
{
	if (mErrorCode!=EcNoError) return;

	checkPopSize("void Simulation::mortality() - #1");

	const unsigned int popSize = SoilMiteBase::getPopSize();
	for (unsigned int i=0; i<popSize; ++i)
	{
		if (mPop[i]->doIdie()==true)
		{
			delete mPop[i]; mPop[i]=NULL;
		}
	}

	//DO NOT: checkPopSize("void Simulation::mortality() - #1.5");
	//This will not be correct, because the std::vector mPop then
	//has individuals deleted, but is not yet shrunk

	//Remove NULLs
	for (unsigned int i=0; i < mPop.size() ; ++i)
	{
		while (mPop[i]==NULL && i<mPop.size())
		{
			mPop[i]=mPop.back();
			mPop.pop_back();
		}
	}

	checkPopSize("void Simulation::mortality() - #2");

}
//----------------------------------------------------------------------------------
double Simulation::getSumFeedRate() const
{
	checkPopSize("double Simulation::getSumFeedRate() const - #1");
	const unsigned int popSize = SoilMiteBase::getPopSize();
	double sumFeedRate = 0.0;
	for (unsigned int i=0; i<popSize; ++i)
	{
		const double feedRate = mPop[i]->getFeedRate();
		assert(feedRate>=0.0);
		sumFeedRate+=feedRate;
		#ifdef EXTREME_LOGGING_PLUS
		dot("FeedRate ["+itoa(i)+"]: "+ftoa(feedRate));
		#endif
	}
	return sumFeedRate;
}
//----------------------------------------------------------------------------------
/// Compares if the population sizes of the vector mPop and the static 
/// SoilMiteBase::mPopSize do match.
void Simulation::checkPopSize(const std::string& location) const
{
	#ifndef NDEBUG
	const int popSizeVector = mPop.size();
	const int popSizeClass = SoilMiteBase::getPopSize();
	if (popSizeVector!=popSizeClass) 
	{
		std::cout << "MEMORY LEAK at location: " << location << std::endl;
		std::cout << "mPop size: " << popSizeVector << std::endl;
		std::cout << "SoilMiteBase::sPopSize: " << popSizeClass << std::endl;
	}
	#endif
}
//----------------------------------------------------------------------------------
void Simulation::checkResources(const double& totalResources) const
{
	#ifndef NDEBUG
	double sumResources = 0.0;
	const unsigned int popSize = mVectorResources.size();
	for (unsigned int i=0; i<popSize; ++i)
	{
		sumResources+=mVectorResources[i];
	}

	if (sumResources < 0.999 * totalResources && sumResources>1.001*totalResources)
	{
		std::cout << "sumResources: " << sumResources
			<< "totalResources: " << totalResources << std::endl;
		assert(!"Resources not correct in vector");
	}
	#endif
}
//----------------------------------------------------------------------------------
void Simulation::measurePopulation(MeasurementsTable& table)
{
	if (mErrorCode!=EcNoError) return;

	checkPopSize("void Simulation::measurePopulation()");
	const unsigned int popSize = SoilMiteBase::getPopSize();

	std::vector<double> bodySizeTable(popSize);
	std::vector<double> reservesTable(popSize);
	std::vector<double> chanceToDieTable(popSize);
	std::vector<double> foodIntakeTable(popSize);
	std::vector<double> allocationTable(popSize);
	std::vector<double> fractionBiomassPerOffspringInitialTable(popSize);
	std::vector<double> fractionBiomassPerOffspringTable(popSize);

	std::vector<bool> isAdultTable(popSize);
	const double splitValue = SoilMiteBase::getBodySizeAdult();

	for (unsigned int i=0; i<popSize; ++i)
	{
		bodySizeTable[i]    = mPop[i]->getBodySize();
		reservesTable[i]    = mPop[i]->getReserves();
		foodIntakeTable[i]  = mPop[i]->getFeedRate();
		chanceToDieTable[i] = mPop[i]->getChanceToDie();
		allocationTable[i]  = mPop[i]->getAllocation();
		fractionBiomassPerOffspringInitialTable[i] = mPop[i]->getFractionBiomassPerOffspringInitial();
		fractionBiomassPerOffspringTable[i] = mPop[i]->getFractionBiomassPerOffspring();
		isAdultTable[i]     = ( bodySizeTable[i]>splitValue ? true : false);

		assert(allocationTable[i]>=0.0 && allocationTable[i]<=1.0);
		assert(fractionBiomassPerOffspringInitialTable[i]>=0.0 && fractionBiomassPerOffspringInitialTable[i]<=1.0);
		assert(fractionBiomassPerOffspringTable[i]>=0.0 && fractionBiomassPerOffspringTable[i]<=1.0);
		assert(mPop[i]->getChanceToDie()>=0.0 && mPop[i]->getChanceToDie()<=1.0);
	}

	double meanBodySize, stdDevBodySize;
	SafeMeanAndStdDev(bodySizeTable, meanBodySize, stdDevBodySize);
	table.mMeanBodySize.push_back(meanBodySize);
	table.mStdDevBodySize.push_back(stdDevBodySize);

	double meanReserves, stdDevReserves;
	SafeMeanAndStdDev(reservesTable, meanReserves, stdDevReserves);
	table.mMeanReserves.push_back(meanReserves);
	table.mStdDevReserves.push_back(stdDevReserves);

	double meanFoodIntake, stdDevFoodIntake;
	SafeMeanAndStdDev(foodIntakeTable, meanFoodIntake, stdDevFoodIntake);
	table.mMeanFoodIntake.push_back(meanFoodIntake);
	table.mStdDevFoodIntake.push_back(stdDevFoodIntake);
	
	double meanChanceToDie, stdDevChanceToDie;
	SafeMeanAndStdDev(chanceToDieTable, meanChanceToDie, stdDevChanceToDie);
	table.mMeanChanceToDie.push_back(meanChanceToDie);
	table.mStdDevChanceToDie.push_back(stdDevChanceToDie);

	//Plus
	int popSizeJuvenileInt, popSizeAdultInt;
	countSplit(splitValue, bodySizeTable, popSizeJuvenileInt, popSizeAdultInt);
	double popSizeJuvenile = static_cast<double>(popSizeJuvenileInt);
	double popSizeAdult    = static_cast<double>(popSizeAdultInt);
	table.mPopSizeJuvenile.push_back(popSizeJuvenile);
	table.mPopSizeAdult.push_back(popSizeAdult);
	
	double meanBodySizeJuvenile, meanBodySizeAdult;
	SafeMeanSplit(splitValue,bodySizeTable, meanBodySizeJuvenile, meanBodySizeAdult);
	assert(meanBodySizeJuvenile<=splitValue);
	assert(meanBodySizeAdult>=splitValue || meanBodySizeAdult==0.0);
	table.mMeanBodySizeJuvenile.push_back(meanBodySizeJuvenile);
	table.mMeanBodySizeAdult.push_back(meanBodySizeAdult);
	
	double meanReservesJuvenile, meanReservesAdult;
	SafeMeanSplit(isAdultTable,reservesTable, meanReservesJuvenile, meanReservesAdult);
	table.mMeanReservesJuvenile.push_back(meanReservesJuvenile);
	table.mMeanReservesAdult.push_back(meanReservesAdult);
	
	double meanChanceToDieJuvenile, meanChanceToDieAdult;
	SafeMeanSplit(isAdultTable,chanceToDieTable, meanChanceToDieJuvenile, meanChanceToDieAdult);
	table.mMeanChanceToDieJuvenile.push_back(meanChanceToDieJuvenile);
	table.mMeanChanceToDieAdult.push_back(meanChanceToDieAdult);
	
	double meanFoodIntakeJuvenile, meanFoodIntakeAdult;
	SafeMeanSplit(isAdultTable,foodIntakeTable, meanFoodIntakeJuvenile, meanFoodIntakeAdult);
	table.mMeanFoodIntakeJuvenile.push_back(meanFoodIntakeJuvenile);
	table.mMeanFoodIntakeAdult.push_back(meanFoodIntakeAdult);

	//Plus plus
	double meanAllocationJuvenile, meanAllocationAdult;
	SafeMeanSplit(isAdultTable,allocationTable, meanAllocationJuvenile, meanAllocationAdult);
	table.mMeanAllocation.push_back(meanAllocationAdult);

	double meanFractionBiomassPerOffspringInitialJuvenile, meanFractionBiomassPerOffspringInitialAdult;
	SafeMeanSplit(isAdultTable,fractionBiomassPerOffspringInitialTable, meanFractionBiomassPerOffspringInitialJuvenile, meanFractionBiomassPerOffspringInitialAdult);
	table.mMeanFractionBiomassPerOffspringInitial.push_back(meanFractionBiomassPerOffspringInitialAdult);

	double meanFractionBiomassPerOffspringJuvenile, meanFractionBiomassPerOffspringAdult;
	SafeMeanSplit(isAdultTable,fractionBiomassPerOffspringTable, meanFractionBiomassPerOffspringJuvenile, meanFractionBiomassPerOffspringAdult);
	table.mMeanFractionBiomassPerOffspring.push_back(meanFractionBiomassPerOffspringAdult);
}
//----------------------------------------------------------------------------------
void Simulation::cout(const std::string& logMessage) const
{
	std::cout << "LOG: " << logMessage << std::endl;
}
//----------------------------------------------------------------------------------
void Simulation::dot(const std::string& errorMessage) const
{
	#ifdef EXTREME_LOGGING
	std::cout << "DOT: " << errorMessage << std::endl;
	#endif
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

