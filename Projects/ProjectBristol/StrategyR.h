/*
 *  StrategyR.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 31 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __STRATEGY_R_H
#define __STRATEGY_R_H

#include <iostream>
#include <memory>
#include "ParameterSets.h"
#include "HelperFunctions.h"
//----------------------------------------------------------------------------------
class StrategyRbase
{
	public:
	StrategyRbase() 
	{
		mpParams.reset(new ParameterSetR);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyRbase() {}
	virtual double eval(const double&, const double&) const = 0;
	virtual std::string getString() const = 0;
	virtual std::string getString(const double&, const double&) const = 0;
	virtual void testMe() const = 0;
	void testMe(const std::string& filename) const
	{
		std::ofstream fileOutput(filename.c_str());
		assert(fileOutput.is_open()==true);
		
		for (double x = 0.0; x<10.0; x+=0.1)
		{
			for (double t = 0.0; t<10.0; t+=0.1)
			{
				fileOutput << x << " " << t << " " << eval(x,t) << "\n";
			}
		}
		fileOutput.close();
	}	

	protected:
	std::auto_ptr<ParameterSetR> mpParams;
};
//----------------------------------------------------------------------------------
class StrategyRconstant : public StrategyRbase
{
	public:
	StrategyRconstant(const ParameterSetR * pParams)
	{
		mpParams->A = pParams->A;
		mpParams->B  = pParams->B;
		assert(mpParams->A>=0.0);
		assert(mpParams->B>=0.0 && mpParams->B <=1.0);
	}
	~StrategyRconstant() {}
	double eval(const double& x, const double& t) const
	{
		assert(x>-0.001);
		assert(t>=0.0);
		const double A = mpParams->A;
		const double B  = mpParams->B;
		const double inflow = A - (B*x);
		return (inflow);
	}

	std::string getString() const
	{
		const std::string rBegin = "R(x,t) = ";
		const std::string r = "A - (B*x)";
		return (rBegin + r);
	}

	std::string getString(const double& x, const double& t) const
	{
		const double A = mpParams->A;
		const double B  = mpParams->B;
		
		const std::string rBegin = "R(x,t) = R("+ftoa(x)+","+ftoa(t)+") = ";
		const std::string r = ftoa(A)+"-("+ftoa(B)+"*"+ftoa(x)+")";
		const std::string rOutcome = ftoa(eval(x,t));
		return (rBegin + r + " = " + rOutcome);
	}
	
	void testMe() const { StrategyRbase::testMe("Rconstant.rda"); }

};
//----------------------------------------------------------------------------------
class StrategyRlogistic : public StrategyRbase
{
	public:
	StrategyRlogistic(const ParameterSetR * pParams)
	{
		mpParams->A = pParams->A;
		mpParams->B  = pParams->B;
		assert(mpParams->A>=0.0);
		assert(mpParams->B>=0.0);
	}
	~StrategyRlogistic() {}
	//Inflow can be negative
	double eval(const double& x, const double& t) const
	{
		double xCopy = x;
		if (x>-0.001 && x<0.0) xCopy=0.0;
		assert(xCopy>=0.0);
		assert(t>=0.0);
		const double A = mpParams->A;
		const double B = mpParams->B;
		//const double r = x + (A*x*(1.0-(B/x))); //NOT THIS ONE!!! R SHOULD BE INFLOW ONLY!
		const double r = (A*xCopy*(1.0-(x/B)));
		return (r);
	}

	std::string getString() const
	{
		const std::string rBegin = "R(x,t) = ";
		//const std::string r = "A*x*(1.0-(B/x))";
		const std::string r = "A*x*(1.0-(x/B))";
		return (rBegin + r);
	}

	std::string getString(const double& x, const double& t) const
	{
		const double A = mpParams->A;
		const double B = mpParams->B;
		const std::string rBegin = "R(x,t) = R("+ftoa(x)+","+ftoa(t)+") = ";
		//const std::string r = ftoa(A)+"*"+ftoa(x)+"*(1.0-("+ftoa(B)+"/"+ftoa(x)+"))";
		const std::string r = ftoa(A)+"*"+ftoa(x)+"*(1.0-("+ftoa(x)+"/"+ftoa(B)+"))";
		const std::string rOutcome = ftoa(eval(x,t));
		return (rBegin + r + " = " + rOutcome);
	}
	
	void testMe() const { StrategyRbase::testMe("Rlogistic.rda"); }

};
//----------------------------------------------------------------------------------
class StrategyRcosine : public StrategyRbase
{
	public:
	StrategyRcosine(const ParameterSetR * pParams)
	{
		mpParams->A = pParams->A;
		mpParams->B = pParams->B;
		mpParams->C = pParams->C;
		mpParams->D = pParams->D;
		assert(mpParams->A>=0.0);
		assert(mpParams->B>=0.0);
		assert(mpParams->C>=0.0);
	}
	~StrategyRcosine() {}
	//Inflow can be negative
	double eval(const double& x, const double& t) const
	{
		assert(x>=0.0);
		assert(t>=0.0);
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const double r = A + (B*(cos( ((M_PI*2.0)/C)*t + D)));
		return (r);
	}

	std::string getString() const
	{
		const std::string rBegin = "R(x,t) = ";
		const std::string r = "A+B*cos( (2pi/C)*t + D )";
		return (rBegin + r);
	}

	std::string getString(const double& x, const double& t) const
	{
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const std::string rBegin = "R(x,t) = R("+ftoa(x)+","+ftoa(t)+") = ";

		const std::string r = ftoa(A)+"+"+ftoa(B)+"*cos( (2pi/"+ftoa(C)+")*"+ftoa(t)+" + "+ftoa(D)+" )";
		const std::string rOutcome = ftoa(eval(x,t));
		return (rBegin + r + " = " + rOutcome);
	}
	
	void testMe() const { StrategyRbase::testMe("Rcosine.rda"); }

};
//----------------------------------------------------------------------------------
#endif //#ifndef __STRATEGY_P_H
