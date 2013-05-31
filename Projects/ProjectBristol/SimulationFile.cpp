/*
 *  SimulationFile.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Thu Jun 16 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#include "SimulationFile.h"
//----------------------------------------------------------------------------------
//#define EXTREME_LOGGING
//----------------------------------------------------------------------------------
SimulationFile::SimulationFile(const std::string& fileName, const bool& overWrite) :
	mFileName(fileName),
	mVersionName1("V1"), //Do not change
	mVersionName2("V2"), //Do not change
	mCurrentVersionName(mVersionName2) //Change every new version
{		
	//mpVersionNames.reset(new VersionNames);
	//A proper initialization
	/*mParameters.reproductionMode = enumReproductionModeAmount;
	mParameters.seed = 0;
	mParameters.outputFileName = "defaultOutputFile.txt";
	mParameters.startingPopSize = 1000;
	mParameters.startingResources = 0.0;
	mParameters.maxTime = 100;
	mParameters.A = 1.0;
	mParameters.B = 1.0;
	mParameters.C = 1.0;
	mParameters.bodySizeAdult = 10.0;
	mParameters.enumD = enumDconstant;
	mParameters.paramsD.A = 0.05;
	mParameters.paramsD.B = 0.0; 
	mParameters.paramsD.C = 0.0;
	mParameters.paramsD.D = 0.0;
	mParameters.enumF = enumFconstant;
	mParameters.paramsF.A = 0.99;
	mParameters.paramsF.B = 0.0; 
	mParameters.paramsF.C = 0.0; 
	mParameters.paramsF.D = 0.0; 
	mParameters.enumG = enumGfixed;
	mParameters.paramsG.A = 0.5;
	mParameters.paramsG.B = 0.0;
	mParameters.paramsG.C = 0.0;
	mParameters.paramsG.D = 0.0;
	mParameters.enumM = enumMconstant;
	mParameters.paramsM.A = 0.05;
	mParameters.paramsM.B = 0.0;
	mParameters.paramsM.C = 0.0;
	mParameters.paramsM.D = 0.0;
	mParameters.enumN = enumNdefault;
	mParameters.paramsN.A = 1.0;
	mParameters.paramsN.B = 1.0;
	mParameters.paramsN.C = 0.0;
	mParameters.paramsN.D = 0.0;
	mParameters.enumP = enumPconstant;
	mParameters.paramsP.A = 0.5;
	mParameters.paramsP.B = 0.0;
	mParameters.paramsP.C = 0.0;
	mParameters.paramsP.D = 0.0;
	mParameters.enumQ = enumQconstant;
	mParameters.paramsQ.A = 0.5;
	mParameters.paramsQ.B = 0.0;
	mParameters.paramsQ.C = 0.0;
	mParameters.paramsQ.D = 0.0;
	mParameters.enumR = enumRconstant;
	mParameters.paramsR.A = 200.0;
	mParameters.paramsR.B = 0.1;
	mParameters.paramsR.C = 0.0;
	mParameters.paramsR.D = 0.0;
	mParameters.enumW = enumWZero;
	mParameters.paramsW.A = 0.0;
	mParameters.paramsW.B = 0.0;
	mParameters.paramsW.C = 0.0;
	mParameters.paramsW.D = 0.0;*/
	enumsToStrings();


	if (fileExists(mFileName)==true) 
	{
		dot("Config file '"+mFileName+"' found.");
		if (overWrite==false) 
		{ 
			readFromFile(); 
			dot("Loaded '"+mFileName+"' successfully.");
			return; 
		}
	}
	writeToFile();
	if (overWrite==true) 
	{
		dot("Overwritten '"+mFileName+"' successfully.");
	}
	else
	{
		dot("Config file '"+mFileName+"' not found, now created.");
	}
}
//----------------------------------------------------------------------------------
void SimulationFile::writeToFile()
{
	dot(mParameters.outputFileName);
	enumsToStrings();
	assert(mCurrentVersionName == mVersionName2);
	std::ofstream file;
	file.open(mFileName.c_str());
	file 
		<<  mCurrentVersionName << '\n'
		<<  mParameters.outputFileName << '\n'
		<<  mParameters.seed << '\n'
		<<  mParameters.startingPopSize << '\n'
		<<  mParameters.startingResources << '\n'
		<<  mParameters.maxTime << '\n'
		<<  mParameters.A << '\n'
		<<  mParameters.B << '\n'
		<<  mParameters.C << '\n'
		<<  mParameters.bodySizeAdult << '\n'
		<<  enumDstring << '\n'
		<<  mParameters.paramsD.A << '\n'
		<<  mParameters.paramsD.B << '\n'
		<<  mParameters.paramsD.C << '\n'
		<<  mParameters.paramsD.D << '\n'
		<<  mParameters.paramsD.E << '\n'
		<<  enumFstring << '\n'
		<<  mParameters.paramsF.A << '\n'
		<<  mParameters.paramsF.B << '\n'
		<<  mParameters.paramsF.C << '\n'
		<<  mParameters.paramsF.D << '\n'
		<<  mParameters.paramsF.E << '\n'
		<<  enumGstring << '\n'
		<<  mParameters.paramsG.A << '\n'
		<<  mParameters.paramsG.B << '\n'
		<<  mParameters.paramsG.C << '\n'
		<<  mParameters.paramsG.D << '\n'
		<<  mParameters.paramsG.E << '\n'
		<<  enumMstring << '\n'
		<<  mParameters.paramsM.A << '\n'
		<<  mParameters.paramsM.B << '\n'
		<<  mParameters.paramsM.C << '\n'
		<<  mParameters.paramsM.D << '\n'
		<<  mParameters.paramsM.E << '\n'
		<<  enumNstring << '\n'
		<<  mParameters.paramsN.A << '\n'
		<<  mParameters.paramsN.B << '\n'
		<<  mParameters.paramsN.C << '\n'
		<<  mParameters.paramsN.D << '\n'
		<<  mParameters.paramsN.E << '\n'
		<<  enumPstring << '\n'
		<<  mParameters.paramsP.A << '\n'
		<<  mParameters.paramsP.B << '\n'
		<<  mParameters.paramsP.C << '\n'
		<<  mParameters.paramsP.D << '\n'
		<<  mParameters.paramsP.E << '\n'
		<<  enumQstring << '\n'
		<<  mParameters.paramsQ.A << '\n'
		<<  mParameters.paramsQ.B << '\n'
		<<  mParameters.paramsQ.C << '\n'
		<<  mParameters.paramsQ.D << '\n'
		<<  mParameters.paramsQ.E << '\n'
		<<  enumRstring << '\n'
		<<  mParameters.paramsR.A << '\n'
		<<  mParameters.paramsR.B << '\n'
		<<  mParameters.paramsR.C << '\n'
		<<  mParameters.paramsR.D << '\n'
		<<  mParameters.paramsR.E << '\n'
		<<  enumWstring << '\n'
		<<  mParameters.paramsW.A << '\n'
		<<  mParameters.paramsW.B << '\n'
		<<  mParameters.paramsW.C << '\n'
		<<  mParameters.paramsW.D << '\n'
		<<  mParameters.paramsW.E << '\n'
		<<  enumReproductionModeString << '\n'
		<<  mFlag
		<< std::endl;
	file.close();
}
//----------------------------------------------------------------------------------
void SimulationFile::readFromFile()
{ 
	if (fileExists(mFileName)==false)
	{
		std::cout << "File '" << mFileName << "' does not exist. " << std::endl;
		exit(0);
	}

	//Read version
	std::string versionName = "NOTHING";
	{
		std::ifstream file;
		file.open(mFileName.c_str());
		file >>  versionName;
		file.close();
	}
	assert(versionName!="NOTHING");
	
	//Do the real reading of a file, dependent on the version
	if (versionName==mVersionName2) readFromFile2();
	else if (versionName==mVersionName1) readFromFile1();
	else readFromFile0();
	

	stringsToEnums();
}
//----------------------------------------------------------------------------------
///Reads a SimFile V2.0
void SimulationFile::readFromFile2()
{
	std::string versionNameDummy; //Do not want to write to mpVersionNames, therefore use dummy
	std::ifstream file;
	file.open(mFileName.c_str());
	file 
		>>  versionNameDummy //Write to dummy mpVersionNames->versionName1
		>>  mParameters.outputFileName
		>>  mParameters.seed
		>>  mParameters.startingPopSize
		>>  mParameters.startingResources
		>>  mParameters.maxTime
		>>  mParameters.A
		>>  mParameters.B
		>>  mParameters.C
		>>  mParameters.bodySizeAdult
		>>  enumDstring
		>>  mParameters.paramsD.A
		>>  mParameters.paramsD.B 
		>>  mParameters.paramsD.C
		>>  mParameters.paramsD.D
		>>  mParameters.paramsD.E
		>>  enumFstring
		>>  mParameters.paramsF.A
		>>  mParameters.paramsF.B 
		>>  mParameters.paramsF.C
		>>  mParameters.paramsF.D
		>>  mParameters.paramsF.E
		>>  enumGstring
		>>  mParameters.paramsG.A
		>>  mParameters.paramsG.B 
		>>  mParameters.paramsG.C
		>>  mParameters.paramsG.D
		>>  mParameters.paramsG.E
		>>  enumMstring
		>>  mParameters.paramsM.A
		>>  mParameters.paramsM.B 
		>>  mParameters.paramsM.C
		>>  mParameters.paramsM.D
		>>  mParameters.paramsM.E
		>>  enumNstring
		>>  mParameters.paramsN.A
		>>  mParameters.paramsN.B 
		>>  mParameters.paramsN.C
		>>  mParameters.paramsN.D
		>>  mParameters.paramsN.E
		>>  enumPstring
		>>  mParameters.paramsP.A
		>>  mParameters.paramsP.B 
		>>  mParameters.paramsP.C
		>>  mParameters.paramsP.D
		>>  mParameters.paramsP.E
		>>  enumQstring
		>>  mParameters.paramsQ.A
		>>  mParameters.paramsQ.B 
		>>  mParameters.paramsQ.C
		>>  mParameters.paramsQ.D
		>>  mParameters.paramsQ.E
		>>  enumRstring
		>>  mParameters.paramsR.A
		>>  mParameters.paramsR.B 
		>>  mParameters.paramsR.C
		>>  mParameters.paramsR.D
		>>  mParameters.paramsR.E
		>>  enumWstring
		>>  mParameters.paramsW.A
		>>  mParameters.paramsW.B
		>>  mParameters.paramsW.C
		>>  mParameters.paramsW.D
		>>  mParameters.paramsW.E
		>>  enumReproductionModeString
		>>  mFlag
		; //End of reading
	assert(versionNameDummy == mVersionName2); //Check dummy
	file.close();
}
//----------------------------------------------------------------------------------
///Reads a SimFile V1.0
void SimulationFile::readFromFile1()
{
	std::string versionNameDummy; //Do not want to write to mpVersionNames, therefore use dummy
	std::ifstream file;
	file.open(mFileName.c_str());
	file 
		>>  versionNameDummy //Write to dummy mpVersionNames->versionName1
		>>  mParameters.outputFileName
		>>  mParameters.seed
		>>  mParameters.startingPopSize
		>>  mParameters.startingResources
		>>  mParameters.maxTime
		>>  mParameters.A
		>>  mParameters.B
		>>  mParameters.C
		>>  mParameters.bodySizeAdult
		>>  enumDstring
		>>  mParameters.paramsD.A
		>>  mParameters.paramsD.B 
		>>  mParameters.paramsD.C
		>>  mParameters.paramsD.D
		>>  enumFstring
		>>  mParameters.paramsF.A
		>>  mParameters.paramsF.B 
		>>  mParameters.paramsF.C
		>>  mParameters.paramsF.D
		>>  enumGstring
		>>  mParameters.paramsG.A
		>>  mParameters.paramsG.B 
		>>  mParameters.paramsG.C
		>>  mParameters.paramsG.D
		>>  enumMstring
		>>  mParameters.paramsM.A
		>>  mParameters.paramsM.B 
		>>  mParameters.paramsM.C
		>>  mParameters.paramsM.D
		>>  enumNstring
		>>  mParameters.paramsN.A
		>>  mParameters.paramsN.B 
		>>  mParameters.paramsN.C
		>>  mParameters.paramsN.D
		>>  enumPstring
		>>  mParameters.paramsP.A
		>>  mParameters.paramsP.B 
		>>  mParameters.paramsP.C
		>>  mParameters.paramsP.D
		>>  enumQstring
		>>  mParameters.paramsQ.A
		>>  mParameters.paramsQ.B 
		>>  mParameters.paramsQ.C
		>>  mParameters.paramsQ.D
		>>  enumRstring
		>>  mParameters.paramsR.A
		>>  mParameters.paramsR.B 
		>>  mParameters.paramsR.C
		>>  mParameters.paramsR.D
		>>  enumWstring
		>>  mParameters.paramsW.A
		>>  mParameters.paramsW.B
		>>  mParameters.paramsW.C
		>>  mParameters.paramsW.D
		>>  enumReproductionModeString
		>>  mFlag
		; //End of reading
	assert(versionNameDummy == mVersionName1); //Check dummy
	file.close();
}
//----------------------------------------------------------------------------------
///Reads a SimFile before V1.0
void SimulationFile::readFromFile0()
{
	std::ifstream file;
	file.open(mFileName.c_str());
	file 
		>>  mParameters.outputFileName
		>>  mParameters.startingPopSize
		>>  mParameters.startingResources
		>>  mParameters.maxTime
		>>  mParameters.A
		>>  mParameters.B
		>>  mParameters.C
		>>  mParameters.bodySizeAdult
		>>  enumDstring
		>>  mParameters.paramsD.A
		>>  mParameters.paramsD.B 
		>>  mParameters.paramsD.C
		>>  mParameters.paramsD.D
		>>  enumFstring
		>>  mParameters.paramsF.A
		>>  mParameters.paramsF.B 
		>>  mParameters.paramsF.C
		>>  mParameters.paramsF.D
		>>  enumGstring
		>>  mParameters.paramsG.A
		>>  mParameters.paramsG.B 
		>>  mParameters.paramsG.C
		>>  mParameters.paramsG.D
		>>  enumMstring
		>>  mParameters.paramsM.A
		>>  mParameters.paramsM.B 
		>>  mParameters.paramsM.C
		>>  mParameters.paramsM.D
		>>  enumNstring
		>>  mParameters.paramsN.A
		>>  mParameters.paramsN.B 
		>>  mParameters.paramsN.C
		>>  mParameters.paramsN.D
		>>  enumPstring
		>>  mParameters.paramsP.A
		>>  mParameters.paramsP.B 
		>>  mParameters.paramsP.C
		>>  mParameters.paramsP.D
		>>  enumQstring
		>>  mParameters.paramsQ.A
		>>  mParameters.paramsQ.B 
		>>  mParameters.paramsQ.C
		>>  mParameters.paramsQ.D
		>>  enumRstring
		>>  mParameters.paramsR.A
		>>  mParameters.paramsR.B 
		>>  mParameters.paramsR.C
		>>  mParameters.paramsR.D
		>>  enumWstring
		>>  mParameters.paramsW.A
		>>  mParameters.paramsW.B
		>>  mParameters.paramsW.C
		>>  mParameters.paramsW.D
		>>  enumReproductionModeString
		>>  mFlag
		; //End of reading
	file.close();
}
//----------------------------------------------------------------------------------
void SimulationFile::coutAll() const
{
	std::cout << mParameters << std::endl;
}
//----------------------------------------------------------------------------------
void SimulationFile::stringsToEnums()
{
	mParameters.enumD = stringToEnumD(enumDstring);
	mParameters.enumF = stringToEnumF(enumFstring);
	mParameters.enumG = stringToEnumG(enumGstring);
	mParameters.enumM = stringToEnumM(enumMstring);
	mParameters.enumN = stringToEnumN(enumNstring);
	mParameters.enumP = stringToEnumP(enumPstring);
	mParameters.enumQ = stringToEnumQ(enumQstring);
	mParameters.enumR = stringToEnumR(enumRstring);
	mParameters.enumW = stringToEnumW(enumWstring);
	mParameters.reproductionMode = stringToEnumReproductionMode(enumReproductionModeString);
}
//----------------------------------------------------------------------------------
void SimulationFile::enumsToStrings()
{
	enumDstring = enumDtoString(mParameters.enumD);
	enumFstring = enumFtoString(mParameters.enumF);
	enumGstring = enumGtoString(mParameters.enumG);
	enumMstring = enumMtoString(mParameters.enumM);
	enumNstring = enumNtoString(mParameters.enumN);
	enumPstring = enumPtoString(mParameters.enumP);
	enumQstring = enumQtoString(mParameters.enumQ);
	enumRstring = enumRtoString(mParameters.enumR);
	enumWstring = enumWtoString(mParameters.enumW);
	enumReproductionModeString = enumReproductionModeToString(mParameters.reproductionMode);
}

