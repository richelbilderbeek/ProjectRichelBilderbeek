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
  }
  std::vector<Task> tasks;
  tasks.push_back(Task(10,10,1,true,0.1));
  tasks.push_back(Task(20,10,1,true,0.1));
  tasks.push_back(Task(10,20,1,true,0.1));
  tasks.push_back(Task(10,10,2,true,0.1));
  tasks.push_back(Task(10,10,1,false,0.1));
  tasks.push_back(Task(10,10,1,true,0.01));

  Simulation simulation(tasks,specset);

  const std::vector<double> species_richnesses{
    simulation.GetSpeciesRichnesses()
  };
  assert(species_richnesses.size() == 12);
  assert(std::abs(species_richnesses[ 0]-34.0484) < 0.0001);
  assert(std::abs(species_richnesses[ 1]-16.6893) < 0.0001);
  assert(std::abs(species_richnesses[ 2]-71.3487) < 0.0001);
  assert(std::abs(species_richnesses[ 3]-23.975 ) < 0.0001);
  assert(std::abs(species_richnesses[ 4]-70.9428) < 0.0001);
  assert(std::abs(species_richnesses[ 5]-23.4636) < 0.0001);
  assert(std::abs(species_richnesses[ 6]-48.4659) < 0.0001);
  assert(std::abs(species_richnesses[ 7]-23.7277) < 0.0001);
  assert(std::abs(species_richnesses[ 8]-37.5131) < 0.0001);
  assert(std::abs(species_richnesses[ 9]-12.9071) < 0.0001);
  assert(std::abs(species_richnesses[10]-38.2425) < 0.0001);
  assert(std::abs(species_richnesses[11]-14.5789) < 0.0001);
  assert(1==289);
}
#endif
