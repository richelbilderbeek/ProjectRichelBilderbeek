/*
 *  StrategyM.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 31 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __STRATEGY_M_H
#define __STRATEGY_M_H

#include <memory>
#include "ParameterSets.h"
#include "HelperFunctions.h"
//----------------------------------------------------------------------------------
class StrategyMbase
{
	public:
	StrategyMbase() 
	{
		mpParams.reset(new ParameterSetM);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyMbase() {}
	virtual double eval(const double&, const double&) const = 0;
	virtual std::string getString() const = 0;
	virtual std::string getString(const double&, const double&) const = 0;
	virtual void testMe() const = 0;
	void testMe(const std::string& filename) const
	{
		std::ofstream fileOutput(filename.c_str());
		assert(fileOutput.is_open()==true);
		
		for (double s = 0.0; s<10.0; s+=0.1)
		{
			for (double v = 0.0; v<10.0; v+=0.1)
			{
				fileOutput << s << " " << v << " " << eval(s,v) << "\n";
			}
		}
		fileOutput.close();
	}	

	protected:
	std::auto_ptr<ParameterSetM> mpParams;
};
//----------------------------------------------------------------------------------
class StrategyMdefault : public StrategyMbase
{
	public:
	StrategyMdefault(const ParameterSetM * pParams)
	{
		mpParams->A = pParams->A;
		assert(mpParams->A>=0.0);
	}
	~StrategyMdefault() {}
	double eval(const double& s, const double& v) const
	{
		return s * mpParams->A;
	}

	std::string getString() const
	{
		return "M(s,v) = A.s";

	}

	std::string getString(const double& s, const double& v) const
	{
		const double A = mpParams->A;
		const std::string mStart = "M(s,v) = M("+ftoa(s)+","+ftoa(v)+") = ";
		const std::string m1 = ftoa(A)+"*"+ftoa(s);
		const std::string mOutcome = ftoa(eval(s,v));
		const std::string m = mStart + m1 + " = " + mOutcome;
		return m;
	}
	
		void testMe() const
	{
		StrategyMbase::testMe("Mdefault.rda");
	}

};
//----------------------------------------------------------------------------------
class StrategyMconstant : public StrategyMbase
{
	public:
	StrategyMconstant(const ParameterSetM * pParams)
	{
		mpParams->A = pParams->A;
		mpParams->B  = pParams->B;
		assert(mpParams->A>=0.0);
	}
	~StrategyMconstant() {}
	double eval(const double& s, const double& v) const
	{
		assert(s>=0.0);
		assert(v>=0.0);
		const double m = mpParams->A;
		return m;
	}

	std::string getString() const
	{
		const std::string mStart = "M(s,v) = ";
		const std::string m1 = "A";
		const std::string m = mStart + m1;
		return m;

	}

	std::string getString(const double& s, const double& v) const
	{
		const double A = mpParams->A;
		const std::string mStart = "M(s,v) = M("+ftoa(s)+","+ftoa(v)+") = ";
		const std::string m1 = ftoa(A);
		const std::string mOutcome = ftoa(eval(s,v));
		const std::string m = mStart + m1 + " = " + mOutcome;
		return m;
	}
	
		void testMe() const
	{
		StrategyMbase::testMe("Mconstant.rda");
	}

};
//----------------------------------------------------------------------------------


#endif //#ifndef __STRATEGY_M_H