//----------------------------------------------------------------------------------
void SimulationFile::setD(const EnumD& enumD)
{
	mParameters.enumD = enumD;
	enumDstring = enumDtoString(mParameters.enumD);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setF(const EnumF& enumF)
{
	mParameters.enumF = enumF;
	enumFstring = enumFtoString(mParameters.enumF);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setG(const EnumG& enumG)
{
	mParameters.enumG = enumG;
	enumGstring = enumGtoString(mParameters.enumG);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setM(const EnumM& enumM)
{
	mParameters.enumM = enumM;
	enumMstring = enumMtoString(mParameters.enumM);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setN(const EnumN& enumN)
{
	mParameters.enumN = enumN;
	enumNstring = enumNtoString(mParameters.enumN);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setP(const EnumP& enumP)
{
	mParameters.enumP = enumP;
	enumPstring = enumPtoString(mParameters.enumP);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setQ(const EnumQ& enumQ)
{
	mParameters.enumQ = enumQ;
	enumQstring = enumQtoString(mParameters.enumQ);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setR(const EnumR& enumR)
{
	mParameters.enumR = enumR;
	enumRstring = enumRtoString(mParameters.enumR);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setW(const EnumW& enumW)
{
	mParameters.enumW = enumW;
	enumWstring = enumWtoString(mParameters.enumW);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setDparams(const ParameterSetD& params)
{
	mParameters.paramsD = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setFparams(const ParameterSetF& params)
{
	mParameters.paramsF = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setGparams(const ParameterSetG& params)
{
	mParameters.paramsG = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setMparams(const ParameterSetM& params)
{
	mParameters.paramsM = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setNparams(const ParameterSetN& params)
{
	mParameters.paramsN = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setPparams(const ParameterSetP& params)
{
	mParameters.paramsP = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setQparams(const ParameterSetQ& params)
{
	mParameters.paramsQ = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setRparams(const ParameterSetR& params)
{
	mParameters.paramsR = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setWParams(const ParameterSetW& params)
{
	mParameters.paramsW = params;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setOutputFileName(const std::string& outputFileName)
{
	dot("\nSetting to outputFileName: "+outputFileName);
	mParameters.outputFileName = outputFileName;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setSeed(const unsigned int& seed)
{
	mParameters.seed = seed;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setMaxTime(const unsigned int& time)
{
	mParameters.maxTime = time;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setStartPopSize(const unsigned int& popSize)
{
	mParameters.startingPopSize = popSize;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setStartResources(const double& resources)
{
	mParameters.startingResources = resources;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setBodySizeAdult(const double& bodySize)
{
	mParameters.bodySizeAdult = bodySize;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setConstA(const double& constA)
{
	mParameters.A = constA;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setConstB(const double& constB)
{
	mParameters.B = constB;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setConstC(const double& constC)
{
	mParameters.C = constC;
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setReproductionMode(const EnumReproductionMode & reproductionMode)
{
	mParameters.reproductionMode = reproductionMode;
	enumReproductionModeString = enumReproductionModeToString(mParameters.reproductionMode);
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::setFlag(const int& value) 
{ 
	mFlag = value; 
	writeToFile();
}
//----------------------------------------------------------------------------------
void SimulationFile::showUser() const
{
	std::cout << "\n\tShowing Simulation File '" << mFileName << "':\n"
		<< mParameters << std::endl;
}
//----------------------------------------------------------------------------------
void SimulationFile::cout(const std::string& logMessage) const
{
	std::cout << "LOG: " << logMessage << std::endl;
}
//----------------------------------------------------------------------------------
void SimulationFile::dot(const std::string& errorMessage) const
{
	#ifdef EXTREME_LOGGING
	std::cout << "DOT: " << errorMessage << std::endl;
	#endif
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
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

