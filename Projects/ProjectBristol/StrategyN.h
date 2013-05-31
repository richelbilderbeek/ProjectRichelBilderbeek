/*
 *  StrategyN.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Thu Jun 30 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __STRATEGY_N_H
#define __STRATEGY_N_H

#include <memory>
#include "ParameterSets.h"
#include "HelperFunctions.h"
//----------------------------------------------------------------------------------
class StrategyNbase
{
	public:
	StrategyNbase() 
	{
		mpParams.reset(new ParameterSetN);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyNbase() {}
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
	std::auto_ptr<ParameterSetN> mpParams;
};
//----------------------------------------------------------------------------------
class StrategyNplastic : public StrategyNbase
{
	public:
	StrategyNplastic(const ParameterSetN * pParams)
	{
		assert(pParams!=NULL);
		mpParams->A = pParams->A;
		mpParams->B = pParams->B;
		mpParams->C = pParams->C;
		mpParams->D = pParams->D;
		mpParams->E = pParams->E;
		assert(mpParams->A>=0.0 && mpParams->A<=1.0);
		assert(mpParams->B>=0.0);
		assert(mpParams->C>=0.0);
		assert(mpParams->D>=0.0);
		assert(mpParams->E>=0.0);
	}
	~StrategyNplastic() {}
	double eval(const double& f, const double& v) const
	{
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const double E = mpParams->E;
		const double n = A*(D*f + E*v)+(1.0-A)*(B*D+C*E);
		assert(n>=0.0);
		return n;
	}
	std::string getString() const
	{
		return "N(f,v) = A*(D*f + E*v)+(1.0-A)*(B*D+C*E)";

	}
	std::string getString(const double& f, const double& v) const
	{
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const double E = mpParams->E;
		
		const std::string nStart =  "N(f,v) = N("+ftoa(f)+","+ftoa(v)+") = ";
		const std::string n1 = ftoa(A)+"*("+ftoa(D)+"*"+ftoa(f)+" + "+ftoa(E)+"*"+ftoa(v)+")+(1.0-"+ftoa(A)+")*("+ftoa(B)+"*"+ftoa(D)+"+"+ftoa(C)+"*"+ftoa(E)+")";
		const std::string nOutcome = ftoa(eval(f,v));
		const std::string n = nStart + n1+" = " + nOutcome;
		return n;
	}
	
	void testMe() const { StrategyNbase::testMe("Nplastic.rda"); }

};
//----------------------------------------------------------------------------------
class StrategyNconstant : public StrategyNbase
{
	public:
	StrategyNconstant(const ParameterSetN * pParams)
	{
		assert(pParams!=NULL);
		mpParams->A = pParams->A;
		assert(pParams->A>=0.0);
	}
	~StrategyNconstant() {}
	double eval(const double& f, const double& v) const
	{
		return mpParams->A;
	}
	std::string getString() const
	{
		return "N(f,v) = A";

	}
	std::string getString(const double& f, const double& v) const
	{
		const double A = mpParams->A;
		const std::string nStart =  "N(f,v) = N("+ftoa(f)+","+ftoa(v)+") = ";
		const std::string n1 = ftoa(A);
		const std::string nOutcome = ftoa(eval(f,v));
		const std::string n = nStart + n1+" = " + nOutcome;
		return n;
	}

	void testMe() const { StrategyNbase::testMe("Nconstant.rda"); }

};
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
#endif //#ifndef __STRATEGY_N_H
