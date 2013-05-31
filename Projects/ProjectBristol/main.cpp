#include <iostream>
#include "Sim4Interpreter.h"
#include "OptionsFile.h"
#include "Experiment.h"

///Goal of main is to be the interface between command-line input, OptionsFile and Experiment
///
///The meat of the code is in those classes.
///
///

//#include "HelperFunctions.h"
//#include "Test.h"
//demoGnuplot();


int main (int argc, char * const argv[]) 
{
	std::cout << "VERSION 17" << std::endl;
	//Read the command line options
	const Sim4Interpreter interpreter(argc,argv);
	//Get the OptionsFile
	const OptionsFile optionsFile = interpreter.getOptionsFile();
	//Create the Experiment with the OptionsFile
	const Experiment experiment(optionsFile);
	//Run the Experiment
	experiment.execute();
	//Done...
    return 0;
}
