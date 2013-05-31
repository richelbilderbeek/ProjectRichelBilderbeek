/*
 *  StrategyP.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 31 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __STRATEGY_P_H
#define __STRATEGY_P_H

#include <memory>
#include "ParameterSets.h"
#include "HelperFunctions.h"

//----------------------------------------------------------------------------------
class StrategyPbase
{
	public:
	StrategyPbase() 
	{
		mpParams.reset(new ParameterSetP);
		assert(mpParams.get()!=NULL);
	}
	virtual ~StrategyPbase() {}
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
	std::auto_ptr<ParameterSetP> mpParams;
};
//----------------------------------------------------------------------------------
/* Removed at 01-08-2005
class StrategyPplasticA : public StrategyPbase
{
	public:
	StrategyPplasticA(const ParameterSetP * pParams)
	{
		mpParams->A = pParams->A;
		mpParams->B  = pParams->B;
		assert(mpParams->A>=0.0);
		assert(mpParams->B>=0.0);
	}
	~StrategyPplasticA() {}
	double eval(const double& f, const double& v) const
	{
		assert(f>=0.0);
		assert(v>=0.0);
		const double p1 = 1.0-exp(-mpParams->A * f);
		const double p2 = 1.0-exp(-mpParams->B  * v);
		const double p  = p1 * p2;
		assert(p1>=0.0 && p1<=1.0);
		assert(p2>=0.0 && p2<=1.0);
		assert(p >=0.0 && p <=1.0);
		return p;
	}

	std::string getString() const
	{
		const std::string pBegin = "P(f,v) = ";
		const std::string p1 = "[1.0-exp(-A*f)]";
		const std::string p2 = "[1.0-exp(-B *v)]";
		const std::string p = pBegin + p1 + " * " + p2;
		return p;
	}

	std::string getString(const double& f, const double& v) const
	{
		const double A = mpParams->A;
		const double B  = mpParams->B;
		const std::string pBegin = "P(f,v) = P("+ftoa(f)+","+ftoa(v)+") = ";
		const std::string p1 = "[1.0-exp(-"+ftoa(A)+"*"+ftoa(f)+")]";
		const std::string p2 = "[1.0-exp(-"+ftoa(B )+"*"+ftoa(v)+")]";
		const std::string pOutcome = ftoa(eval(f,v));
		const std::string p = pBegin + p1 + " * " + p2 + " = " + pOutcome;
		return p;
	}
};*/
//----------------------------------------------------------------------------------
class StrategyPplastic : public StrategyPbase
{
	public:
	StrategyPplastic(const ParameterSetP * pParams)
	{
		mpParams->A = pParams->A;
		mpParams->B = pParams->B;
		mpParams->C = pParams->C;
		mpParams->D = pParams->D;
		mpParams->E = pParams->E;
		assert(mpParams->A>=0.0 && mpParams->A<=1.0);
		assert(mpParams->B>=0.0);
		assert(!(mpParams->C==0.0 && mpParams->A!=0.0));
		assert(mpParams->D>=0.0);
		assert(!(mpParams->E==0.0 && mpParams->A!=0.0));
	}
	~StrategyPplastic() {}
	double eval(const double& f, const double& v) const
	{
		assert(f>=0.0);
		assert(v>=0.0);
		const double A = mpParams->A;
		const double B = mpParams->B;
		const double C = mpParams->C;
		const double D = mpParams->D;
		const double E = mpParams->E;
		#ifndef __HACK_RIOGWIGUIGUOYG
		if (!((pow(f/C,B)/(1.0+pow(f/C,B))) * (pow(v/E,D)/(1.0+pow(v/E,D)))>=0.0))
		{
		  std::cout << "ERROR: " << std::endl
		    << "f: " << f << std::endl
		    << "v: " << v << std::endl
		    << "A: " << A << std::endl
		    << "B: " << B << std::endl
		    << "C: " << C << std::endl
		    << "D: " << D << std::endl
		    << "E: " << E << std::endl
	      << ((pow(f/C,B)/(1.0+pow(f/C,B))) * (pow(v/E,D)/(1.0+pow(v/E,D)))) 
			<< std::endl;
		}
		#endif
		//Assert((pow(f/C,B)/(1.0+pow(f/C,B))) * (pow(v/E,D)/(1.0+pow(v/E,D)))>=0.0);
		const double p = ( A==0.0 ? 0.5 : A*(sqrt((pow(f/C,B)/(1.0+pow(f/C,B))) * (pow(v/E,D)/(1.0+pow(v/E,D)))))+((1.0-A)*0.5));
		#ifndef __HACK_UYGEFOUYG
		if (!(p >=-0.0001 && p <=1.0001)) std::cout << "ERROR: p: " << p << std::endl;
		#endif
		assert(p >=-0.0001 && p <=1.0001);
		return p;
	}

	std::string getString() const
	{
		const std::string pBegin = "P(f,v) = ";
		const std::string p1 = "A*(sqrt((pow(f/C,B)/(1.0+pow(f/C,B))) * (pow(v/E,D)/(1.0+pow(v/E,D)))))+((1.0-A)*0.5)";
		const std::string p = pBegin + p1;
		return p;
	}

	std::string getString(const double& f, const double& v) const
	{
		const std::string pBegin = "P(f,v) = P("+ftoa(f)+","+ftoa(v)+") = ";
		const std::string p1 = "something";
		const std::string pOutcome = ftoa(eval(f,v));
		const std::string p = pBegin + p1 + " = " + pOutcome;
		return p;
	}
	
	void testMe() const { StrategyPbase::testMe("Pplastic.rda"); }

};
//----------------------------------------------------------------------------------
class StrategyPconstant : public StrategyPbase
{
	public:
	StrategyPconstant(const ParameterSetP * pParams)
	{
		mpParams->A = pParams->A;
		assert(mpParams->A>=0.0);
	}
	~StrategyPconstant() {}
	double eval(const double& f, const double& v) const
	{
		assert(f>=0.0);
		assert(v>=0.0);
		const double p = mpParams->A;
		assert(p >=0.0 && p <=1.0);
		return p;
	}

	std::string getString() const
	{
		const std::string pBegin = "P(f,v) = ";
		const std::string p1 = "A";
		const std::string p = pBegin + p1;
		return p;
	}

	std::string getString(const double& f, const double& v) const
	{
		const double A = mpParams->A;
		const std::string pBegin = "P(f,v) = P("+ftoa(f)+","+ftoa(v)+") = ";
		const std::string p1 = ftoa(A);
		const std::string pOutcome = ftoa(eval(f,v));
		const std::string p = pBegin +  " = " + pOutcome;
		return p;
	}
	
	void testMe() const { StrategyPbase::testMe("Pconstant.rda"); }

};
//----------------------------------------------------------------------------------


#endif //#ifndef __STRATEGY_P_H
