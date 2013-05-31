/*
 *  StrategyW.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Wed Jun 01 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */
 
///Strategy W denotes the hunting success.
///Hunting success is dependent on size.
///This class needs as input a population size and a total amount of resources.
///The population size is extracted from a vector given by reference as input, with size equal to popSize.

///StrategyWzero = everybody gets equal share
///StrategyWuniform = uniform deviation from equal share, size independent
///StrategyWsizeDependent = uniform deviation from size-dependent hunting success

///01-08-2005: Changed:
///eval(size) returns r_i (==w_i)
///after every individual has its r_i calculated (==maximal amount of resources possible to eat),
///it has to be checked if SUM(r_i) is smaller or equal then the total amunt of resources, as the
///derived class StrategyWsizeDependent does NOT scale nicely.

#ifndef __STRATEGY_W_H
#define __STRATEGY_W_H

#include <memory>
#include <vector>
#include <assert.h>
#include "ParameterSets.h"
#include "random.h"
#include "HelperFunctions.h"

//----------------------------------------------------------------------------------
class StrategyWbase
{
	public:
	StrategyWbase() 
	{
		mpParams.reset(new ParameterSetW);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyWbase() {}
	//virtual void distributeResources(const double&, std::vector<double>&) = 0;
	virtual double eval(const double&, const double&) const = 0;
	virtual std::string getString() const = 0;
	virtual void testMe() const = 0;
	void testMe(const std::string& filename) const
	{
		std::ofstream fileOutput(filename.c_str());
		assert(fileOutput.is_open()==true);
		
		for (double size = 0.0; size<10.0; size+=0.1)
		{
			for (double equalShareResources = 0.0; equalShareResources<10.0; equalShareResources+=0.1)
			{
				fileOutput << size << " " << equalShareResources << " " << eval(size,equalShareResources) << "\n";
			}
		}
		fileOutput.close();
	}	

	protected:
	std::auto_ptr<ParameterSetW> mpParams;

};
//----------------------------------------------------------------------------------
class StrategyWzero : public StrategyWbase
{
	public:
	StrategyWzero(const ParameterSetW * pParams)
	{
		//Nothing
	}
	~StrategyWzero() {}
	double eval(const double& size, const double& equalShareResources) const
	{
		return equalShareResources;
	}
	/*void distributeResources(const double& totalResources, std::vector<double>& vectorResources)
	{
		assert(totalResources>=0.0);
		assert(vectorResources.size()!=0);
		const unsigned int popSize = vectorResources.size();
		const double resourcesShare = totalResources / static_cast<double>(popSize);
		assert(resourcesShare>=0.0);
		for (unsigned int i=0; i<popSize; ++i)
		{
			vectorResources[i] = resourcesShare;
		}


		#ifndef DEBUG_ZXC_GDF_635_ALPHA
		double sumResources = 0.0;
		for (unsigned int i=0; i<popSize; ++i)
		{
			sumResources+=vectorResources[i];
			#ifdef EXTREME_LOGGING
			std::cout
				<< "Resources[" << i 
				<< "]: " << vectorResources[i] << std::endl;
			#endif
		}
		//std::cout << "100.0+(1.0/1000.0): " << 100.0+(1.0/1000.0) << std::endl; 
		#ifdef LOGGING_RESOURCE_ACCURACY
		std::cout << "Resource accuracy: " << 100.0*sumResources/totalResources << "%" << std::endl;
		#endif
		if (sumResources<0.999*totalResources || sumResources>1.001*totalResources)
		{
			assert(!"Kut!");
		}
		#endif

	}*/
	std::string getString() const
	{
		return ("W: WZero, all individuals get equal share of food");
	}


	void testMe() const { StrategyWbase::testMe("Wzero.rda"); }

};
//----------------------------------------------------------------------------------
class StrategyWuniform : public StrategyWbase
{
	public:
	StrategyWuniform(const ParameterSetW * pParams)
	{
		assert(mpParams.get()!=NULL);
		mpParams->A = pParams->A;
		mpParams->B = pParams->B;
		mpParams->C = pParams->C;
		mpParams->D = pParams->D;
		assert(mpParams->A>=0.0 && mpParams->A<=1.0);
	}
	~StrategyWuniform() {}
	double eval(const double& size, const double& equalShareResources) const
	{
		//01-08-2005: OLD: return equalShareResources * (1.0 + (2.0*mpParams->A * (uniform()-0.5)));
		//Only called when SoilMite is not an egg anymore
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const double r_i = (1.0+(A*(size-B)*(size-B))) * C * (1.0 + (2.0* D * (uniform()-0.5)));
		return r_i;
	}

