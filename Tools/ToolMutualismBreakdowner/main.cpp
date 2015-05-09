#include "parameters.h"
#include "simulation.h"
#include "units.h"

#include <iostream>

int main()
{
  ribi::units::Test();
  ribi::units::TestSpeciesDensity();
  Parameters p;
  p.SetRandom();
  p.n_timesteps = 10;
  p.delta_t = 0.1;
  Simulation s(p);
  s.Run();
  std::cout << s << std::endl;
}
