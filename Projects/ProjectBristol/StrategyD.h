/*
 *  StrategyD.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 31 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

///StrategyD[something] embodies the function for death rate.
///
///example of the formula being embodied by StrategyDdefault:
///
///D(s_i,v_i) = (1-exp(-alph*s_i)*exp(-B*v_i)+C
///
///D : Death rate, chance to die per time unit
///s_i : individual i's body size
///v_i : individual i's reserves
///A, B, C : constants
///
///The Strategy pattern can be found described in ref. 1.
///Instead of using the standard 'evil' pointer, I use the std::auto_ptr (ref. 2)
///
///
///
///1) Design Patterns. By Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides. ISBN: 0-201-63361-2
///2) Exceptional C++: 47 Engineering Puzzles, Programming Problems, and Solutions. By Herb Sutter. ISBN: 0-201-61562-2

#ifndef __STRATEGY_D_H
#define __STRATEGY_D_H

#include <fstream>
#include <memory>
#include "ParameterSets.h"
#include "HelperFunctions.h"

//----------------------------------------------------------------------------------
class StrategyDbase
{
	public:
	StrategyDbase() 
	{
		mpParams.reset(new ParameterSetD);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyDbase() {};
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
	std::auto_ptr<ParameterSetD> mpParams;
};
//----------------------------------------------------------------------------------
class StrategyDdefault : public StrategyDbase
{
	public:
	StrategyDdefault(const ParameterSetD * pParams)
	{
		mpParams->A = pParams->A;
		mpParams->B = pParams->B;
		mpParams->C = pParams->C;
		mpParams->D = pParams->D;
		assert(mpParams->A>=0.0);
		assert(mpParams->B>=0.0);
		assert(mpParams->C>=0.0);
		assert(mpParams->D>=0.0);
	}
	~StrategyDdefault() {};
	double eval(const double& s, const double& v) const
	{
		//OLD const double d = (1.0-exp(-mpParams->A*s)) * exp(-mpParams->B*v) + mpParams->C;
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const double d = A + (((1.0-A)*D*pow(s/(v+B),C))/(1.0+pow(s/(v+B),C)));
		assert(d>=0 && d<=1.0);
		return d;
	}
	std::string getString() const
	{
		const std::string begin =  "D(s,v) = ";
		const std::string part1 = "A + (1.0-A).D.((s/(v+B))^C) / (1.0+(s/(v+B))^C)";
		return begin + part1;
	}
	std::string getString(const double& s, const double& v) const
	{
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const std::string begin =  "D(s,v) = D("+ftoa(s)+","+ftoa(v)+") = ";
		const std::string part1 = ftoa(A)+" + (1.0-"+ftoa(A)+")."+ftoa(D)+".(("+ftoa(s)
		  +"/("+ftoa(v)+"+"+ftoa(B)+"))^"+ftoa(C)
		  +") / (1.0+("+ftoa(s)+"/("+ftoa(v)+"+"+ftoa(B)+"))^"+ftoa(C)+")";
		const std::string outcome = ftoa(eval(s,v));
		return begin + part1 + " = "+outcome;
	}

	void testMe() const
	{
		const std::string fileName = "Ddefault.rda";
		StrategyDbase::testMe(fileName);
	}

};
//----------------------------------------------------------------------------------
/*class StrategyDsizeOnly : public StrategyDbase
{
	public:
	StrategyDsizeOnly(const ParameterSetD * pParams)
	{
		mpParams.reset(new ParameterSetD);
		mpParams->A = pParams->A;
		assert(mpParams->A>=0.0);
	}
	~StrategyDsizeOnly() {};
	double eval(const double& s, const double& v) const
	{
		const double d = (1.0-exp(-mpParams->A*s));
		assert(d>=0 && d<=1.0);
		return d;
	}
	std::string getString() const
	{
		const std::string begin =  "D(s,v) = ";
		const std::string part1 = "(1.0-exp(-A*s))";
		return begin + part1 + " + C";
	}
	std::string getString(const double& s, const double& v) const
	{
		const std::string begin =  "D(s,v) = D("+ftoa(s)+","+ftoa(v)+") = ";
		const std::string part1 = "(1.0-exp(-" 	+ftoa(mpParams->A) + "*"+ftoa(s)+"))";
		const std::string outcome = ftoa(eval(s,v));
		return begin + part1 +  " = "+outcome;
	}
};
//----------------------------------------------------------------------------------
class StrategyDconstant : public StrategyDbase
{
	public:
	StrategyDconstant(const ParameterSetD * pParams)
	{
		mpParams.reset(new ParameterSetD);
		mpParams->A = pParams->A;
		assert(mpParams->A>=0.0  && mpParams->A<=1.0);
	}
	~StrategyDconstant() {};
	double eval(const double& s, const double& v) const
	{
		const double d = mpParams->A;
		assert(d>=0 && d<=1.0);
		return d;
	}
	std::string getString() const
	{
		const std::string begin =  "D(s,v) = ";
		const std::string part1 = "A";
		return begin + part1;
	}
	std::string getString(const double& s, const double& v) const
	{
		const std::string begin =  "D(s,v) = D("+ftoa(s)+","+ftoa(v)+") = ";
		const std::string part1 = ftoa(mpParams->A);
		const std::string outcome = ftoa(eval(s,v));
		return begin + part1 +  " = "+outcome;
	}
};*/
//----------------------------------------------------------------------------------


#endif //#ifndef __STRATEGY_D_H
