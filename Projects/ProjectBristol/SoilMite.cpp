/*
 *  SoilMiteBase.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 24 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */
//----------------------------------------------------------------------------------
#include "SoilMite.h"
//#define EXTREME_LOGGING
//----------------------------------------------------------------------------------
int                  SoilMiteBase::sPopSize       = 0;
double               SoilMiteBase::mBodySizeAdult = -1.0;
FunctionsSingleton * SoilMiteBase::mpFunctions    = FunctionsSingleton::instance();
//----------------------------------------------------------------------------------
SoilMiteBase::SoilMiteBase()
{
	mBodySize = 0.0;
	mFeedRate = 0.0;
	mAllocation = 0.0;
	mBiomassEggs = 0.0;
	sPopSize++;
}
//----------------------------------------------------------------------------------
SoilMiteBase::~SoilMiteBase()
{
	sPopSize--;
	if (sPopSize<0) assert(!"Population size BELOW zero!!!");

}
//----------------------------------------------------------------------------------
bool SoilMiteBase::doIdie() const
{
	assert(mpFunctions!=NULL);
	assert(mChanceToDie>=0.0 && mChanceToDie<=1.0);
	const double randomNumber = uniform();
	assert(randomNumber>=0.0 && randomNumber<=1.0);
	if (mChanceToDie>randomNumber) return true;
	else return false;
}
//----------------------------------------------------------------------------------
void SoilMiteBase::intake(const double& resources)
{
	assert(mpFunctions!=NULL);
	//Let the mite have its meal
	mFeedRate = mpFunctions->F(resources,mBodySize);
	assert(mFeedRate<=resources);
	assert(mFeedRate>=0.0);
	assert(mReserves>=0.0);
	//change its body size and reserves
	mAllocation = mpFunctions->P(mFeedRate, mReserves);
	assert(mAllocation>=0.0 && mAllocation<=1.0);
	const double metabolism = mpFunctions->M(mBodySize, mReserves);
	assert(metabolism>=0.0);
	//Determine the amount of biomass invested in eggs
	mBiomassEggs = (mBodySize < mBodySizeAdult  ? 0.0 : mpFunctions->Q(mReserves));
	assert(mpFunctions->Q(mReserves)>=0.0 && mpFunctions->Q(mReserves)<=mReserves);
	//Change body
	const double alpha = mpFunctions->getAlpha();
	const double beta  = mpFunctions->getBeta();
	const double gamma = mpFunctions->getGamma();
	assert(alpha>0.0);
	assert(beta >0.0);
	//assert(gamma>0.0 && gamma<=1.0);
	
	mBodySize+=alpha*mAllocation*mFeedRate;
	mReserves+=(beta*(1.0-mAllocation)*mFeedRate) - metabolism - (gamma*mBiomassEggs);
	//assert(mReserves>=0.0);
	if (mReserves<0)
	{
		mChanceToDie = 1.0;
	}
	else
	{
		mChanceToDie = mpFunctions->D(mBodySize,mReserves);
	}
	assert(mChanceToDie>=0.0 && mChanceToDie<=1.0);
}
//----------------------------------------------------------------------------------
void SoilMiteBase::cout(const std::string& logMessage) const
{
	std::cout << "LOG: " << logMessage << std::endl;
}
//----------------------------------------------------------------------------------
void SoilMiteBase::dot(const std::string& errorMessage) const
{
	#ifdef EXTREME_LOGGING
	std::cout << "DOT: " << errorMessage << std::endl;
	#endif
}
//----------------------------------------------------------------------------------



//----------------------------------------------------------------------------------
//
// VIRTUAL FUNCTIONS OF DERIVED CLASSES
//
//----------------------------------------------------------------------------------
EnumErrorCode SoilMiteFraction::reproduce(std::vector<SoilMiteBase*>& offspring)
{
	if (mBiomassEggs==0.0) return EcNoError;
	

	assert(mpFunctions!=NULL);

	dot("BiomassEggs: " + ftoa(mBiomassEggs));

	mFractionBiomassPerOffspringInitial = mpFunctions->G(mFeedRate, mReserves);
	dot("Fraction Biomass Per Offspring (Initial):" + ftoa(mFractionBiomassPerOffspringInitial));
	assert(mFractionBiomassPerOffspringInitial>0.0 && mFractionBiomassPerOffspringInitial <=1.0);
	const double nOffspringDinitial = 1.0/mFractionBiomassPerOffspringInitial;
	const int nOffspring = static_cast<int>(round(nOffspringDinitial));

	dot("nOffspringDinitial: " + ftoa(nOffspringDinitial));

	assert(static_cast<int>(round(1.4))==1); assert(static_cast<int>(round(1.6))==2);
	const double nOffspringD = static_cast<double>(nOffspring);
	mFractionBiomassPerOffspring = (1.0/nOffspringD);
	const double biomassPerOffspring = mFractionBiomassPerOffspring*mBiomassEggs;

	dot("nOffspring (final): " + ftoa(nOffspring));

	if (nOffspring>100000) 
	{
		std::cout << "More then 100000 offspring were created. Terminating simulation." << std::endl;
		//Clean offspring vector
		unsigned int nOffspring = offspring.size();
		for (unsigned int i = 0; i<nOffspring; ++i) { delete offspring[i]; offspring[i]=NULL; }
		offspring.resize(0);
		return EcNoffspringTooBigSingleParent; 
	}

	for (int i=0; i<nOffspring; ++i)
	{
		SoilMiteBase * pOffspring = new SoilMiteFraction(biomassPerOffspring);
		assert(pOffspring!=NULL);
		offspring.push_back(pOffspring);
	}
	
	return EcNoError;
}
//----------------------------------------------------------------------------------
EnumErrorCode SoilMiteAmount::reproduce(std::vector<SoilMiteBase*>& offspring)
{
	if (mBiomassEggs==0.0) return EcNoError;
	assert(mpFunctions!=NULL);

	const double nOffspringInitial = mpFunctions->N(mFeedRate, mReserves);
	const int nOffspring = static_cast<int>(round(nOffspringInitial));
	if (nOffspring==0) return EcNoError;

	const double biomassPerOffspring = mBiomassEggs / static_cast<double>(nOffspring);

	if (nOffspring>100000) 
	{ 
		std::cout << "More then 100000 offspring were created. Terminating simulation." << std::endl;
		//Clean offspring vector
		unsigned int nOffspring = offspring.size();
		for (unsigned int i = 0; i<nOffspring; ++i) { delete offspring[i]; offspring[i]=NULL; }
		offspring.resize(0);
		return EcNoffspringTooBigSingleParent; 
	}

	for (int i=0; i<nOffspring; ++i)
	{
		SoilMiteBase * pOffspring = new SoilMiteAmount(biomassPerOffspring);
		assert(pOffspring!=NULL);
		offspring.push_back(pOffspring);
	}
	
	return EcNoError;
}
//----------------------------------------------------------------------------------



