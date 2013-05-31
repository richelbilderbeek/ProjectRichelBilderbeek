/*
 *  FunctionsSingleton.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Wed May 25 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

///The function of FunctionsSingleton is to embody all formulae used in the simulation
///
///To be sure a simulation has only one set of formulae, I used the Singleton pattern (ref. 1).
///The different kinds of functions it can contain, are put in the Strategy Pattern (ref. 1).
///The Strategy pattern uses polymorphism, therefore a pointer to the derived Strategy class.
///Instead of the standard 'evil' pointer, I used the std::auto_ptr (ref. 2)
///
///The FunctionsSingleton is default initialized and later it is set with an SimulationFile.
///The SoilMite class has a static pointer to FunctionsSingleton, so all individuals always have the same mathematical behaviour
///Before the class Experiment executes a Simulation, it changes the FunctionsSingleton with a SimulationFile.
///
///
///References:
///1) Design Patterns. By Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides. ISBN: 0-201-63361-2
///2) Exceptional C++: 47 Engineering Puzzles, Programming Problems, and Solutions. By Herb Sutter. ISBN: 0-201-61562-2

#ifndef __FUNCTIONS_SINGLETON_H
#define __FUNCTIONS_SINGLETON_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "StrategyD.h"
#include "StrategyF.h"
#include "StrategyG.h"
#include "StrategyM.h"
#include "StrategyN.h"
#include "StrategyP.h"
#include "StrategyQ.h"
#include "StrategyR.h"
#include "StrategyW.h"

#include "Enumerations.h"
#include "HelperFunctions.h"
#include "SimulationFile.h"
#include "random.h"

class FunctionsSingleton
{
	public:
	static FunctionsSingleton * instance();

	double D(const double& s, const double& v) const { assert(mpD.get()!=NULL); return mpD->eval(s,v); }
	double F(const double& r, const double& s) const { assert(mpF.get()!=NULL); return mpF->eval(r,s); }
	double G(const double& f, const double& v) const { assert(mpG.get()!=NULL); return mpG->eval(f,v); }
	double M(const double& s, const double& v) const { assert(mpM.get()!=NULL); return mpM->eval(s,v); }
	double N(const double& f, const double& v) const { assert(mpN.get()!=NULL); return mpN->eval(f,v); }
	double P(const double& f, const double& v) const { assert(mpP.get()!=NULL); return mpP->eval(f,v); }
	double Q(const double& v) const { assert(mpQ.get()!=NULL); return mpQ->eval(v); }
	double R(const double& x, const double& t) const { assert(mpR.get()!=NULL); return mpR->eval(x,t); }
	double W(const double& s, const double& equalShare) const { assert(mpW.get()!=NULL); return mpW->eval(s,equalShare); }

	std::vector<double> FunctionsSingleton::distributeResources(const std::vector<double>&, const double&) const;
	/* 01-08-2005: Replaced by eval()
	void distributeResources(const double& totalResources, std::vector<double>& vectorResources) const 
	{ 
		mpW->distributeResources(totalResources, vectorResources);
	}*/

	//Setting functions and their parameters
	void setD(const EnumD&, const ParameterSetD*);
	void setF(const EnumF&, const ParameterSetF*);
	void setG(const EnumG&, const ParameterSetG*);
	void setM(const EnumM&, const ParameterSetM*);
	void setN(const EnumN&, const ParameterSetN*);
	void setP(const EnumP&, const ParameterSetP*);
	void setQ(const EnumQ&, const ParameterSetQ*);
	void setR(const EnumR&, const ParameterSetR*);
	void setW(const EnumW&, const ParameterSetW*);

	//Getting the formulas
	std::string getD() const { return mpD->getString(); }
	std::string getF() const { return mpF->getString(); }
	std::string getG() const { return mpG->getString(); }
	std::string getM() const { return mpM->getString(); }
	std::string getN() const { return mpN->getString(); }
	std::string getP() const { return mpP->getString(); }
	std::string getQ() const { return mpQ->getString(); }
	std::string getR() const { return mpR->getString(); }
	std::string getW() const { return mpW->getString(); }

	//Getting the formulas
	std::string getD(const double& s, const double& v) const { return mpD->getString(s,v); }
	std::string getF(const double& r, const double& s) const { return mpF->getString(r,s); }
	std::string getG(const double& f, const double& v) const { return mpG->getString(f,v); }
	std::string getM(const double& s, const double& v) const { return mpM->getString(s,v); }
	std::string getN(const double& f, const double& v) const { return mpN->getString(f,v); }
	std::string getP(const double& f, const double& v) const { return mpP->getString(f,v); }
	std::string getQ(const double& v) const { return mpQ->getString(v); }
	std::string getR(const double& x, const double& t) const { return mpR->getString(x,t); }

	//Environmental parameters
	double getAlpha() const { return mAlpha; }
	double getBeta()  const { return mBeta ; }
	double getGamma() const { return mGamma; }
	void setAlpha(double);
	void setBeta( double);
	void setGamma(double);

	//Misc
	void coutAll() const;
	
	protected:
	FunctionsSingleton();

	private:
	static FunctionsSingleton * mpInstance;
	
	std::auto_ptr<StrategyDbase> mpD;
	std::auto_ptr<StrategyFbase> mpF;
	std::auto_ptr<StrategyGbase> mpG;
	std::auto_ptr<StrategyMbase> mpM;
	std::auto_ptr<StrategyNbase> mpN;
	std::auto_ptr<StrategyPbase> mpP;
	std::auto_ptr<StrategyQbase> mpQ;
	std::auto_ptr<StrategyRbase> mpR;
	std::auto_ptr<StrategyWbase> mpW;

	double mAlpha, mBeta, mGamma;

	
	//Misc
	void processError(const std::string&) const;

};

#endif //#ifndef __FUNCTIONS_SINGLETON_H