	/*void distributeResources(const double& totalResources, std::vector<double>& vectorResources)
	{
		assert(totalResources>=0.0);
		assert(vectorResources.size()!=0);
		const unsigned int popSize = vectorResources.size();
		if (popSize==1) { vectorResources[0]=totalResources; return; }
		const double resourcesEqual = totalResources / static_cast<double>(popSize);
		assert(resourcesEqual>=0.0);
		const double A = mpParams->A;

		const double step = (2.0*A)/static_cast<double>(popSize-1);


		//for (unsigned int i=0,double fraction = mpParams->A; i<popSize; ++i , fraction+=step)
		double fraction = 1.0-A;
		for (unsigned int i=0; i<popSize; ++i)
		{
			vectorResources[i] = resourcesEqual*fraction;
			fraction+=step;
		}

		random_shuffle(vectorResources.begin(), vectorResources.end());

		#ifndef DEBUG_ZXC_GDF_635_ALPHA
		double sumResources = 0.0;
		for (unsigned int i=0; i<popSize; ++i)
		{
			sumResources+=vectorResources[i];
			#ifdef EXTREME_LOGGING
			std::cout
				<< "Resources[" << i 
				<< "]: " << vectorResources[i] << std::endl;
			#endif
		}
		#ifdef LOGGING_RESOURCE_ACCURACY
		std::cout << "Resource accuracy: " << 100.0*sumResources/totalResources << "%" << std::endl;
		#endif
		if (sumResources<0.999*totalResources || sumResources>1.001*totalResources)
		{
			assert(!"Kut!");
		}
		#endif

	}*/
	std::string getString() const
	{
		return ("W: WUniform: Resources are unequally distributed, from "
			+ftoa(1.0-mpParams->A)+" to "
			+ftoa(1.0+mpParams->A)+" the equal resource share."
		    +"\nr_i = (1.0+(A*(size-B)*(size-B))) * C * (1.0 + (2.0* D * (uniform()-0.5)))");
	}
	
	void testMe() const { StrategyWbase::testMe("Wuniform.rda"); }

};
//----------------------------------------------------------------------------------
/*class StrategyWsizeDependent : public StrategyWbase
{
	public:
	StrategyWsizeDependent(const ParameterSetW * pParams)
	{
		assert(mpParams.get()!=NULL);
		mpParams->A = pParams->A;
		mpParams->B = pParams->B;
		mpParams->C = pParams->C;
		mpParams->D = pParams->D;
		assert(mpParams->A>=0.0);
		assert(mpParams->B>=0.0);
		assert(mpParams->C>=0.0 && mpParams->A<=1.0);
		assert(mpParams->D>=0.0 && mpParams->A<=1.0);
	}
	~StrategyWsizeDependent() {}
	double eval(const double& size, const double& equalShareResources) const
	{
		//Only called when SoilMite is not an egg anymore
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const double r_i = (1.0+(A*(size-B)*(size-B))) * C * (1.0 + (2.0* D * (uniform()-0.5)));
		return r_i;
	}*/

	/*void distributeResources(const double& totalResources, std::vector<double>& vectorResources)
	{
		assert(totalResources>=0.0);
		assert(vectorResources.size()!=0);
		const unsigned int popSize = vectorResources.size();
		if (popSize==1) { vectorResources[0]=totalResources; return; }
		const double resourcesEqual = totalResources / static_cast<double>(popSize);
		assert(resourcesEqual>=0.0);
		const double A = mpParams->A;

		const double step = (2.0*A)/static_cast<double>(popSize-1);


		//for (unsigned int i=0,double fraction = mpParams->A; i<popSize; ++i , fraction+=step)
		double fraction = 1.0-A;
		for (unsigned int i=0; i<popSize; ++i)
		{
			vectorResources[i] = resourcesEqual*fraction;
			fraction+=step;
		}

		random_shuffle(vectorResources.begin(), vectorResources.end());

		#ifndef DEBUG_ZXC_GDF_635_ALPHA
		double sumResources = 0.0;
		for (unsigned int i=0; i<popSize; ++i)
		{
			sumResources+=vectorResources[i];
			#ifdef EXTREME_LOGGING
			std::cout
				<< "Resources[" << i 
				<< "]: " << vectorResources[i] << std::endl;
			#endif
		}
		#ifdef LOGGING_RESOURCE_ACCURACY
		std::cout << "Resource accuracy: " << 100.0*sumResources/totalResources << "%" << std::endl;
		#endif
		if (sumResources<0.999*totalResources || sumResources>1.001*totalResources)
		{
			assert(!"Kut!");
		}
		#endif

	}*/
/*
	std::string getString() const
	{
		return ("W: WsizeDependent: Resources are unequally distributed dependent on size:"
		"\nr_i = (1.0+(A*(size-B)*(size-B))) * C * (1.0 + (2.0* D * (uniform()-0.5)))"
		+ "\nA: " + ftoa(mpParams->A) 
		+ "\nB: " + ftoa(mpParams->B) 
		+ "\nC: " + ftoa(mpParams->C) 
		+ "\nD: " + ftoa(mpParams->D)
		);  
		
	}
};*/
//----------------------------------------------------------------------------------

#endif //#ifndef __STRATEGY_SIMGA_H




