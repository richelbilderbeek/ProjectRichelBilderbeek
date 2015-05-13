#include "parameters.h"
#include "timesimulation.h"
#include "units.h"

#include <iostream>

int main()
{
  try
  {
    #ifndef NDEBUG
    ribi::units::Test();
    ribi::units::TestSpeciesDensity();
    #endif // NDEBUG
    Parameters p = Parameters::GetTest(0);
    TimeSimulation s(p);
    s.Run();
    std::cout << s << std::endl;
    std::cout << "SIM FINISHED SUCCESSFULLY" << std::endl;
  }
  catch(std::logic_error& e)
  {
    std::cerr << "main: " << e.what() << std::endl;
    std::cout << "SIM FINISHED WITH ERROR" << std::endl;
  }
  std::cout << "DONE" << std::endl;
}
