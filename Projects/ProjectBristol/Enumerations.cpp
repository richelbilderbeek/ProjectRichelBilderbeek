/*
 *  Enumerations.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue Jun 07 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#include "Enumerations.h"
//----------------------------------------------------------------------------------
// EnumD
//----------------------------------------------------------------------------------
std::string enumDtoString(const EnumD& enumD)
{
	switch(enumD)
	{
		case enumDdefault: return "enumDdefault";
		//case enumDsizeOnly: return "enumDsizeOnly";
		//case enumDconstant: return "enumDconstant";
	}
	assert(!"ERROR in 'std::string enumDToString(const EnumD& enumD)'");
	exit(1);

}
//----------------------------------------------------------------------------------
EnumD stringToEnumD(const std::string& myString)
{
	if (myString=="enumDdefault") return enumDdefault;
	//if (myString=="enumDsizeOnly") return enumDsizeOnly;
	if (myString=="enumDconstant") return enumDdefault; //Backwards compatible
	assert(!"ERROR in 'EnumD StringToEnumD(const std::string& myString)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumD userInputToEnumD(const int& index)
{
	switch(index)
	{
		case 0: return enumDdefault;
		//case 1: return enumDconstant;
		//case 2: return enumDsizeOnly;
	}
	assert(!"Unknown index in userInputToEnumD");
	exit(1);
}
//----------------------------------------------------------------------------------
// EnumF
//----------------------------------------------------------------------------------
std::string enumFtoString(const EnumF& enumF)
{
	switch(enumF)
	{
		//case enumFgauss: return "enumFgauss";
		case enumFdefault: return "enumFdefault";
		//case enumFconstant: return "enumFconstant";
	}
	assert(!"ERROR in 'std::string enumFToString(const EnumF& enumF)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumF stringToEnumF(const std::string& myString)
{
	//if (myString=="enumFgauss") return enumFgauss;
	if (myString=="enumFdefault") return enumFdefault;
	if (myString=="enumFconstant") return enumFdefault;
	std::cout << "ERROR: myString equals: " << myString << std::endl;
	assert(!"ERROR in 'EnumF StringToEnumF(const std::string& myString)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumF userInputToEnumF(const int& index)
{
	switch(index)
	{
//		case 0: return enumFconstant;
		case 0: return enumFdefault;
//		case 2: return enumFgauss;
	}
	assert(!"Unknown index in userInputToEnumF");
	exit(1);
}
//----------------------------------------------------------------------------------
// EnumG
//----------------------------------------------------------------------------------
std::string enumGtoString(const EnumG& enumG)
{
	switch(enumG)
	{
		case enumGplastic: return "enumGplastic";
		case enumGconstant: return "enumGconstant";
	}
	assert(!"ERROR in 'std::string enumGToString(const EnumG& enumG)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumG stringToEnumG(const std::string& myString)
{
	if (myString=="enumGplastic") return enumGplastic;
	if (myString=="enumGconstant") return enumGconstant;
	if (myString=="enumGfixed") return enumGconstant; //Backwards compatible
	assert(!"ERROR in 'EnumG StringToEnumG(const std::string& myString)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumG userInputToEnumG(const int& index)
{
	switch(index)
	{
		case 0: return enumGconstant;
		case 1: return enumGplastic;
	}
	assert(!"Unknown index in userInputToEnumG");
	exit(1);
}
//----------------------------------------------------------------------------------
// EnumM
//----------------------------------------------------------------------------------
std::string enumMtoString(const EnumM& enumM)
{
	switch(enumM)
	{
		case enumMdefault : return "enumMdefault";
		case enumMconstant: return "enumMconstant";
		//case enumMzero: return "enumMzero";
	}
	assert(!"std::string enumMtoString(const EnumM& enumM)");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumM stringToEnumM(const std::string& myString)
{
	if (myString=="enumMdefault") return enumMdefault;
	if (myString=="enumMconstant") return enumMconstant;
	assert(!"EnumM StringToEnumM(const std::string& myString)");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumM userInputToEnumM(const int& index)
{
	switch(index)
	{
		case 0: return enumMconstant;
		case 1: return enumMdefault;
	}
	assert(!"Unknown index in userInputToEnumM");
	exit(1);
}
//----------------------------------------------------------------------------------
// EnumN
//----------------------------------------------------------------------------------
std::string enumNtoString(const EnumN& enumN)
{
	switch(enumN)
	{
		case enumNplastic : return "enumNplastic";
		case enumNconstant: return "enumNconstant";
	}
	assert(!"Unknown value of enumN");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumN stringToEnumN(const std::string& myString)
{
	if (myString=="enumNplastic") return enumNplastic;
	if (myString=="enumNconstant") return enumNconstant;
	if (myString=="enumNdefault") return enumNplastic; //Backwards compatibility
	std::cout << "ERROR: myString equals: " << myString << std::endl;
	assert(!("Cannot convert myString to enumN"));
	exit(1);
}
//----------------------------------------------------------------------------------
EnumN userInputToEnumN(const int& index)
{
	switch(index)
	{
		case 0: return enumNplastic;
		case 1: return enumNconstant;
	}
	assert(!"Unknown index in userInputToEnumN");
	exit(1);
}
//----------------------------------------------------------------------------------
// EnumP
//----------------------------------------------------------------------------------
std::string enumPtoString(const EnumP& enumP)
{
	switch(enumP)
	{
		case enumPplastic: return "enumPplastic";
		//case enumPplasticB: return "enumPplasticB";
		//case enumPnonPlastic: return "enumPnonPlastic";
		case enumPconstant: return "enumPconstant";
	}
	assert(!"ERROR in 'std::string enumPToString(const EnumP& enumP)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumP stringToEnumP(const std::string& myString)
{
	if (myString=="enumPplastic") return enumPplastic;
	//if (myString=="enumPplasticB") return enumPplasticB;
	//if (myString=="enumPnonPlastic") return enumPnonPlastic;
	if (myString=="enumPconstant") return enumPconstant; //Backwards compatible
	if (myString=="enumPplastic") return enumPplastic; //Backwards compatible
	std::cout << "ERROR in 'EnumP StringToEnumP(const std::string& myString)'" << std::endl;
	std::cout << myString << std::endl;
	exit(1);
}
//----------------------------------------------------------------------------------
EnumP userInputToEnumP(const int& index)
{
	switch(index)
	{
		case 0: return enumPconstant;
		case 1: return enumPplastic;
//		case 2: return enumPplasticB;
	}
	assert(!"Unknown index in userInputToEnump");
	exit(1);
}
//----------------------------------------------------------------------------------
//  EnumQ
//----------------------------------------------------------------------------------
std::string enumQtoString(const EnumQ& enumQ)
{
	switch(enumQ)
	{
		case enumQdefault: return "enumQdefault";
		case enumQconstant: return "enumQconstant";
	}
	assert(!"ERROR in 'std::string enumQToString(const EnumQ& enumQ)'");
	exit(1);
	
}
//----------------------------------------------------------------------------------
EnumQ stringToEnumQ(const std::string& myString)
{
	if (myString=="enumQdefault") return enumQdefault;
	if (myString=="enumQconstant") return enumQconstant;
	assert(!"ERROR in 'EnumQ StringToEnumQ(const std::string& myString)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumQ userInputToEnumQ(const int& index)
{
	switch(index)
	{
		case 0: return enumQconstant;
		case 1: return enumQdefault;
	}
	assert(!"Unknown index in userInputToEnumQ");
	exit(1);
}
//----------------------------------------------------------------------------------
//  EnumR
//----------------------------------------------------------------------------------
std::string enumRtoString(const EnumR& enumR)
{
	switch(enumR)
	{
		case enumRconstant: return "enumRconstant";
		case enumRlogistic: return "enumRlogistic";
		case enumRcosine  : return "enumRcosine";
	}
	assert(!"ERROR in 'std::string enumRToString(const EnumR& enumR)'");
	exit(1);

}
//----------------------------------------------------------------------------------
EnumR stringToEnumR(const std::string& myString)
{
	if (myString=="enumRconstant") return enumRconstant;
	if (myString=="enumRlogistic") return enumRlogistic;
	if (myString=="enumRcosine") return enumRcosine;
	assert(!"ERROR in 'EnumR StringToEnumR(const std::string& myString)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumR userInputToEnumR(const int& index)
{
	switch(index)
	{
		case 0: return enumRconstant;
		case 1: return enumRlogistic;
		case 2: return enumRcosine;
	}
	assert(!"Unknown index in userInputToEnumR");
	exit(1);
}
//----------------------------------------------------------------------------------
//  EnumW
//----------------------------------------------------------------------------------
std::string enumWtoString(const EnumW& enumW)
{
	switch(enumW)
	{
		case enumWzero: return "enumWzero";
		case enumWuniform: return "enumWuniform";
	}
	assert(!"ERROR in 'std::string enumWToString(const EnumW& enumW)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumW stringToEnumW(const std::string& myString)
{
	if (myString=="enumWzero") return enumWzero;
	if (myString=="enumWuniform") return enumWuniform;
	if (myString=="enumWZero") return enumWzero; //Backwards compampatible
	if (myString=="enumWUniform") return enumWuniform; //Backwards compatible
	if (myString=="enumSigmaZero") return enumWzero; //Backwards compatible
	if (myString=="enumSigmaUniform") return enumWuniform; //Backwards compatible

	std::cout << "ERROR: myString: '"<< myString << "'" << std::endl;
	assert(!"Unknown myString for EnumW");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumW userInputToEnumW(const int& index)
{
	switch(index)
	{
		case 0: return enumWzero;
		case 1: return enumWuniform;
	}
	assert(!"Unknown index in userInputToEnumW");
	exit(1);
}
//----------------------------------------------------------------------------------
// EnumReproductionMode
//----------------------------------------------------------------------------------
std::string enumReproductionModeToString(const EnumReproductionMode& enumReproductionMode)
{
	switch(enumReproductionMode)
	{
		case enumReproductionModeFraction: return "enumReproductionModeFraction";
		case enumReproductionModeAmount: return "enumReproductionModeAmount";
	}
	assert(!"Unknown enumReproductionMode");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumReproductionMode stringToEnumReproductionMode(const std::string& myString)
{
	if (myString=="enumReproductionModeFraction") return enumReproductionModeFraction;
	if (myString=="enumReproductionModeAmount") return enumReproductionModeAmount;
	std::cout << "ERROR: myString: '"<< myString << "'" << std::endl;
	assert(!"Unknown myString for EnumReprodictionMode");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumReproductionMode userInputToEnumReproductionMode(const int& index)
{
	switch(index)
	{
		case 0: return enumReproductionModeFraction;
		case 1: return enumReproductionModeAmount;
	}
	assert(!"Unknown index in userInputToEnumReproductionMode");
	exit(1);
}
//----------------------------------------------------------------------------------
//  EnumInitializationMode
//----------------------------------------------------------------------------------
std::string enumInitializationModetoString(const EnumInitializationMode& enumInitializationMode)
{
	switch(enumInitializationMode)
	{
		case enumInitializationModeSame: return "enumInitializationModeSame";
		case enumInitializationModeUniform: return "enumInitializationModeUniform";
	}
	assert(!"ERROR in 'std::string enumInitializationModeToString(const EnumInitializationMode& enumInitializationMode)'");
	exit(1);
}
//----------------------------------------------------------------------------------
EnumInitializationMode stringToEnumInitializationMode(const std::string& myString)
{
	if (myString=="enumInitializationModeSame") return enumInitializationModeSame;
	if (myString=="enumInitializationModeUniform") return enumInitializationModeUniform;
	std::cout << "ERROR in 'EnumInitializationMode StringToEnumInitializationMode(const std::string& myString)'" << std::endl;
	exit(1);
}
//----------------------------------------------------------------------------------
//  EnumConclusion
//----------------------------------------------------------------------------------
std::string enumConclusionToString(const EnumConclusion& conclusion)
{
	switch (conclusion)
	{
		case CcNoError: 
			return "No error";
		case CcPopExtinct : 
			return "Population went extinct";
		case CcPopSizeTooBig : 
			return "Population size got too big";
		case CcNoffspringTooBigSingleParent : 
			return "A single parent created too much offspring, in G: increase a";
		case CcNoffspringTooBigAllParents : 
			return "All parents together created too much offspring, in G: increase a";
		case CcNoOffspringProduced :
			return "No offspring produced";
		case CcMeanPopSizeSmall:
			return "Mean population size was small";
		case CcMeanPopSizeLarge:
			return "Mean population size was large";
		case CcMeanBodySizeSmall:
			return "Mean Body size remained small";
		case CcMeanBodySizeLarge:
			return "Mean Body size remained large";
		case CcChanceToDieSmall:
			return "Mean chance to die small, in D: increase a and c, decrease b";
		case CcChanceToDieLarge:
			return "Mean chance to die large, in D: decrease a and c, increase b";
		case CcFractionBiomassPerOffspringInitialLarge:
			return "Mean Fraction Biomass Per Offspring Initail Large, decrease G, by decreasing a";

	}
	assert(!"UNKNOWN Enum used in EnumConclusionToString");
	exit(1);

}
//----------------------------------------------------------------------------------
void coutConclusions(std::vector<EnumConclusion>& conclusions)
{
	const unsigned int nConclusions = conclusions.size();
	std::cout << "Drawing " << nConclusions << " conclusions..." << std::endl;
	for (unsigned int i = 0; i<nConclusions; ++i)
	{
		std::cout << enumConclusionToString(conclusions[i]) << std::endl;
	}
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------



