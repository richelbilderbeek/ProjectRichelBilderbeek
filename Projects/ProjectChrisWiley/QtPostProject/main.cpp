#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>

#include "parameters.h"
#include "simulation.h"
#include "helperfunctions.h"
//Parameters readParametersFromFile(const std::string& fileName);
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc<2)
  {
    std::cout << "Please enter name of data file after file name,"
      << "\ne.g. ProjectChrisWileySTL data.txt" << std::endl;
      return 0;
  }
  if (fileExists(argv[1])==false)
  {
    std::cout << "Please enter a VALID and EXISTING name of data file after file name." << std::endl;
    return 0;
  }

  //Parameters parameters = readParametersFromFile(argv[1]);

  //Simulation simulation(parameters);
  //std::auto_ptr<Simulation> simulation(new Simulation(
}
//---------------------------------------------------------------------------
