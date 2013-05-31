/*
 *  ParameterSets.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 31 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __PARAMETERSETS_H
#define __PARAMETERSETS_H

#include <iostream>
#include <memory>
#include "Enumerations.h"

//----------------------------------------------------------------------------------
//
//  COMPUTER GENERATED CODE, except for:
//    - ParameterSetSimulation (at the bottom)
//
//----------------------------------------------------------------------------------
class ParameterSetD
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetD() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetD& params)
	{
		os << "    D.A: " << params.A << std::endl
		   << "    D.B: " << params.B << std::endl
		   << "    D.C: " << params.C << std::endl
		   << "    D.D: " << params.D << std::endl
		   << "    D.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetD* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetD>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------
class ParameterSetF
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetF() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetF& params)
	{
		os << "    F.A: " << params.A << std::endl
		   << "    F.B: " << params.B << std::endl
		   << "    F.C: " << params.C << std::endl
		   << "    F.D: " << params.D << std::endl
		   << "    F.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetF* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetF>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------
class ParameterSetG
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetG() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetG& params)
	{
		os << "    G.A: " << params.A << std::endl
		   << "    G.B: " << params.B << std::endl
		   << "    G.C: " << params.C << std::endl
		   << "    G.D: " << params.D << std::endl
		   << "    G.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetG* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetG>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------
class ParameterSetM
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetM() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetM& params)
	{
		os << "    M.A: " << params.A << std::endl
		   << "    M.B: " << params.B << std::endl
		   << "    M.C: " << params.C << std::endl
		   << "    M.D: " << params.D << std::endl
		   << "    M.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetM* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetM>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------
class ParameterSetN
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetN() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetN& params)
	{
		os << "    N.A: " << params.A << std::endl
		   << "    N.B: " << params.B << std::endl
		   << "    N.C: " << params.C << std::endl
		   << "    N.D: " << params.D << std::endl
		   << "    N.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetN* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetN>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------
class ParameterSetP
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetP() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetP& params)
	{
		os << "    P.A: " << params.A << std::endl
		   << "    P.B: " << params.B << std::endl
		   << "    P.C: " << params.C << std::endl
		   << "    P.D: " << params.D << std::endl
		   << "    P.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetP* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetP>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------
class ParameterSetQ
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetQ() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetQ& params)
	{
		os << "    Q.A: " << params.A << std::endl
		   << "    Q.B: " << params.B << std::endl
		   << "    Q.C: " << params.C << std::endl
		   << "    Q.D: " << params.D << std::endl
		   << "    Q.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetQ* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetQ>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------
class ParameterSetR
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetR() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetR& params)
	{
		os << "    R.A: " << params.A << std::endl
		   << "    R.B: " << params.B << std::endl
		   << "    R.C: " << params.C << std::endl
		   << "    R.D: " << params.D << std::endl
		   << "    R.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetR* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetR>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------
class ParameterSetW
{
	public:
	double A;
	double B;
	double C;
	double D;
	double E;
	ParameterSetW() : A(0.0), B(0.0), C(0.0), D(0.0), E(0.0) { ; }
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetW& params)
	{
		os << "    W.A: " << params.A << std::endl
		   << "    W.B: " << params.B << std::endl
		   << "    W.C: " << params.C << std::endl
		   << "    W.D: " << params.D << std::endl
		   << "    W.E: " << params.E;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetW* pParams)
	{
		os << *pParams; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetW>& pParams)
	{
		os << pParams.get(); return os;
	}
};
//----------------------------------------------------------------------------------



















//----------------------------------------------------------------------------------
class ParameterSetSimulation
{
	public:
	ParameterSetSimulation() :
	outputFileName("defaultOutputFile.txt"),
	seed(0),
	reproductionMode(enumReproductionModeAmount),
	startingPopSize(1000),
	startingResources(0.0),
	maxTime(100),
	A(1.0),
	B(1.0),
	C(1.0),
	bodySizeAdult(10.0),
	enumD(enumDdefault),
	enumF(enumFdefault),
	enumG(enumGconstant),
	enumM(enumMconstant),
	enumN(enumNconstant),
	enumP(enumPconstant),
	enumQ(enumQconstant),
	enumR(enumRconstant),
	enumW(enumWzero)
	{
		//Nothing
	}
	std::string outputFileName;
	int seed;
	EnumReproductionMode reproductionMode;
	unsigned int startingPopSize;
	double startingResources;
	unsigned int maxTime;
	double A, B, C;
	double bodySizeAdult;
	ParameterSetD paramsD; EnumD enumD;
	ParameterSetF paramsF; EnumF enumF;
	ParameterSetG paramsG; EnumG enumG;
	ParameterSetM paramsM; EnumM enumM;
	ParameterSetN paramsN; EnumN enumN;
	ParameterSetP paramsP; EnumP enumP;
	ParameterSetQ paramsQ; EnumQ enumQ;
	ParameterSetR paramsR; EnumR enumR;
	ParameterSetW paramsW; EnumW enumW;
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetSimulation& params)
	{
		os
		<< "\n\tOutput file name: " << params.outputFileName
		<< "\n\tRandom number generator seed: " << params.seed
		<< "\n\tStarting PopSize: " << params.startingPopSize
		<< "\n\tStarting resources: " << params.startingResources
		<< "\n\tMax time: " << params.maxTime
		<< "\n\talpha: " << params.A
		<< "\n\tbeta: " << params.B
		<< "\n\tgamma: " << params.C
		<< "\n\tbody size adult: " << params.bodySizeAdult
		<< "\n\tReproductionMode: " << enumReproductionModeToString(params.reproductionMode) << std::endl
		<< '\t' << enumDtoString(params.enumD) << std::endl
		<< params.paramsD << std::endl
		<< '\t' << enumFtoString(params.enumF) << std::endl
		<< params.paramsF << std::endl
		<< '\t' << enumGtoString(params.enumG) << std::endl
		<< params.paramsG << std::endl
		<< '\t' << enumMtoString(params.enumM) << std::endl
		<< params.paramsM << std::endl
		<< '\t' << enumNtoString(params.enumN) << std::endl
		<< params.paramsN << std::endl
		<< '\t' << enumPtoString(params.enumP) << std::endl
		<< params.paramsP << std::endl
		<< '\t' << enumQtoString(params.enumQ) << std::endl
		<< params.paramsQ << std::endl
		<< '\t' << enumRtoString(params.enumR) << std::endl
		<< params.paramsR << std::endl
		<< '\t' << enumWtoString(params.enumW) << std::endl
		<< params.paramsW << std::endl;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const ParameterSetSimulation *params)
	{
		os << *params; return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const std::auto_ptr<ParameterSetSimulation> params)
	{
		os << params.get(); return os;
	}
};

#endif //#ifndef __PARAMETERSETS_H

