// RosindellEtAl2008, refactoring of code of Rosindell et al., 2008
// (C) 2015 Richel Bilderbeek
//
// The original source code is writtem by James Rosindell
// and accompanies the following article:
//
// "A COALESCENCE APPROACH TO SPATIAL NEUTRAL ECOLOGY"
// James Rosindell, Yan Wong, Rampal Etienne

#include <cassert>
#include <iostream>
#include <stdexcept>
#include "simulation.h"

int main()
{
  #ifndef NDEBUG
  Simulation::Test();
  #endif

  try
  {
    Simulation simulation;
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << '\n';
  }
  #ifndef NDEBUG
  std::cout << "Done (debug)" << std::endl;
  #endif
}
