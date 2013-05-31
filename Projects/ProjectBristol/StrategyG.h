/*
 *  StrategyG.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 31 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __STRATEGY_G_H
#define __STRATEGY_G_H

#include <memory>
#include "ParameterSets.h"
#include "HelperFunctions.h"
//----------------------------------------------------------------------------------
class StrategyGbase
{
	public:
	StrategyGbase() 
	{
		mpParams.reset(new ParameterSetG);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyGbase() {}
	virtual double eval(const double&, const double&) const = 0;
	virtual std::string getString() const = 0;
	virtual std::string getString(const double&, const double&) const = 0;
	virtual void testMe() const = 0;
	void testMe(const std::string& filename) const
	{
		std::ofstream fileOutput(filename.c_str());
		assert(fileOutput.is_open()==true);
		
		for (double f = 0.0; f<10.0; f+=0.1)
		{
			for (double v = 0.0; v<10.0; v+=0.1)
			{
				fileOutput << f << " " << v << " " << eval(f,v) << "\n";
			}
		}
		fileOutput.close();
	}	

	protected:
	std::auto_ptr<ParameterSetG> mpParams;
};
//----------------------------------------------------------------------------------
class StrategyGplastic : public StrategyGbase
{
	public:
	StrategyGplastic(const ParameterSetG * pParams)
	{
		assert(pParams->A>=0.0);
		mpParams->A = pParams->A;
	}
	~StrategyGplastic() {}
	double eval(const double& f, const double& v) const
	{
		const double A = mpParams->A;
		const double g = 1.0-exp(-A*(f-v)*(f-v));
		assert(g>=0.0 && g<=1.0);
		if (g<0.001)
		{
			std::cout << "WARNING: Value of Gdefault was smaller then 0.001. Setting this to the value of 0.001" << std::endl;
			return 0.001;
		}
		return g;
	}
	std::string getString() const
	{
		const std::string gStart =  "G(f,v) = ";
		const std::string g1 = "1.0-exp(-A*(f-v)*(f-v))";
		const std::string g = gStart + g1;
		return g;

	}
	std::string getString(const double& f, const double& v) const
	{
		const double A = mpParams->A;
		const std::string gStart =  "G(f,v) = F("+ftoa(f)+","+ftoa(v)+") = ";
		const std::string g1 = "1.0-exp(-"+ftoa(A)+"*("+ftoa(f)+"-"+ftoa(v)+")*("+ftoa(f)+"-"+ftoa(v)+"))";
		const std::string gOutcome = ftoa(eval(f,v));
		const std::string g = gStart + g1+" = " + gOutcome;
		return g;
	}

	void testMe() const
	{
		const std::string fileName = "Gplastic.rda";
		StrategyGbase::testMe(fileName);
	}

};
//----------------------------------------------------------------------------------
class StrategyGconstant : public StrategyGbase
{
	public:
	StrategyGconstant(const ParameterSetG * pParams)
	{
		assert(pParams->A>=0.0);
		mpParams->A = pParams->A;
	}
	~StrategyGconstant() {}
	double eval(const double& f, const double& v) const
	{
		const double g = mpParams->A;
		assert(g>=0.0 && g<=1.0);
		return g;
	}
	std::string getString() const
	{
		const std::string gStart =  "G(f,v) = ";
		const std::string g1 = "A";
		const std::string g = gStart + g1;
		return g;

	}
	std::string getString(const double& f, const double& v) const
	{
		const double A = mpParams->A;
		const std::string gStart =  "G(f,v) = G("+ftoa(f)+","+ftoa(v)+") = ";
		const std::string g1 = ftoa(A);
		const std::string gOutcome = ftoa(eval(f,v));
		const std::string g = gStart + g1+" = " + gOutcome;
		return g;
	}

	void testMe() const
	{
		StrategyGbase::testMe("Gconstant.rda");
	}

};
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------


#endif //#ifndef __STRATEGY_G_H
