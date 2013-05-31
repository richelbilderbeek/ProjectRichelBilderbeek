/*
 *  SoilMite.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 24 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */
//----------------------------------------------------------------------------------
#ifndef __SOILMITE_H
#define __SOILMITE_H

#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include "random.h"
#include "FunctionsSingleton.h"
#include "Enumerations.h"
//----------------------------------------------------------------------------------
class SoilMiteBase
{

	public:
	SoilMiteBase();
	virtual ~SoilMiteBase();
	bool doIdie() const;
	void intake(const double&);
	virtual EnumErrorCode reproduce(std::vector<SoilMiteBase*>&) = 0;
	double getFeedRate() const { return mFeedRate; }
	double getBodySize() const { assert(mBodySize>=0.0); return mBodySize; }
	double getReserves() const { return mReserves; }
	double getChanceToDie() const { return mChanceToDie; }
	double getAllocation() const { return mAllocation; }
	virtual double getFractionBiomassPerOffspring() const = 0;
	virtual double getFractionBiomassPerOffspringInitial() const = 0;
	virtual double getNoffspringInitial() const = 0;
	virtual unsigned int getNoffspring() const = 0;

	static void setBodySizeAdult(const double& size) { mBodySizeAdult = size; }
	static int getPopSize() { return sPopSize; }
	static double getBodySizeAdult() { return mBodySizeAdult; }

	protected:
	double mBodySize;
	double mReserves;
	double mFeedRate;
	double mBiomassEggs;
	double mChanceToDie;
	double mAllocation;
	static FunctionsSingleton * mpFunctions;
	static int sPopSize;
	static double mBodySizeAdult;

	void cout(const std::string& logMessage = ".") const;
	void dot(const std::string& errorMessage = ".") const;

};
//----------------------------------------------------------------------------------
class SoilMiteFraction : public SoilMiteBase
{
	public:
	//Constructor for first initialization
	SoilMiteFraction(const std::string& initString) 
	{
		assert(initString=="INIT");
		mFractionBiomassPerOffspringInitial = 1.0;
		mFractionBiomassPerOffspring = 1.0;
		mBodySize = mBodySizeAdult*uniform();
		assert(mBodySizeAdult>=0.0);
		assert(mBodySize>=0.0 && mBodySize<=mBodySizeAdult);
		mReserves = uniform()*10.0; //Just value
		mChanceToDie = mpFunctions->D(mBodySize, mReserves);
		assert(mChanceToDie>=0.0 && mChanceToDie<=1.0);
	}

	SoilMiteFraction(const double& biomassEggs) 
	{
		mFractionBiomassPerOffspringInitial = 1.0;
		mFractionBiomassPerOffspring = 1.0;
		assert(biomassEggs>=0.0);
		mBodySize = 0.0;
		mReserves = biomassEggs;
		mChanceToDie = mpFunctions->D(mBodySize, mReserves);
		assert(mChanceToDie>=0.0 && mChanceToDie<=1.0);
	}
	EnumErrorCode reproduce(std::vector<SoilMiteBase*>&);
	double getFractionBiomassPerOffspring() const { return mFractionBiomassPerOffspring; }
	double getFractionBiomassPerOffspringInitial() const { return mFractionBiomassPerOffspringInitial; }
	double getNoffspringInitial() const 
	{ 
		if (mFractionBiomassPerOffspringInitial==0.0) return 0.0;
		else return 1.0/mFractionBiomassPerOffspringInitial;
	}
	unsigned int getNoffspring() const 
	{ 
		if (mFractionBiomassPerOffspring==0.0) return 0;
		else return static_cast<unsigned int>(1.0/mFractionBiomassPerOffspring);
	}

	private:
	double mFractionBiomassPerOffspring;
	double mFractionBiomassPerOffspringInitial;

};
//----------------------------------------------------------------------------------
class SoilMiteAmount : public SoilMiteBase
{
	public:
	SoilMiteAmount(const std::string& initString) 
	{
		assert(initString=="INIT");
		mBodySize = mBodySizeAdult*uniform();
		assert(mBodySizeAdult>=0.0);
		assert(mBodySize>=0.0 && mBodySize<=mBodySizeAdult);
		mReserves = uniform()*10.0; //Just a number
		mChanceToDie = mpFunctions->D(mBodySize, mReserves);
		assert(mChanceToDie>=0.0 && mChanceToDie<=1.0);
		mNoffspringInitial = 0.0;
		mNoffspring = 0;
	}
	SoilMiteAmount(const double& biomassEggs) 
	{
		assert(biomassEggs>=0.0);
		mBodySize = 0.0;
		mReserves = biomassEggs;
		mChanceToDie = mpFunctions->D(mBodySize, mReserves);
		assert(mChanceToDie>=0.0 && mChanceToDie<=1.0);
		mNoffspringInitial = 0.0;
		mNoffspring = 0;
	}
	
	//The only important one
	EnumErrorCode reproduce(std::vector<SoilMiteBase*>&);
	
	double getFractionBiomassPerOffspring() const 
	{ 
		if (mNoffspringInitial==0.0) return 0.0;
		else return 1.0/mNoffspringInitial; 
	}
	double getFractionBiomassPerOffspringInitial() const 
	{ 
		if (mNoffspring==0) return 0.0;
		else return 1.0/static_cast<double>(mNoffspring);
	}
	double getNoffspringInitial() const { return mNoffspringInitial; }
	unsigned int getNoffspring() const { return mNoffspring; }

	private:
	double mNoffspringInitial;
	unsigned int mNoffspring;
};
//----------------------------------------------------------------------------------
#endif //#ifndef __SOILMITE_DEFAULT_H
//----------------------------------------------------------------------------------

