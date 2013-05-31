/*
 *  FunctionsSingleton.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Wed May 25 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#include "FunctionsSingleton.h"
//----------------------------------------------------------------------------------
FunctionsSingleton * FunctionsSingleton::mpInstance = NULL;
//----------------------------------------------------------------------------------
FunctionsSingleton::FunctionsSingleton() :
	mAlpha(0.0),
	mBeta( 0.0),
	mGamma(0.0)
{ 
	const std::auto_ptr<ParameterSetD> paramsD(new ParameterSetD);
	const std::auto_ptr<ParameterSetF> paramsF(new ParameterSetF);
	const std::auto_ptr<ParameterSetG> paramsG(new ParameterSetG);
	const std::auto_ptr<ParameterSetM> paramsM(new ParameterSetM);
	const std::auto_ptr<ParameterSetN> paramsN(new ParameterSetN);
	const std::auto_ptr<ParameterSetP> paramsP(new ParameterSetP);
	const std::auto_ptr<ParameterSetQ> paramsQ(new ParameterSetQ);
	const std::auto_ptr<ParameterSetR> paramsR(new ParameterSetR);
	const std::auto_ptr<ParameterSetW> paramsW(new ParameterSetW);
	mpD.reset(new StrategyDdefault(paramsD.get()));
	mpF.reset(new StrategyFdefault(paramsF.get()));
	mpG.reset(new StrategyGconstant(paramsG.get()));
	mpM.reset(new StrategyMdefault(paramsM.get()));
	mpN.reset(new StrategyNplastic(paramsN.get()));
	mpP.reset(new StrategyPconstant(paramsP.get()));
	mpQ.reset(new StrategyQdefault(paramsQ.get()));
	mpR.reset(new StrategyRconstant(paramsR.get()));
	mpW.reset(new StrategyWzero(paramsW.get()));
}
//----------------------------------------------------------------------------------
FunctionsSingleton * FunctionsSingleton::instance()
{
	if (mpInstance==NULL) mpInstance = new FunctionsSingleton();
	return mpInstance;
}
//----------------------------------------------------------------------------------
std::vector<double> FunctionsSingleton::distributeResources(const std::vector<double>& popBodySize, const double& totalResources) const 
{
	const unsigned int popSize = popBodySize.size();
	const double equalShare = totalResources / static_cast<double>(popSize);
	std::vector<double> resource(popSize);

	double sumResources = 0.0;
	for(unsigned int i=0; i<popSize; ++i)
	{
		resource[i] = W(popBodySize[i],equalShare);
		sumResources+=resource[i];
	}
	
	if (sumResources>totalResources)
	{
		//Scale down
		const double scale = totalResources / sumResources;
		assert(scale<1.0);
		for(unsigned int i=0; i<popSize; ++i) 
		{
			resource[i] *= scale;
		}
	}

	#ifndef NDEBUG
	//Check again to be sure
	double sumResourcesDebug = 0.0;
	for(unsigned int i=0; i<popSize; ++i)
	{
		sumResources+=resource[i];
	}
	assert(sumResourcesDebug<=sumResources);
	#endif
	
	return resource;
	
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setD(const EnumD& enumD, const ParameterSetD* params)
{
	switch (enumD)
	{
		case enumDdefault  : mpD.reset(new StrategyDdefault(params)); return;
		//case enumDsizeOnly : mpD.reset(new StrategyDsizeOnly(params)); return;
		//case enumDconstant : mpD.reset(new StrategyDconstant(params)); return;
	}
	processError("void FunctionsSingleton::setD(const EnumD& enumD, const ParameterSet& params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setF(const EnumF& enumF, const ParameterSetF* params)
{
	switch (enumF)
	{
		//case enumFgauss    : mpF.reset(new StrategyFgauss(params)); return;
		case enumFdefault  : mpF.reset(new StrategyFdefault(params)); return;
		//case enumFconstant : mpF.reset(new StrategyFconstant(params)); return;
	}
	processError("void FunctionsSingleton::setF(const EnumF& enumF, const ParameterSet& params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setG(const EnumG& enumG, const ParameterSetG* params)
{
	switch (enumG)
	{
		case enumGplastic  : mpG.reset(new StrategyGplastic(params)); return;
		case enumGconstant : mpG.reset(new StrategyGconstant(params)); return;
	}
	processError("void FunctionsSingleton::setG(const EnumG& enumG, const ParameterSet& params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setM(const EnumM& enumM, const ParameterSetM* params)
{
	switch (enumM)
	{
		case enumMdefault : mpM.reset(new StrategyMdefault(params)); return;
		case enumMconstant: mpM.reset(new StrategyMconstant(params)); return;
	}
	processError("void FunctionsSingleton::setM(const EnumM& enumM, const ParameterSetM& params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setN(const EnumN& enumN, const ParameterSetN* params)
{
	switch (enumN)
	{
		case enumNplastic  : mpN.reset(new StrategyNplastic(params)); return;
		case enumNconstant : mpN.reset(new StrategyNconstant(params)); return;
	}
	processError("void FunctionsSingleton::setN(const EnumN& enumN, const ParameterSetN& params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setP(const EnumP& enumP, const ParameterSetP* params)
{
	switch (enumP)
	{
		case enumPplastic  : mpP.reset(new StrategyPplastic(params)); return;
		//case enumPplasticB  : mpP.reset(new StrategyPplasticB(params)); return;
		//case enumPnonPlastic: mpP.reset(new StrategyPnonPlastic(params)); return;
		case enumPconstant  : mpP.reset(new StrategyPconstant(params)); return;
	}
	processError("void FunctionsSingleton::setP(const EnumP& enumP, const ParameterSet& params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setQ(const EnumQ& enumQ, const ParameterSetQ* params)
{
	switch (enumQ)
	{
		case enumQdefault: mpQ.reset(new StrategyQdefault(params)); return;
		case enumQconstant: mpQ.reset(new StrategyQconstant(params)); return;
	}
	processError("void FunctionsSingleton::setQ(const EnumQ& enumQ, const ParameterSet& params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setR(const EnumR& enumR, const ParameterSetR* params)
{
	switch (enumR)
	{
		case enumRconstant: mpR.reset(new StrategyRconstant(params)); return;
		case enumRlogistic: mpR.reset(new StrategyRlogistic(params)); return;
		case enumRcosine  : mpR.reset(new StrategyRcosine(params)); return;
	}
	processError("void FunctionsSingleton::setR(const EnumR& enumR, const ParameterSet& params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setW(const EnumW& enumW, const ParameterSetW* params)
{
	switch(enumW)
	{
		case enumWzero: mpW.reset(new StrategyWzero(params)); return;
		case enumWuniform: mpW.reset(new StrategyWuniform(params)); return;
	}
	processError("void FunctionsSingleton::setW(const EnumW& enumW, const ParameterSetW* params)");
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setAlpha(double A)
{
	if (A<=0.0) 
	{
		std::cout << "WARNING! A<=0.0! Set to 1.0." << std::endl;
		A = 1.0;
	}
	mAlpha = A;
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setBeta(double B)
{
	if (B<=0.0) 
	{
		std::cout << "WARNING! B<=0.0! Set to 1.0." << std::endl;
		B = 1.0;
	}
	mBeta = B;
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::setGamma(double C)
{
	if (C<=0.0) 
	{
		std::cout << "WARNING! A<=0.0! Set to 1.0." << std::endl;
		C = 1.0;
	}
	mGamma = C;

}
//----------------------------------------------------------------------------------
void FunctionsSingleton::coutAll() const
{
	std::cout << getD() << std::endl;
	std::cout << getF() << std::endl;
	std::cout << getG() << std::endl;
	std::cout << getM() << std::endl;
	std::cout << getN() << std::endl;
	std::cout << getP() << std::endl;
	std::cout << getQ() << std::endl;
	std::cout << getR() << std::endl;
	std::cout << getW() << std::endl;
	
	std::cout << "Alpha: " << mAlpha << std::endl;
	std::cout << "Beta: "  << mBeta  << std::endl;
	std::cout << "Gamma: " << mGamma << std::endl;
}
//----------------------------------------------------------------------------------
void FunctionsSingleton::processError(const std::string& errorMessage) const
{
	std::cout << "ERROR!!!" << std::endl;
	std::cout << "Message: " << errorMessage << std::endl;
	std::exit(1);
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
