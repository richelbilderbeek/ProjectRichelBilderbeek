#include "simulation.h"

#include <cassert>
#include <cmath>

#ifndef NDEBUG
void Simulation::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  std::vector<double> specset;
  {
    specset.push_back(0.1);
    specset.push_back(0.01);
    specset.push_back(0.001);
    specset.push_back(0.0001);
    specset.push_back(0.00001);
  }
  std::vector<Task> tasks;
  tasks.push_back(Task(10,10,1,true,0.01));

  Simulation simulation(tasks,specset);

  const std::vector<double> species_richnesses{
    simulation.GetSpeciesRichnesses()
  };
  assert(species_richnesses.size() == 5);
  assert(std::abs(species_richnesses[0]-34.0484) < 0.0001);
  assert(std::abs(species_richnesses[1]-16.6893) < 0.0001);
  assert(std::abs(species_richnesses[2]-8.98513) < 0.0001);
  assert(std::abs(species_richnesses[3]-7.0361) < 0.0001);
  assert(std::abs(species_richnesses[4]-4.88861) < 0.0001);
  assert(1==289);
}
#endif
