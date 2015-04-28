// Code inspired on:
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

