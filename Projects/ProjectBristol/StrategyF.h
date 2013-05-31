/*
 *  StrategyF.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 31 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __STRATEGY_F_H
#define __STRATEGY_F_H

#include <memory>
#include "ParameterSets.h"
#include "HelperFunctions.h"
//----------------------------------------------------------------------------------
class StrategyFbase
{
	public:
	StrategyFbase() 
	{
		mpParams.reset(new ParameterSetF);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyFbase() {}
	virtual double eval(const double&, const double&) const = 0;
	virtual std::string getString() const = 0;
	virtual std::string getString(const double&, const double&) const = 0;
	virtual void testMe() const = 0;
	void testMe(const std::string& filename) const
	{
		std::ofstream fileOutput(filename.c_str());
		assert(fileOutput.is_open()==true);
		
		for (double r = 0.0; r<10.0; r+=0.1)
		{
			for (double s = 0.0; s<10.0; s+=0.1)
			{
				fileOutput << r << " " << s << " " << eval(r,s) << "\n";
			}
		}
		fileOutput.close();
	}	

	protected:
	std::auto_ptr<ParameterSetF> mpParams;
};
//----------------------------------------------------------------------------------
class StrategyFdefault : public StrategyFbase
{
	public:
	StrategyFdefault(const ParameterSetF * pParams)
	{
		mpParams->A = pParams->A;
		assert(mpParams->A>=0.0 && mpParams->A<=1.0);
	}
	~StrategyFdefault() {}
	double eval(const double& r, const double& s) const
	{
		assert(r>=0.0);
		assert(s>=0.0);
		return (mpParams->A * r);
	}

	std::string getString() const
	{
		const std::string begin = "F(r,s) = ";
		const std::string part1 = "A*r";
		return begin + part1;
	}

	std::string getString(const double& r, const double& s) const
	{
		const std::string begin = "F(r,s) = F("+ftoa(r)+","+ftoa(s)+") = ";
		const std::string part1 = ftoa(mpParams->A)+"*"+ftoa(r);
		const std::string outcome = ftoa(eval(r,s));
		return begin + part1 + " = "+outcome;
	}
		void testMe() const
	{
		const std::string fileName = "Fdefault.rda";
		StrategyFbase::testMe(fileName);
	}

};
//----------------------------------------------------------------------------------



#endif //#ifndef __STRATEGY_H
