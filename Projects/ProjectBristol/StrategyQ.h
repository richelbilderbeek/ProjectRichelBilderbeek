/*
 *  StrategyQ.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 31 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __STRATEGY_Q_H
#define __STRATEGY_Q_H


#include <memory>
#include <math.h>
#include "ParameterSets.h"
#include "HelperFunctions.h"
//----------------------------------------------------------------------------------
class StrategyQbase
{
	public:
	StrategyQbase() 
	{
		mpParams.reset(new ParameterSetQ);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyQbase() {}
	virtual double eval(const double&) const = 0;
	virtual std::string getString() const = 0;
	virtual std::string getString(const double&) const = 0;
	virtual void testMe() const = 0;
	void testMe(const std::string& filename) const
	{
		std::ofstream fileOutput(filename.c_str());
		assert(fileOutput.is_open()==true);
		for (double v = 0.0; v<10.0; v+=0.1)
		{
			fileOutput <<  v << " " << eval(v) << "\n";
		}
		fileOutput.close();
	}	

	protected:
	std::auto_ptr<ParameterSetQ> mpParams;
};
//----------------------------------------------------------------------------------
class StrategyQdefault : public StrategyQbase
{
	public:
	StrategyQdefault(const ParameterSetQ * pParams)
	{
		mpParams->A = pParams->A;
		mpParams->B = pParams->B;
		mpParams->C = pParams->C;
		assert(mpParams->A>=0.0);
		assert(mpParams->B>=0.0);
		assert(mpParams->C>=0.0);
	}
	~StrategyQdefault() {}
	double eval(const double& v) const
	{
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		//OLD: const double q = (exp(-A*v))*v;
		const double q = (A*v)/(1.0+(pow(v,B)*(C/A)));
		assert(q>=0 && q<=v);
		return (q);
	}

	std::string getString() const
	{
		const std::string qBegin = "Q(v) = ";
		const std::string q = "(A.v)/(1.0+(pow(v,B).(C/A)))";
		return (qBegin + q);
	}

	std::string getString(const double& v) const
	{
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const std::string qBegin = "Q(v) = Q("+ftoa(v)+") = ";
		const std::string q = "(" + ftoa(A)+"." + ftoa(v)+")/(1.0+(pow(" + ftoa(v)+"," + ftoa(B)+").(" + ftoa(C)+"/" + ftoa(A)+")))";
		const std::string qOutcome = ftoa(eval(v));
		return (qBegin + q + " = " + qOutcome);
	}
	
	void testMe() const { StrategyQbase::testMe("Qdefault.rda"); }

};
//----------------------------------------------------------------------------------
class StrategyQconstant : public StrategyQbase
{
	public:
	StrategyQconstant(const ParameterSetQ * pParams)
	{
		mpParams->A = pParams->A;
		assert(mpParams->A>=0.0 && mpParams->A<=1.0);
	}
	~StrategyQconstant() {}
	double eval(const double& v) const
	{
		return (mpParams->A*v);
	}

	std::string getString() const
	{
		const std::string qBegin = "Q(v) = ";
		const std::string q = "A.v";
		return (qBegin + q);
	}

	std::string getString(const double& v) const
	{
		const double A = mpParams->A;
		const std::string qBegin = "Q(v) = Q("+ftoa(v)+") = ";
		const std::string q = ftoa(A)+"*"+ftoa(v);
		const std::string qOutcome = ftoa(eval(v));
		return (qBegin + q + " = " + qOutcome);
	}
	
	void testMe() const { StrategyQbase::testMe("Qconstant.rda"); }

};
//----------------------------------------------------------------------------------

#endif //#ifndef __STRATEGY_P_H
