#include "parameters.h"
#include "simulation.h"

#include <iostream>

int main()
{
  Parameters p;
  p.SetRandom();
  p.n_timesteps = 10;
  p.delta_t = 0.1;
  Simulation s(p);
  s.Run();
  std::cout << s << std::endl;
}
