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
#include <fstream>
#include <stdexcept>
#include "simulation.h"
#include "nrrand.h"

int main(int argc, char **)
{
  {
    std::ofstream f("tmp.txt");
    Rng r(4,Rng::Type::bilderbeek);
    //NRrand r(4);
    for (int i=0; i!=1000; ++i) f << r.GetRandomNormal() << '\n';
  }
  #ifndef NDEBUG
  Rng::Test();
  Simulation::Test();
  #endif

  try
  {
    Simulation simulation(
      argc == 1 ? Rng::Type::rosindell : Rng::Type::bilderbeek
    );
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << '\n';
  }
  #ifndef NDEBUG
  std::cout << "Done (debug)" << std::endl;
  #endif
}
