/*
 *  Sim4Interpreter.h
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Thu Jun 16 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

///Sim4Interpreter interprets the user's command line input.
///
///The only members it has are mCommands and mOptionsFile.
///mCommands contains the words the user typed.
///mOptionsFile embodies the user's Options file, which can be 
///modified by the user via Sim4Interpreter.

#ifndef __SIM4_INTERPRETER
#define __SIM4_INTERPRETER

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include "OptionsFile.h"
#include "HelperFunctions.h"
#include "StrategyD.h"
#include "StrategyF.h"
#include "StrategyG.h"
#include "StrategyM.h"
#include "StrategyN.h"
#include "StrategyP.h"
#include "StrategyQ.h"
#include "StrategyR.h"
#include "StrategyW.h"

class Sim4Interpreter
{
	public:
	Sim4Interpreter(const int&, char* const []);
	OptionsFile getOptionsFile() const { return mOptionsFile; }

	private:
	
	const std::string mIniFileName;
	OptionsFile mOptionsFile;
	std::string getOptionsFileName() const;
	std::vector<std::string> mCommand;
	std::vector<std::string> mArgv;
	bool mDoExit;

	void setOptionsFileName(const std::string&) const;

	//'show' means that no next words must be interpreted
	void showHelp() const;
	void showHelpOptionFile() const;
	void showHelpSimFile() const;
	void showUses() const; 
	void showOptionsFile() const;
	void showAbout() const; 

	//'interpret' mean that also next words must be interpreted
	void interpretCommandLine();

	//General interface
	void interpretHelp(const unsigned int&) const;
	void interpretUseOptionsFile(const unsigned int&);
	void interpretShowSimFile(const unsigned int&) const;
	void interpretCopyOptionsFile(const unsigned int&) const;
	void interpretCopySimFile(const unsigned int&) const;
	void interpretAddSimFile(const unsigned int&);
	void interpretRemoveSimFile(const unsigned int&);
	void interpretExecute(const unsigned int&);
	void testFunctions() const;
	void extractCov() const;
	//Options File interface
	void interpretSetOutputFileName(const unsigned int&);
	void interpretSetSeed(const unsigned int&);

	void interpretSetWriteOutputFile(const unsigned int&);
	void interpretSetWriteOutput(const unsigned int&);

	void interpretSetText(const unsigned int&);
	void interpretSetPlotting(const unsigned int&);
	void interpretUsesSimFile(const unsigned int&);
	void interpretSetSimTime(const unsigned int&);
	void interpretSetStartPopSize(const unsigned int&);
	void interpretSetStartResources(const unsigned int&);
	void interpretSetBodySizeAdult(const unsigned int&);
	void interpretSetConstA(const unsigned int&);
	void interpretSetConstB(const unsigned int&);
	void interpretSetConstC(const unsigned int&);
	void interpretSetReproductionMode(const unsigned int&);

	//----------------------------------------------------------------------------------
	//
	// COMPUTER GENERATED CODE
	// Sim4Interpreter
	//
	//----------------------------------------------------------------------------------
	void interpretSetDconstA(const unsigned int&);
	void interpretSetFconstA(const unsigned int&);
	void interpretSetGconstA(const unsigned int&);
	void interpretSetMconstA(const unsigned int&);
	void interpretSetNconstA(const unsigned int&);
	void interpretSetPconstA(const unsigned int&);
	void interpretSetQconstA(const unsigned int&);
	void interpretSetRconstA(const unsigned int&);
	void interpretSetWconstA(const unsigned int&);
	void interpretSetDconstB(const unsigned int&);
	void interpretSetFconstB(const unsigned int&);
	void interpretSetGconstB(const unsigned int&);
	void interpretSetMconstB(const unsigned int&);
	void interpretSetNconstB(const unsigned int&);
	void interpretSetPconstB(const unsigned int&);
	void interpretSetQconstB(const unsigned int&);
	void interpretSetRconstB(const unsigned int&);
	void interpretSetWconstB(const unsigned int&);
	void interpretSetDconstC(const unsigned int&);
	void interpretSetFconstC(const unsigned int&);
	void interpretSetGconstC(const unsigned int&);
	void interpretSetMconstC(const unsigned int&);
	void interpretSetNconstC(const unsigned int&);
	void interpretSetPconstC(const unsigned int&);
	void interpretSetQconstC(const unsigned int&);
	void interpretSetRconstC(const unsigned int&);
	void interpretSetWconstC(const unsigned int&);
	void interpretSetDconstD(const unsigned int&);
	void interpretSetFconstD(const unsigned int&);
	void interpretSetGconstD(const unsigned int&);
	void interpretSetMconstD(const unsigned int&);
	void interpretSetNconstD(const unsigned int&);
	void interpretSetPconstD(const unsigned int&);
	void interpretSetQconstD(const unsigned int&);
	void interpretSetRconstD(const unsigned int&);
	void interpretSetWconstD(const unsigned int&);
	void interpretSetDconstE(const unsigned int&);
	void interpretSetFconstE(const unsigned int&);
	void interpretSetGconstE(const unsigned int&);
	void interpretSetMconstE(const unsigned int&);
	void interpretSetNconstE(const unsigned int&);
	void interpretSetPconstE(const unsigned int&);
	void interpretSetQconstE(const unsigned int&);
	void interpretSetRconstE(const unsigned int&);
	void interpretSetWconstE(const unsigned int&);
	void interpretSetD(const unsigned int&);
	void interpretSetF(const unsigned int&);
	void interpretSetG(const unsigned int&);
	void interpretSetM(const unsigned int&);
	void interpretSetN(const unsigned int&);
	void interpretSetP(const unsigned int&);
	void interpretSetQ(const unsigned int&);
	void interpretSetR(const unsigned int&);
	void interpretSetW(const unsigned int&);
};




#endif //#ifndef __SIM4_FLAGS_INTERPRETER


