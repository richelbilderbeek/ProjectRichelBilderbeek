/*
 *  Sim4Interpreter.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Thu Jun 16 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#include "Sim4Interpreter.h"
//----------------------------------------------------------------------------------
Sim4Interpreter::Sim4Interpreter(const int& argc, char* const argv[]) :
	mIniFileName("Sim4.ini"),
	mOptionsFile(getOptionsFileName()),
	mDoExit(false)
{
	//Convert char* to std::string in uppercase as commands
	//Keep a backup (for e.g. filenames) in mArgv.
	mCommand.resize(argc);
	mArgv.resize(argc);
	for (int i=0; i<argc; ++i) 
	{
		mArgv[i]    = argv[i];
		mCommand[i] = stringToUpper(argv[i]);
	}
	//Interpret it
	interpretCommandLine();
}
//----------------------------------------------------------------------------------
std::string Sim4Interpreter::getOptionsFileName() const
{
	if (fileExists(mIniFileName)==false)
	{
		std::ofstream fileOutput(mIniFileName.c_str());
		const std::string optionsFileName = "defaultOptionsFile.txt";
		fileOutput << optionsFileName << '\n';
		fileOutput.close();
		return optionsFileName;
	}
	else
	{
		std::ifstream fileInput(mIniFileName.c_str());
		assert(fileInput.is_open()==true);
		std::string optionsFileName;
		fileInput >> optionsFileName;
		fileInput.close();
		return optionsFileName;
	}
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretCommandLine()
{
	const unsigned int nCommands = mCommand.size();
	if (nCommands==1) 
	{
		//Just run the simulation...
		return;
	}
	
	
	for (unsigned int i = 0; i<nCommands; ++i)
	{
		std::cout << "Now interpreting: " << mCommand[i] << std::endl;
		if (mCommand[i]=="RUN" or mDoExit==true) 
		{
			std::cout << "STARTING SIMULATION(S) NOW." << std::endl;
			return;
		}
		//if (mCommand[i]=="NOEXIT") doExit=false;
		//Help
		if (mCommand[i]=="HELP")  interpretHelp(i);
		if (mCommand[i]=="-HELP") interpretHelp(i);
		if (mCommand[i]=="-?")    interpretHelp(i); 
		if (mCommand[i]=="?")     interpretHelp(i);
		//General interface
		if (mCommand[i]=="ABOUT") showAbout();
		if (mCommand[i]=="ADDSIMFILE") interpretAddSimFile(i);
		if (mCommand[i]=="ASF") interpretAddSimFile(i);
		if (mCommand[i]=="COPYOPTIONFILE") interpretCopyOptionsFile(i);
		if (mCommand[i]=="COF") interpretCopyOptionsFile(i);
		if (mCommand[i]=="COPYOPTIONSFILE") interpretCopyOptionsFile(i);
		if (mCommand[i]=="COPYSIMFILE") interpretCopySimFile(i);
		if (mCommand[i]=="CSF") interpretCopySimFile(i);
		if (mCommand[i]=="REMOVESIMFILE") interpretRemoveSimFile(i);
		if (mCommand[i]=="RSF") interpretRemoveSimFile(i);
		if (mCommand[i]=="SHOWOPTIONSFILE") showOptionsFile(); 
		if (mCommand[i]=="SHOWOPTIONFILE") showOptionsFile(); 
		if (mCommand[i]=="SOF") showOptionsFile(); 
		if (mCommand[i]=="SHOWSIMFILE") interpretShowSimFile(i);
		if (mCommand[i]=="SSF") interpretShowSimFile(i);
		if (mCommand[i]=="SHOWUSES") showUses(); 
		if (mCommand[i]=="SU") showUses(); 
		if (mCommand[i]=="USEOPTIONFILE") interpretUseOptionsFile(i);
		if (mCommand[i]=="USEOPTIONSFILE") interpretUseOptionsFile(i);
		if (mCommand[i]=="UOF") interpretUseOptionsFile(i);
		if (mCommand[i]=="EXECUTE") { interpretExecute(i); i=0; }
		if (mCommand[i]=="EXEC")    { interpretExecute(i); i=0; }
		if (mCommand[i]=="TEST") testFunctions();
		if (mCommand[i]=="TESTFUNCTION") testFunctions();
		if (mCommand[i]=="TESTFUNCTIONS") testFunctions();
		//Options File specific
		if (mCommand[i]=="SETPLOTTING") interpretSetPlotting(i);
		if (mCommand[i]=="SETTEXT") interpretSetText(i);
		if (mCommand[i]=="USESIM") interpretUsesSimFile(i);
		if (mCommand[i]=="USESIMFILE") interpretUsesSimFile(i);
		if (mCommand[i]=="USESSIMFILE") interpretUsesSimFile(i);
		if (mCommand[i]=="USF") interpretUsesSimFile(i);
		//Simulation File specific
		if (mCommand[i]=="SETSEED") interpretSetSeed(i);
		if (mCommand[i]=="SEED") interpretSetSeed(i);
		if (mCommand[i]=="OUTPUTFILENAME") interpretSetOutputFileName(i);
		if (mCommand[i]=="SETWRITEOUTPUTFILENAME") interpretSetOutputFileName(i);
		if (mCommand[i]=="SETOUTPUTFILENAME") interpretSetOutputFileName(i);
		if (mCommand[i]=="SETWRITEOUTPUTFILE") interpretSetWriteOutput(i);
		if (mCommand[i]=="SETWRITEOUTPUT") interpretSetWriteOutput(i);
		if (mCommand[i]=="DOWRITEOUTPUTFILE") interpretSetWriteOutput(i);
		if (mCommand[i]=="DOWRITEOUTPUT") interpretSetWriteOutput(i);
		if (mCommand[i]=="SETBODYSIZEADULT") interpretSetBodySizeAdult(i);
		if (mCommand[i]=="SETCONSTA") interpretSetConstA(i);
		if (mCommand[i]=="SETCONSTB") interpretSetConstB(i);
		if (mCommand[i]=="SETCONSTC") interpretSetConstC(i);
		if (mCommand[i]=="SETREPRODUCTIONMODE") interpretSetReproductionMode(i);
		if (mCommand[i]=="SETSIMTIME") interpretSetSimTime(i);
		if (mCommand[i]=="EXTRACTCOV") extractCov();
		//PopSize
		if (mCommand[i]=="SETSTARTPOPSIZE") interpretSetStartPopSize(i);
		if (mCommand[i]=="SETSTARTINGPOPSIZE") interpretSetStartPopSize(i);
		if (mCommand[i]=="STARTPOPSIZE") interpretSetStartPopSize(i);
		if (mCommand[i]=="STARTINGPOPSIZE") interpretSetStartPopSize(i);
		//Start resources
		if (mCommand[i]=="SETSTARTRESOURCES") interpretSetStartResources(i);
		if (mCommand[i]=="SETSTARTRESOURCE") interpretSetStartResources(i);
		if (mCommand[i]=="SETSTARTINGRESOURCES") interpretSetStartResources(i);
		if (mCommand[i]=="SETSTARTINGRESOURCE") interpretSetStartResources(i);
		if (mCommand[i]=="STARTRESOURCES") interpretSetStartResources(i);
		if (mCommand[i]=="STARTRESOURCE") interpretSetStartResources(i);
		if (mCommand[i]=="STARTINGRESOURCES") interpretSetStartResources(i);
		if (mCommand[i]=="STARTINGRESOURCE") interpretSetStartResources(i);
		//COMPUTER GENERATED
		if (mCommand[i]=="SETD") interpretSetD(i);
		if (mCommand[i]=="SETF") interpretSetF(i);
		if (mCommand[i]=="SETG") interpretSetG(i);
		if (mCommand[i]=="SETM") interpretSetM(i);
		if (mCommand[i]=="SETN") interpretSetN(i);
		if (mCommand[i]=="SETP") interpretSetP(i);
		if (mCommand[i]=="SETQ") interpretSetQ(i);
		if (mCommand[i]=="SETR") interpretSetR(i);
		if (mCommand[i]=="SETW") interpretSetW(i);
		//  COMPUTER GENERATED CODE
		if (mCommand[i]=="SETDCONSTA") interpretSetDconstA(i);
		if (mCommand[i]=="SETFCONSTA") interpretSetFconstA(i);													
		if (mCommand[i]=="SETGCONSTA") interpretSetGconstA(i);													
		if (mCommand[i]=="SETMCONSTA") interpretSetMconstA(i);													
		if (mCommand[i]=="SETNCONSTA") interpretSetNconstA(i);													
		if (mCommand[i]=="SETPCONSTA") interpretSetPconstA(i);													
		if (mCommand[i]=="SETQCONSTA") interpretSetQconstA(i);													
		if (mCommand[i]=="SETRCONSTA") interpretSetRconstA(i);													
		if (mCommand[i]=="SETWCONSTA") interpretSetWconstA(i);													
		if (mCommand[i]=="SETDCONSTB") interpretSetDconstB(i);													
		if (mCommand[i]=="SETFCONSTB") interpretSetFconstB(i);													
		if (mCommand[i]=="SETGCONSTB") interpretSetGconstB(i);													
		if (mCommand[i]=="SETMCONSTB") interpretSetMconstB(i);													
		if (mCommand[i]=="SETNCONSTB") interpretSetNconstB(i);													
		if (mCommand[i]=="SETPCONSTB") interpretSetPconstB(i);													
		if (mCommand[i]=="SETQCONSTB") interpretSetQconstB(i);													
		if (mCommand[i]=="SETRCONSTB") interpretSetRconstB(i);													
		if (mCommand[i]=="SETWCONSTB") interpretSetWconstB(i);													
		if (mCommand[i]=="SETDCONSTC") interpretSetDconstC(i);													
		if (mCommand[i]=="SETFCONSTC") interpretSetFconstC(i);													
		if (mCommand[i]=="SETGCONSTC") interpretSetGconstC(i);													
		if (mCommand[i]=="SETMCONSTC") interpretSetMconstC(i);													
		if (mCommand[i]=="SETNCONSTC") interpretSetNconstC(i);													
		if (mCommand[i]=="SETPCONSTC") interpretSetPconstC(i);													
		if (mCommand[i]=="SETQCONSTC") interpretSetQconstC(i);													
		if (mCommand[i]=="SETRCONSTC") interpretSetRconstC(i);													
		if (mCommand[i]=="SETWCONSTC") interpretSetWconstC(i);													
		if (mCommand[i]=="SETDCONSTD") interpretSetDconstD(i);													
		if (mCommand[i]=="SETFCONSTD") interpretSetFconstD(i);													
		if (mCommand[i]=="SETGCONSTD") interpretSetGconstD(i);													
		if (mCommand[i]=="SETMCONSTD") interpretSetMconstD(i);													
		if (mCommand[i]=="SETNCONSTD") interpretSetNconstD(i);													
		if (mCommand[i]=="SETPCONSTD") interpretSetPconstD(i);													
		if (mCommand[i]=="SETQCONSTD") interpretSetQconstD(i);													
		if (mCommand[i]=="SETRCONSTD") interpretSetRconstD(i);													
		if (mCommand[i]=="SETWCONSTD") interpretSetWconstD(i);													
		if (mCommand[i]=="SETDCONSTE") interpretSetDconstE(i);													
		if (mCommand[i]=="SETFCONSTE") interpretSetFconstE(i);													
		if (mCommand[i]=="SETGCONSTE") interpretSetGconstE(i);													
		if (mCommand[i]=="SETMCONSTE") interpretSetMconstE(i);													
		if (mCommand[i]=="SETNCONSTE") interpretSetNconstE(i);													
		if (mCommand[i]=="SETPCONSTE") interpretSetPconstE(i);													
		if (mCommand[i]=="SETQCONSTE") interpretSetQconstE(i);													
		if (mCommand[i]=="SETRCONSTE") interpretSetRconstE(i);													
		if (mCommand[i]=="SETWCONSTE") interpretSetWconstE(i);													

	}

	//No simulation to be done, except when execute is calling this function.
	//if (doExit==true) 
	exit(0);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::setOptionsFileName(const std::string& fileName) const
{
	assert(fileExists(mIniFileName)==true);
	std::ofstream fileOutput(mIniFileName.c_str());
	fileOutput << fileName << '\n';
	fileOutput.close();
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretExecute(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{
		std::cout << "\n\tPlease specify the file name of the file you want to execute.\n\n";
		return;
	}

	assert(index+1<mCommand.size());
	std::string fileName = mArgv[index+1];
	if (fileExists(fileName)==false)
	{
		std::cout << "\n\tFile '" << fileName << "' does not exist. Therefore, it cannot be used as an execution file.\n\n";
		return;
	}
	
	mArgv.resize(0); mCommand.resize(0);
	mArgv = fileToVector(fileName);
	coutVector(mArgv);
	mArgv.push_back("run");
	const unsigned int size = mArgv.size();
	mCommand.resize(size);
	for (unsigned int i=0; i<size; ++i) mCommand[i] = stringToUpper(mArgv[i]);
	interpretCommandLine();
	mDoExit = true;
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::extractCov() const
{
	std::cout << "NOT PROGRAMMED YET" << std::endl;
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::testFunctions() const
{
	ParameterSetSimulation params; //Default params
	if (mOptionsFile.getNsimFiles() > 0) params =  mOptionsFile.getParameterSetSimulation();
	std::auto_ptr<StrategyDdefault> pDdefault(new StrategyDdefault(&params.paramsD));
	std::auto_ptr<StrategyFdefault> pFdefault(new StrategyFdefault(&params.paramsF));
	std::auto_ptr<StrategyGconstant> pGconstant(new StrategyGconstant(&params.paramsG));
	std::auto_ptr<StrategyGplastic>  pGplastic( new StrategyGplastic( &params.paramsG));
	std::auto_ptr<StrategyMdefault>  pMdefault( new StrategyMdefault( &params.paramsM));
	std::auto_ptr<StrategyMconstant> pMconstant(new StrategyMconstant(&params.paramsM));
	std::auto_ptr<StrategyNplastic>  pNplastic(new StrategyNplastic(&params.paramsN));
	std::auto_ptr<StrategyNconstant> pNconstant(new StrategyNconstant(&params.paramsN));
	std::auto_ptr<StrategyPplastic>  pPplastic( new StrategyPplastic( &params.paramsP));
	std::auto_ptr<StrategyPconstant> pPconstant(new StrategyPconstant(&params.paramsP));
	std::auto_ptr<StrategyQdefault>  pQdefault(new StrategyQdefault(&params.paramsQ));
	std::auto_ptr<StrategyQconstant> pQconstant(new StrategyQconstant(&params.paramsQ));
	std::auto_ptr<StrategyRconstant> pRconstant(new StrategyRconstant(&params.paramsR));
	std::auto_ptr<StrategyRlogistic> pRlogistic(new StrategyRlogistic(&params.paramsR));
	std::auto_ptr<StrategyRcosine>   pRcosine(  new StrategyRcosine(  &params.paramsR));
	std::auto_ptr<StrategyWzero>    pWzero(new StrategyWzero(&params.paramsW));
	std::auto_ptr<StrategyWuniform> pWuniform(new StrategyWuniform(&params.paramsW));

	std::cout << "Now testing D." << std::endl;
	pDdefault->testMe();
	std::cout << "Now testing F." << std::endl;
	pFdefault->testMe();
	std::cout << "Now testing G." << std::endl;
	pGconstant->testMe();
	pGplastic->testMe();
	std::cout << "Now testing M." << std::endl;
	pMdefault->testMe();
	pMconstant->testMe();
	std::cout << "Now testing N." << std::endl;
	pNplastic->testMe();
	pNconstant->testMe();
	std::cout << "Now testing P." << std::endl;
	pPplastic->testMe();
	pPconstant->testMe();
	std::cout << "Now testing Q." << std::endl;
	pQdefault->testMe();
	pQconstant->testMe();
	std::cout << "Now testing R." << std::endl;
	pRconstant->testMe();
	pRlogistic->testMe();
	pRcosine->testMe();
	std::cout << "Now testing W." << std::endl;
	pWzero->testMe();
	pWuniform->testMe();
	std::cout << "Done testing." << std::endl;
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretUseOptionsFile(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{
		std::cout << "\n\tPlease specify the file name of the Options File you want to use.\n\n";
		return;
	}

	assert(index+1<mCommand.size());
	std::string fileName = mArgv[index+1];
	if (fileExists(fileName)==false)
	{
		std::cout << "\n\tFile '" << fileName << "' does not exist. Therefore, it cannot be used as an Options File.\n\n";
		return;
	}
	
	setOptionsFileName(fileName);
	std::cout << "\n\tFile '" << fileName << "' set to the Options File now used.\n\n";
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretShowSimFile(const unsigned int& index) const
{
	int simFileNumber;
	if (index+1==mCommand.size())
	{
		const int usesSimFile = mOptionsFile.getUsesSimFile();
		std::cout << "\n\tShowing Simulation File: " << (usesSimFile==-1 ? "all." : "#"+itoa(usesSimFile)+".") << std::endl;
		simFileNumber = usesSimFile;
	}
	else 
	{
		assert(index+1<mCommand.size());
		std::string nextInput = mCommand[index+1];
		if (isInt(nextInput,simFileNumber)==true)
		{   //User gives SimFile index
			if (simFileNumber<0)
			{
				std::cout << "\n\tIncorrect Simulation file index, as they cannot be negative.\n\n";
				return;
			}
			if (simFileNumber>=static_cast<int>(mOptionsFile.getNsimFiles()))
			{
				std::cout << "\n\tIncorrect Simulation file index, as this index does not exist.\n\n";
				return;
			}
			std::cout << "\n\tShowing Simulation File: #" << simFileNumber << std::endl;
		}
		else
		{   //User typed 'all' or bullshit
			if (nextInput=="ALL")
			{
				std::cout << "\n\tShowing Simulation File: all." << std::endl;
				simFileNumber=-1;
			}
			else
			{
				std::cout << "\n\tIncorrect Simulation file index, can only be either an index or 'all'.\n\n";
				return;
			}
		}
	
	}

	mOptionsFile.showSimFile(simFileNumber);
}
//----------------------------------------------------------------------------------
///Copies an Options File
void Sim4Interpreter::interpretCopyOptionsFile(const unsigned int& index) const
{
	if (index+1==mCommand.size())
	{   //User typed only 'copyOptionsFile'
		std::cout << "\n\tPlease add the target's file name.\n\n";
		return;
	}
	if (index+2>=mCommand.size())
	{   //User typed 'copyOptionsFile [something]'
		const std::string optionsFileNameFrom = mOptionsFile.getFileName();
		const std::string optionsFileNameTo   = mArgv[index+1];
		std::cout << "\n\tCopying Options File: '" << optionsFileNameFrom 
			<< "' to '"<< optionsFileNameTo << "'.\n\n";
		copyFile(optionsFileNameFrom,optionsFileNameTo);
	}
	
}
//----------------------------------------------------------------------------------
///Copies a SimFile
void Sim4Interpreter::interpretCopySimFile(const unsigned int& index) const
{
	if (mOptionsFile.getNsimFiles()==0)
	{
		std::cout << "\n\tNo Simulation Files to copy. Please use 'addSimFile' command first.\n\n";
		return;
	}

	std::string simFileNameFrom;
	std::string simFileNameTo;
	if (index+1==mCommand.size())
	{   //User typed only 'copySimfile'
		std::cout << "\n\tPlease add the target's file name.\n\n";
		return;
	}
	if (index+2==mCommand.size())
	{   //User typed 'copySimfile [something]', use the SimFile in focus
		const int usesSimFile = mOptionsFile.getUsesSimFile();
		if (usesSimFile==-1)
		{
			std::cout << "\n\tIncorrect Simulation file index 'all': cannot copy all files\n\n";
			return;
		}
		assert((usesSimFile>-1 && usesSimFile<static_cast<int>(mOptionsFile.getNsimFiles())));
		simFileNameFrom = mOptionsFile.getSimFileName(usesSimFile);
		simFileNameTo   = mArgv[index+1];
	}
	else 
	{   //User typed 'copySimfile [something] [something]' (and perhaps more [something]'s)
		assert(index+3<=mCommand.size());
		const std::string nextInput = mCommand[index+1];
		int simFileNumber;
		if (isInt(nextInput,simFileNumber)==true)
		{   //User gives SimFile index
			if (simFileNumber<0)
			{
				std::cout << "\n\tIncorrect Simulation file index, as they cannot be negative.\n\n";
				return;
			}
			if (simFileNumber>=static_cast<int>(mOptionsFile.getNsimFiles()))
			{
				std::cout << "\n\tIncorrect Simulation file index, as this index does not exist.\n\n";
				return;
			}
			simFileNameFrom = mOptionsFile.getSimFileName(simFileNumber);
			simFileNameTo   = mArgv[index+2];
		}
		else
		{   //User typed 'all' or bullshit
			if (nextInput=="ALL")
			{
				std::cout << "\n\tCannot copy 'all' files. Please use an index.\n\n";
			}
			else
			{
				std::cout << "\n\tIncorrect Simulation file index, can only be an index.\n\n";
				return;
			}
		}
	}

	std::cout << "\n\tCopying Simulation File: '" << simFileNameFrom << "' to '"<< simFileNameTo << "'.\n\n";
	copyFile(simFileNameFrom,simFileNameTo);
	
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretRemoveSimFile(const unsigned int& index)
{
	int simFileNumber;
	if (index+1==mCommand.size())
	{
		const int usesSimFile = mOptionsFile.getUsesSimFile();
		std::cout << "\n\tRemoving Simulation File: " << (usesSimFile==-1 ? "all." : "#"+itoa(usesSimFile)+".") << std::endl;
		simFileNumber = -1;
	}
	else 
	{
		assert(index+1<mCommand.size());
		std::string nextInput = mCommand[index+1];
		if (isInt(nextInput,simFileNumber)==true)
		{   //User gives SimFile index
			if (simFileNumber<0)
			{
				std::cout << "\n\tIncorrect Simulation file index, as they cannot be negative.\n\n";
				return;
			}
			if (simFileNumber>=static_cast<int>(mOptionsFile.getNsimFiles()))
			{
				std::cout << "\n\tIncorrect Simulation file index, as this index does not exist.\n\n";
				return;
			}
			std::cout << "\n\tRemoving Simulation File: #" << simFileNumber << std::endl;
		}
		else
		{   //User typed 'all' or bullshit
			if (nextInput=="ALL")
			{
				std::cout << "\n\tRemoving Simulation File: all." << std::endl;
				simFileNumber=-1;
			}
			else
			{
				std::cout << "\n\tIncorrect Simulation file index, can only be either an index or 'all'.\n\n";
				return;
			}
		}
	
	}

	mOptionsFile.removeSimFile(simFileNumber);

	//If all files are removed, 'usesSimFile' is set to 'all'
	//if (mOptionsFile.getNsimFiles()==0)	mOptionsFile.setUsesSimFile(-1);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretAddSimFile(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{
		std::cout << "\n\tPlease specify the file name of the Simulation file you want to add.\n\n";
		return;
	}

	assert(index+1<mCommand.size());
	std::string fileName = mArgv[index+1];
	if (fileExists(fileName)==false)
	{
		std::cout << "\n\tFile '" << fileName << "' does not exist. Therefore, it cannot be added to the Options File.\n\n";
		return;
	}
	
	mOptionsFile.addSimFile(fileName);
	std::cout << "\n\tFile '" << fileName << "' added to the Options File.\n\n";
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretUsesSimFile(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setUses' only
		std::cout
			<< "\n\tPlease specify to INDEX or 'all' for the Simulation File in focus.\n"
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];

	if (nextCommand=="ALL") 
	{
		mOptionsFile.setUsesSimFile(-1); //-1 = 'all'
		return;
	}

	int newUsesNumber=-1;
	if (isInt(nextCommand,newUsesNumber)==false)
	{   //User typed 'setSimTime [non-integer]'
		std::cout 
			<< "\n\tPlease input the index of the Simulation File you want to use as a NUMBER,"
			<< "\n\te.g. './Sim4 setUses 0', or use './Sim4 setUses all'" 
			<< std::endl << std::endl;
	}

	//This sets the Uses to 'index'. OptionsFile handles if 'index' is out of range
	mOptionsFile.setUsesSimFile(newUsesNumber);
	//std::cout << "\n\tSet the files in focus to '" << index << "'.\n" << std::endl;

}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetText(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setPlotting' only
		std::cout 
			<< "\n\tPlease also specify if you want to turn showing the year's summary 'on' or 'off',"
			<< "\n\te.g. './Sim4 setText on' or './Sim4 setText off'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];
	if (nextCommand=="ON")
	{
		mOptionsFile.setShowYearSummary(true);
	}
	else
	if (nextCommand=="OFF")
	{
		mOptionsFile.setShowYearSummary(false);
	}
	else
	{
		std::cout 
			<< "\n\tShowing the year's summary can only be turned 'on' or 'off',"
			<< "\n\te.g. './Sim4 setText on' or './Sim4 setText off'" 
			<< std::endl << std::endl;
	}

}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetPlotting(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setPlotting' only
		std::cout 
			<< "\n\tPlease also specify if you want to turn plotting 'on' or 'off',"
			<< "\n\te.g. './Sim4 setPlotting on' or './Sim4 setPlotting off'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];
	if (nextCommand=="ON")
	{
		mOptionsFile.setPlotting(true);
	}
	else
	if (nextCommand=="OFF")
	{
		mOptionsFile.setPlotting(false);
	}
	else
	{
		std::cout 
			<< "\n\tPlotting can only be turned 'on' or 'off',"
			<< "\n\te.g. './Sim4 setPlotting on' or './Sim4 setPlotting off'" 
			<< std::endl << std::endl;
	}

}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetSimTime(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setSimTime' only
		std::cout 
			<< "\n\tPlease also specify the amount of timesteps you want to"
			<< "\n\tset the simulation time to, e.g. './Sim4 setSimTime 1000'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];
	int newTimeStepsNumber=-1;
	if (isInt(nextCommand,newTimeStepsNumber)==false)
	{   //User typed 'setSimTime [non-integer]'
		std::cout 
			<< "\n\tPlease input the amount of timesteps you want to set the"
			<< "\n\t simulation time to as a NUMBER, e.g. './Sim4 setSimTime 1000'" 
			<< std::endl << std::endl;
		return;
	}
	
	if (newTimeStepsNumber<=0) 
	{   //User typed 'setSimTime [zero or smaller]'
		std::cout 
			<< "\n\tPlease input the amount of timesteps you want to set the"
			<< "\n\t simulation time to as a POSITIVE NON_ZERO NUMBER, e.g. './Sim4 setSimTime 1000'" 
			<< std::endl << std::endl;
		return;
	}

	mOptionsFile.setSimTime(newTimeStepsNumber);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetOutputFileName(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setOutputFile' only
		std::cout 
			<< "\n\tPlease also specify the NAME of the output file."
			<< "\n\te.g. './Sim4 setOutputFile myOutput1.rda'" 
			<< std::endl << std::endl;
		return;
	}
	
	mOptionsFile.setOutputFileName(mArgv[index+1]);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetSeed(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setSeed' only
		std::cout 
			<< "\n\tPlease also specify the number of the seed you want to"
			<< "\n\tset the random number generator to, e.g. './Sim4 setSeed 0'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];
	int newSeed=-1;
	if (isInt(nextCommand,newSeed)==false)
	{   //User typed 'setSeede [non-integer]'
		std::cout 
			<< "\n\tPlease specify the number of the seed you want to"
			<< "\n\tset the random number generator to as a NUMBER, e.g. './Sim4 setSeed 0'" 
			<< std::endl << std::endl;
		return;
	}
	
	mOptionsFile.setSeed(newSeed);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetWriteOutput(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setWriteOutput' only
		std::cout 
			<< "\n\tPlease also specify if you want to turn writing to a file 'on' or 'off',"
			<< "\n\te.g. './Sim4 setWriteOutput on' or './Sim4 setWriteOutput off'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];
	if (nextCommand=="ON")
	{
		mOptionsFile.setWriteOutputFile(true);
	}
	else
	if (nextCommand=="OFF")
	{
		mOptionsFile.setWriteOutputFile(false);
	}
	else
	{
		std::cout 
			<< "\n\tWriting to an output file can only be turned 'on' or 'off',"
			<< "\n\te.g. './Sim4 setWriteOutput on' or './Sim4 setWriteOutput off'" 
			<< std::endl << std::endl;
	}

}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetStartPopSize(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setStartPopSize' only
		std::cout 
			<< "\n\tPlease also specify the VALUE of the starting population size."
			<< "\n\te.g. './Sim4 setStartPopSize 1000'" 
			<< std::endl << std::endl;
		return;
	}
	
	const std::string nextCommand = mCommand[index+1];

	int newStartPopSize=-1;
	if (isInt(nextCommand,newStartPopSize)==false)
	{   //User typed 'setStartPopSize [non-integer]'
		std::cout 
			<< "\n\tPlease input the value of the starting population size as a NUMBER."
			<< "\n\te.g. './Sim4 setStartPopSize 1000'" 
			<< std::endl << std::endl;
		return;
	}
	
	if (newStartPopSize<=0)
	{
		std::cout 
			<< "\n\tPlease input for the value of the starting population size a POSITIVE NON_ZERO number."
			<< "\n\te.g. './Sim4 setStartPopSize 1000'" 
			<< std::endl << std::endl;
		return;
	}
	
	//Success. OptionsFile produces this output
	mOptionsFile.setStartPopSize(newStartPopSize);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetStartResources(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setStartPopSize' only
		std::cout 
			<< "\n\tPlease also specify the VALUE of the starting population size."
			<< "\n\te.g. './Sim4 setStartPopSize 1000'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];

	double newStartResources=-1;
	if (isDouble(nextCommand,newStartResources)==false)
	{   //User typed 'setStartResources [non-integer]'
		std::cout 
			<< "\n\tPlease input the amount of starting resources as a NUMBER."
			<< "\n\te.g. './Sim4 setStartResources 0.1'" 
			<< std::endl << std::endl;
		return;
	}

	if (newStartResources<0.0)
	{
		std::cout 
			<< "\n\tPlease input the amount of starting resources as a POSITIVE number."
			<< "\n\te.g. './Sim4 setStartResources 0.1'" 
			<< std::endl << std::endl;
		return;
	}

	//Success. OptionsFile produces this output
	mOptionsFile.setStartResources(newStartResources);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetBodySizeAdult(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setStartPopSize' only
		std::cout 
			<< "\n\tPlease also specify the VALUE of the starting population size."
			<< "\n\te.g. './Sim4 setStartPopSize 1000'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];

	double newBodySize=-1.0;
	if (isDouble(nextCommand,newBodySize)==false)
	{   //User typed 'setBodySizeAdult [non-double]'
		std::cout 
			<< "\n\tPlease input the body size to become an adult as a NUMBER."
			<< "\n\te.g. './Sim4 setBodySizeAdult 1.5'" 
			<< std::endl << std::endl;
		return;
	}

	if (newBodySize<0.0)
	{   //User typed 'setBodySizeAdult [non-double]'
		std::cout 
			<< "\n\tPlease input for the body size to become an adult a POSITIVE number."
			<< "\n\te.g. './Sim4 setBodySizeAdult 1.5'" 
			<< std::endl << std::endl;
		return;
	}
	
	//Success. OptionsFile handles the feedback to the user.
	mOptionsFile.setBodySizeAdult(newBodySize);

}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetConstA(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setStartPopSize' only
		std::cout 
			<< "\n\tPlease also specify the VALUE of the starting population size."
			<< "\n\te.g. './Sim4 setStartPopSize 1000'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];
	double newConstA=-1.0;
	if (isDouble(nextCommand,newConstA)==false)
	{   //User typed 'setConstA [non-double]'
		std::cout 
			<< "\n\tPlease input the value of constant 'A' as a NUMBER."
			<< "\n\te.g. './Sim4 setConstA 0.9'" 
			<< std::endl << std::endl;
		return;
	}

	if (newConstA<0.0) // || newConstA>1.0)
	{   //User typed 'setConstA [non-fraction]'
		std::cout 
			<< "\n\tPlease input the value of constant 'A' as a POSITIVE VALUE."
			<< "\n\ti.e. a value from 0.0 to and including 1.0."
			<< "\n\te.g. './Sim4 setConstA 0.9'" 
			<< std::endl << std::endl;
		return;
	}
	
	//Success. OptionsFile handles the feedback to the user
	mOptionsFile.setConstA(newConstA);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetConstB(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setStartPopSize' only
		std::cout 
			<< "\n\tPlease also specify the VALUE of the starting population size."
			<< "\n\te.g. './Sim4 setStartPopSize 1000'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];
	double newConstB=-1.0;
	if (isDouble(nextCommand,newConstB)==false)
	{   //User typed 'setConstB [non-double]'
		std::cout 
			<< "\n\tPlease input the value of constant 'B' as a NUMBER."
			<< "\n\te.g. './Sim4 setConstB 0.9'" 
			<< std::endl << std::endl;
		return;
	}

	if (newConstB<0.0) // || newConstB>1.0)
	{   //User typed 'setConstB [non-fraction]'
		std::cout 
			<< "\n\tPlease input the value of constant 'B' as a POSITIVE VALUE."
			<< "\n\ti.e. a value from 0.0 to and including 1.0."
			<< "\n\te.g. './Sim4 setConstB 0.9'" 
			<< std::endl << std::endl;
		return;
	}
	
	//Success. OptionsFile handles the feedback to the user
	mOptionsFile.setConstB(newConstB);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetConstC(const unsigned int& index)
{
	if (index+1==mCommand.size())
	{   //User typed 'setStartPopSize' only
		std::cout 
			<< "\n\tPlease also specify the VALUE of the starting population size."
			<< "\n\te.g. './Sim4 setStartPopSize 1000'" 
			<< std::endl << std::endl;
		return;
	}

	const std::string nextCommand = mCommand[index+1];
	double newConstC=-1.0;
	if (isDouble(nextCommand,newConstC)==false)
	{   //User typed 'setConstC [non-double]'
		std::cout 
			<< "\n\tPlease input the value of constant 'C' as a NUMBER."
			<< "\n\te.g. './Sim4 setConstC 0.9'" 
			<< std::endl << std::endl;
		return;
	}

	if (newConstC<0.0) // || newConstC>1.0)
	{   //User typed 'setConstC [non-fraction]'
		std::cout 
			<< "\n\tPlease input the value of constant 'C' as a POSITIVE VALUE."
			<< "\n\ti.e. a value from 0.0 to and including 1.0."
			<< "\n\te.g. './Sim4 setConstC 0.9'" 
			<< std::endl << std::endl;
		return;
	}
	
	//Success. OptionsFile handles the feedback to the user
	mOptionsFile.setConstC(newConstC);
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretHelp(const unsigned int& index) const
{
	if (index+1==mCommand.size())
	{   //User typed 'help' only
		showHelp();
		return;
	}

	if (   mCommand[index+1]=="OPTIONFILE"  || mCommand[index+1]=="OPTIONSFILE")
	{   //User typed 'help OptionsFile'
		showHelpOptionFile();
	}

	if (   mCommand[index+1]=="SIMFILE")
	{   //User typed 'help SimFile'
		showHelpSimFile();
	}
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::showHelp() const
{
	std::cout 
		<< "\n\tHelp for Sim4, by Richel Bilderbeek." 
		<< "\n\t"
		<< "\n\tA simulation uses at least two files: "
		<< "\n\t  1) A single Options file: options for simulation, e.g. write results to disk."
		<< "\n\t  2) One or more Simulation files: parameters for the simulation, e.g. the starting population size."
		<< "\n\tThe Options file is connected to one or more Simulation files."
		<< "\n\tWhen changing a Simulation file, you change only one (or all) of those the Options file is connected to."
		<< "\n\tThis enables you to do multiple simulations with your favorite options."
		<< "\n\tWhen modifying SimFiles, you either specify the index of this SimFile, or write 'all' for all SimFiles."
		<< "\n\tWhen giving neither, the focused Simulation file(s) is used."
		<< "\n\t"
		<< "\n\tProgram usage options: "
		<< "\n\t  ./Sim4 [option1] [option2] [etc]"
		<< "\n\t     without options, the simulation is started with current Options file ('defaultOptionsFile.txt' at start) and its connected Simulation file(s)."
		<< "\n\tOptions:" 
		<< "\n\t  showUses : shows Options file and the Simulation file(s) the simulation will use."
		<< "\n\t  showOptionsFile : shows current Options file and contents."
		<< "\n\t  showSimFile : shows the Simulation file(s) set by useSimFile."
		<< "\n\t  showSimFile {[n],all} : shows 'n'-th or all Simulation file(s) that current Options file is connected to."
		<< "\n\t  useOptionsFile \"optionsfilename\" : use Options file with 'optionsfilename'."
		<< "\n\t  addSimFile \"simulationfilename\" : adds Simulation file to current Options file."
		<< "\n\t  removeSimFile : removes Simulation file(s) set by useSimFile."
		<< "\n\t  removeSimFile {[n],all} : removes 'n'-th or all Simulation file(s) from current Options file. "
		<< "\n\t  useSimFile {[n],all} : sets focus on Simulation file 'n' or all"
		<< "\n\t  copyOptionsFile \"filename\" : copies current Options file to 'filename'."
		<< "\n\t  copySimFile [n] \"filename\" : copies 'n'-th Simulation file to 'filename'."
		<< "\n\tOptions for modifying Options file:"
		<< "\n\t  help OptionFile : displays more options for Options file."
		<< "\n\t  setPlotting {on,off} : turns final plotting on or off."
		<< "\n\t  setWriteOutput {on,off} : turns writing to outputfile on or off."
		<< "\n\t  setWriteOutputFile \"filename\" : sets simulation output file to 'filename'."
		<< "\n\tOptions for modifying Simulation file:"
		<< "\n\t  help SimFile : displays more options for Options file."
		<< "\n\t  setSimTime [number] {[n],all} : sets 'n'-th or all simulation(s) time(s) to 'number' timesteps."
		<< "\n" 
		<< std::endl;
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::showHelpOptionFile() const
{
	std::cout 
		<< "\n\tHelp on Option Files."
		<< "\n\t"
		<< "\n\tAn Option File contains options for one or more Simulation Files. When an experiment is started,"
		<< "\n\tfor every Simulation File one simulation is run, with the options from the Options File."
		<< "\n"
		<< "\n\t  setText {on,off} : turns showing year summary on screen on or off."
		<< "\n\t  setPlotting {on,off} : turns final plotting on or off."
		<< "\n\t  setWriteOutput {on,off} : turns writing to outputfile on or off."
		<< "\n\t  setWriteOutputFile \"filename\" : sets simulation output file to 'filename'."
		<< std::endl;
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::showHelpSimFile() const
{
	std::cout 
		<< "\n\tHelp on Simulation File."
		<< "\n\t"
		<< "\n\tA Simulation File comprises all simulation parameters and setup."
		<< "\n\tEvery parameter can be changed by the following commands, and is"
		<< "\n\tapplied on the simulation(s) in focus."
		<< "\n"
		<< "\n\t  setSimTime [n] : Sets running time to 'n' timesteps."
		<< "\n\t  setStartPopSize [n] : Sets starting population size to 'n' individuals."
		<< "\n\t  setStartResources [n] : Sets starting resources to 'n' units."
		<< "\n\t  setBodySizeAdult [n] : Sets body size to become adult to 'n' units of weight."
		<< "\n\t  setConstA [n] : Sets efficiency to convert resources to body size to fraction 'n'."
		<< "\n\t  setConstB [n] : Sets efficiency to convert resources to reserves to fraction 'n'."
		<< "\n\t  setConstC [n] : Sets efficiency to convert reserves to egg mass to fraction 'n'."
		<< "\n\t  setReproductionMode [n] : Sets 'n'-th reproduction mode. Without giving 'n' a menu appears."
		<< "\n\t  setD [n]: Sets 'n'-th formula for D, the death rate. Without giving 'n' a menu appears."
		<< "\n\t  setF [n]: Sets 'n'-th formula for F, the feeding rate. Without giving 'n' a menu appears."
		<< "\n\t  setG [n]: Sets 'n'-th formula for G, the fraction egg biomass per offspring. Without giving 'n' a menu appears."
		<< "\n\t  setM [n]: Sets 'n'-th formula for M, metabolic cost. Without giving 'n' a menu appears."
		<< "\n\t  setN [n]: Sets 'n'-th formula for N, amount of offspring. Without giving 'n' a menu appears."
		<< "\n\t  setP [n]: Sets 'n'-th formula for P, allocation of resources to body size. Without giving 'n' a menu appears."
		<< "\n\t  setQ [n]: Sets 'n'-th formula for Q, biomass investment in eggs. Without giving 'n' a menu appears."
		<< "\n\t  setR [n]: Sets 'n'-th formula for R, the resource inflow. Without giving 'n' a menu appears."
		<< "\n\t  setW [n]: Sets 'n'-th formula for W, the way resources are (un)equally disributed over individuals. Without giving 'n' a menu appears."
		<< "\n\t"
		<< "\n\tTo change a constant in each of the equations, use:"
		<< "\n\t  set{D,F,G,M,N,P,Q,R,W}const{a,b,c,d} [n] : Sets constant in equation to 'n', e.g. 'setDconstA 0.5'"
		<< "\n\t"
		<< std::endl;
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::showAbout() const
{
	std::cout 
		<< "\n\tThis program was written by:"
		<< "\n\t"
		<< "\n\t    Richel Bilderbeek"
		<< "\n\t    richelbilderbeek@fastmail.fm"
		<< "\n\t"
		<< "\n\twhile in Bristol from the 9th of May 2005 to 14th of August 2005"
		<< "\n\tunder supervision of Robert Payne."
		<< "\n\t"
		<< std::endl;
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::showUses() const
{
	const int usesSimFile = mOptionsFile.getUsesSimFile();
	std::cout
		<< "\n\tOptions file: " << mOptionsFile.getFileName()
		<< "\n\tUsing Simulation File: " << (usesSimFile==-1 ? "all." : "#"+itoa(usesSimFile)+".")
		<< std::endl;
	
	std::vector<std::string> simFileName = mOptionsFile.getSimulationFileNames();
	const unsigned int nSimFileNames = simFileName.size();
	for (unsigned int i=0; i<nSimFileNames; ++i)
	{
		std::cout << "\tSimulation file #" << i << ": " << simFileName[i] << std::endl;
	}
	std::cout << std::endl;
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::showOptionsFile() const
{
	mOptionsFile.showUser();
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetReproductionMode(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setReproductionMode' only
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of D" << std::endl		
			<< "    Optional indices are:" << std::endl									
			<< "        [0] enumReproductionModeFraction : Calculate fraction of egg biomass per offspring, eq. G." << std::endl							
			<< "        [1] enumReproductionModeAmount : Calculate amunt of offspring, eq. N." << std::endl							
			<< std::endl;																	
		return;																				
	}																						
																							
	assert(userInputToEnumReproductionMode(0)==enumReproductionModeFraction);
	assert(userInputToEnumReproductionMode(1)==enumReproductionModeAmount);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setReproductionMode [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the ReproductionMode index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setReproductionMode 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>1)															
	{																						
		std::cout << std::endl																
			<< "    Please select a ReproductionMode index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setReproductionMode 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setReproductionMode(userInputToEnumReproductionMode(userInput));											
}																							
//----------------------------------------------------------------------------------		
void Sim4Interpreter::interpretSetD(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setD' only
	    //const std::auto_ptr<StrategyDconstant> pDconstant(new StrategyDconstant);
		//const std::auto_ptr<StrategyDsizeOnly> pDsizeOnly(new StrategyDsizeOnly);
		const std::auto_ptr<ParameterSetD> pDparams(new ParameterSetD);
		const std::auto_ptr<StrategyDdefault>  pDdefault( new StrategyDdefault(pDparams.get()));
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of D" << std::endl		
			<< "    Optional indices are:" << std::endl									
			<< "        [0] enumDdefault  : " << pDdefault->getString() << std::endl
			//<< "        [1] enumDconstant : " << pDconstant->getString() << std::endl
			//<< "        [2] enumDsizeOnly : " << pDsizeOnly->getString() << std::endl
			<< std::endl;																	
		return;																				
	}																						

	assert(userInputToEnumD(0)==enumDdefault);
	//assert(userInputToEnumD(1)==enumDconstant);
	//assert(userInputToEnumD(2)==enumDsizeOnly);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setD [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the D's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setD 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>2)															
	{																						
		std::cout << std::endl																
			<< "    Please select an D's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setD 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setD(userInputToEnumD(userInput));											
}																							
//----------------------------------------------------------------------------------		
void Sim4Interpreter::interpretSetF(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setF' only															
		const std::auto_ptr<ParameterSetF> pFparams(new ParameterSetF);
	    //const std::auto_ptr<StrategyFconstant> pFconstant(new StrategyFconstant(pFparams.get()));
		const std::auto_ptr<StrategyFdefault>  pFdefault( new StrategyFdefault(pFparams.get()));
	    //const std::auto_ptr<StrategyFgauss>  pFgauss( new StrategyFgauss(pFparams.get()));
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of F" << std::endl		
			<< "    Optional indices are:" << std::endl
			<< "        [0] enumFdefault  : " << pFdefault->getString()  << std::endl
			<< std::endl;																	
		return;																				
	}																						

	assert(userInputToEnumF(0)==enumFdefault);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setF [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the F's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setF 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>2)															
	{																						
		std::cout << std::endl																
			<< "    Please select an F's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setF 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setF(userInputToEnumF(userInput));											
}																							
//----------------------------------------------------------------------------------		
void Sim4Interpreter::interpretSetG(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setG' only															
		const std::auto_ptr<ParameterSetG> pGparams(new ParameterSetG);
	    const std::auto_ptr<StrategyGconstant> pGconstant(new StrategyGconstant(pGparams.get()));
	    const std::auto_ptr<StrategyGplastic>  pGplastic( new StrategyGplastic(pGparams.get()));
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of G" << std::endl		
			<< "    Optional indices are:" << std::endl
			<< "        [0] enumGconstant: " << pGconstant->getString() << std::endl
			<< "        [1] enumGplastic : " << pGplastic->getString()  << std::endl
			<< std::endl;																	
		return;																				
	}																						
																							
	assert(userInputToEnumG(0)==enumGconstant);
	assert(userInputToEnumG(1)==enumGplastic);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setG [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the G's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setG 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>1)															
	{																						
		std::cout << std::endl																
			<< "    Please select an G's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setG 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setG(userInputToEnumG(userInput));											
}																							
//----------------------------------------------------------------------------------		
void Sim4Interpreter::interpretSetM(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setM' only															
		const std::auto_ptr<ParameterSetM> pMparams(new ParameterSetM);
	    const std::auto_ptr<StrategyMconstant> pMconstant(new StrategyMconstant(pMparams.get()));
	    const std::auto_ptr<StrategyMdefault>  pMdefault( new StrategyMdefault(pMparams.get()));

		std::cout << std::endl																
			<< "    Please also specify the index of the formula of M" << std::endl		
			<< "    Optional indices are:" << std::endl
			<< "        [0] enumMconstant : " << pMconstant->getString() << std::endl
			<< "        [1] enumMdefault  : " << pMdefault->getString()  << std::endl
			<< std::endl;																	
		return;																				
	}																						
																							
	assert(userInputToEnumM(0)==enumMconstant);
	assert(userInputToEnumM(1)==enumMdefault);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setM [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the M's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setM 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>1)															
	{																						
		std::cout << std::endl																
			<< "    Please select an M's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setM 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setM(userInputToEnumM(userInput));											
}																							
//----------------------------------------------------------------------------------		
void Sim4Interpreter::interpretSetN(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setN' only															
		const std::auto_ptr<ParameterSetN> pNparams(new ParameterSetN);
		pNparams->C = 1.0;
	    const std::auto_ptr<StrategyNconstant> pNconstant(new StrategyNconstant(pNparams.get()));
	    const std::auto_ptr<StrategyNplastic>  pNplastic( new StrategyNplastic(pNparams.get()));
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of N" << std::endl		
			<< "    Optional indices are:" << std::endl									
			<< "        [0] enumNplastic  : " << pNplastic->getString() << std::endl
			<< "        [1] enumNconstant : " << pNconstant->getString() << std::endl
			<< std::endl;																	
		return;																				
	}																						
																							
	assert(userInputToEnumN(0)==enumNplastic);
	assert(userInputToEnumN(1)==enumNconstant);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setN [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the N's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setN 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>1)															
	{																						
		std::cout << std::endl																
			<< "    Please select an N's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setN 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setN(userInputToEnumN(userInput));
}																							
//----------------------------------------------------------------------------------		
void Sim4Interpreter::interpretSetP(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setP' only
		const std::auto_ptr<ParameterSetP> pPparams(new ParameterSetP);
	    const std::auto_ptr<StrategyPconstant> pPconstant(new StrategyPconstant(pPparams.get()));
	    const std::auto_ptr<StrategyPplastic> pPplasticA(new StrategyPplastic(pPparams.get()));
															
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of P" << std::endl		
			<< "    Optional indices are:" << std::endl									
			<< "        [0] enumPconstant : " << pPconstant->getString() << std::endl
			<< "        [1] enumPplastic : " << pPplasticA->getString() << std::endl
			<< std::endl;																	
		return;																				
	}																						
																							
	assert(userInputToEnumP(0)==enumPconstant);
	assert(userInputToEnumP(1)==enumPplastic);
	
	
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setP [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the P's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setP 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>2)															
	{																						
		std::cout << std::endl																
			<< "    Please select an P's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setP 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setP(userInputToEnumP(userInput));											
}
//----------------------------------------------------------------------------------
void Sim4Interpreter::interpretSetQ(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setQ' only															
		const std::auto_ptr<ParameterSetQ> pQparams(new ParameterSetQ);
	    const std::auto_ptr<StrategyQconstant> pQconstant(new StrategyQconstant(pQparams.get()));
	    const std::auto_ptr<StrategyQdefault > pQdefault( new StrategyQdefault( pQparams.get()));
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of Q" << std::endl		
			<< "    Optional indices are:" << std::endl
			<< "        [0] enumQconstant : " << pQconstant->getString() << std::endl
			<< "        [1] enumQdefault  : " << pQdefault->getString()  << std::endl
			<< std::endl;																	
		return;																				
	}																						
																							
	assert(userInputToEnumQ(0)==enumQconstant);
	assert(userInputToEnumQ(1)==enumQdefault);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setQ [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the Q's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setQ 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>1)															
	{																						
		std::cout << std::endl																
			<< "    Please select an Q's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setQ 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setQ(userInputToEnumQ(userInput));											
}																							
//----------------------------------------------------------------------------------		
void Sim4Interpreter::interpretSetR(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setR' only															
		const std::auto_ptr<ParameterSetR> pRparams(new ParameterSetR);
	    const std::auto_ptr<StrategyRconstant> pRconstant(new StrategyRconstant(pRparams.get()));
	    const std::auto_ptr<StrategyRlogistic> pRlogistic(new StrategyRlogistic(pRparams.get()));
	    const std::auto_ptr<StrategyRcosine  > pRcosine(  new StrategyRcosine(  pRparams.get()));
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of R" << std::endl		
			<< "    Optional indices are:" << std::endl									
			<< "        [0] enumRconstant : " << pRconstant->getString() << std::endl
			<< "        [1] enumRlogistic : " << pRlogistic->getString() << std::endl
			<< "        [2] enumRcosine   : " << pRcosine->getString()   << std::endl
			<< std::endl;																	
		return;																				
	}																						
																							
	assert(userInputToEnumR(0)==enumRconstant);
	assert(userInputToEnumR(1)==enumRlogistic);
	assert(userInputToEnumR(2)==enumRcosine);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setR [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the R's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setR 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>2)															
	{																						
		std::cout << std::endl																
			<< "    Please select an R's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setR 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setR(userInputToEnumR(userInput));											
}																							
//----------------------------------------------------------------------------------		
void Sim4Interpreter::interpretSetW(const unsigned int& index)							
{																							
	if (index+1==mCommand.size())															
	{   //User typed 'setW' only															
		const std::auto_ptr<ParameterSetW> pWparams(new ParameterSetW);
	    const std::auto_ptr<StrategyWzero>    pWzero(   new StrategyWzero(pWparams.get()));
	    const std::auto_ptr<StrategyWuniform> pWuniform(new StrategyWuniform(pWparams.get()));
		std::cout << std::endl																
			<< "    Please also specify the index of the formula of W" << std::endl		
			<< "    Optional indices are:" << std::endl									
			<< "        [0] enumWzero    : " << pWzero->getString()     << std::endl
			<< "        [1] enumWuniform : " << pWuniform->getString() 	
			<< std::endl;
		return;																				
	}																						
																							
	assert(userInputToEnumW(0)==enumWzero);
	assert(userInputToEnumW(1)==enumWuniform);
																							
	const std::string nextCommand = mCommand[index+1];										
																							
	int userInput=-1;																		
	if (isInt(nextCommand,userInput)==false)												
	{   //User typed 'setW [non-integer]'													
		std::cout << std::endl																
			<< "    Please input the W's equation index as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setW 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	if (userInput<0 || userInput>1)															
	{																						
		std::cout << std::endl																
			<< "    Please select an W's equation index that is IN RANGE." << std::endl   
			<< "    e.g. './Sim4 setW 0'" << std::endl									
			<< std::endl;																	
		return;																				
	}																						
																							
	//Success. OptionsFile produces this output.											
	mOptionsFile.setW(userInputToEnumW(userInput));											
}																							
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
