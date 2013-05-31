/*
 *  Enumerations.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Wed Jun 01 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#ifndef __ENUMERATIONS_H
#define __ENUMERATIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

enum EnumD
{
	enumDdefault
};

enum EnumF
{
	enumFdefault
};

enum EnumG
{
	enumGplastic,
	enumGconstant
};

enum EnumM
{
	enumMdefault,
	enumMconstant
};

enum EnumN
{
	enumNplastic,
	enumNconstant
};

std::string enumNtoString(const EnumN&);
EnumN stringToEnumN(const std::string&);

enum EnumP
{
	enumPplastic,
	enumPconstant
};

enum EnumQ
{
	enumQdefault,
	enumQconstant
};


enum EnumR
{
	enumRconstant,
	enumRlogistic,
	enumRcosine
};

enum EnumW
{
	enumWzero,
	enumWuniform
};

enum EnumReproductionMode
{
	enumReproductionModeFraction,
	enumReproductionModeAmount
};

enum EnumInitializationMode
{
	enumInitializationModeSame,
	enumInitializationModeUniform
};

std::string enumInitializationModetoString(const EnumInitializationMode&);
EnumInitializationMode stringToEnumInitializationMode(const std::string&);



enum EnumConclusion
{
	CcNoError,
	CcNoOffspringProduced,
	CcPopExtinct,
	CcPopSizeTooBig,
	CcNoffspringTooBigSingleParent,
	CcNoffspringTooBigAllParents,
	CcMeanPopSizeSmall,
	CcMeanPopSizeLarge,
	CcMeanBodySizeSmall,
	CcMeanBodySizeLarge,
	CcChanceToDieSmall,
	CcChanceToDieLarge,
	CcFractionBiomassPerOffspringInitialLarge
};


enum EnumErrorCode
{
	EcNoError,
	EcPopExtinct,
	EcPopSizeTooBig,
	EcNoffspringTooBigSingleParent,
	EcNoffspringTooBigAllParents
};

std::string enumDtoString(const EnumD&);
std::string enumFtoString(const EnumF&);
std::string enumGtoString(const EnumG&);
std::string enumMtoString(const EnumM&);
std::string enumPtoString(const EnumP&);
std::string enumQtoString(const EnumQ&);
std::string enumRtoString(const EnumR&);
std::string enumWtoString(const EnumW&);
std::string enumConclusionToString(const EnumConclusion&);
std::string enumReproductionModeToString(const EnumReproductionMode&);

EnumD stringToEnumD(const std::string&);
EnumF stringToEnumF(const std::string&);
EnumG stringToEnumG(const std::string&);
EnumM stringToEnumM(const std::string&);
EnumP stringToEnumP(const std::string&);
EnumQ stringToEnumQ(const std::string&);
EnumR stringToEnumR(const std::string&);
EnumW stringToEnumW(const std::string&);
EnumReproductionMode stringToEnumReproductionMode(const std::string&);

EnumD userInputToEnumD(const int&);
EnumF userInputToEnumF(const int&);
EnumG userInputToEnumG(const int&);
EnumM userInputToEnumM(const int&);
EnumN userInputToEnumN(const int&);
EnumP userInputToEnumP(const int&);
EnumQ userInputToEnumQ(const int&);
EnumR userInputToEnumR(const int&);
EnumW userInputToEnumW(const int&);
EnumReproductionMode userInputToEnumReproductionMode(const int&);

//Misc
void coutConclusions(std::vector<EnumConclusion>&);



#endif //#ifndef __ENUMERATIONS_H

