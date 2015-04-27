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
  //Test some known runs
  {
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

    Simulation simulation(
      tasks,
      specset,
      "resultsfile.txt", //results_output_filename
      4, //seed
      true //verbose
    );

    const std::vector<Result> results{
      simulation.GetResults()
    };
    assert(results.size() == 12);
    assert(std::abs(results[ 0].GetSpeciesRichness()-34.0484) < 0.0001);
    assert(std::abs(results[ 1].GetSpeciesRichness()-16.6893) < 0.0001);
    assert(std::abs(results[ 2].GetSpeciesRichness()-71.3487) < 0.0001);
    assert(std::abs(results[ 3].GetSpeciesRichness()-23.975 ) < 0.0001);
    assert(std::abs(results[ 4].GetSpeciesRichness()-70.9428) < 0.0001);
    assert(std::abs(results[ 5].GetSpeciesRichness()-23.4636) < 0.0001);
    assert(std::abs(results[ 6].GetSpeciesRichness()-48.4659) < 0.0001);
    assert(std::abs(results[ 7].GetSpeciesRichness()-23.7277) < 0.0001);
    assert(std::abs(results[ 8].GetSpeciesRichness()-37.5131) < 0.0001);
    assert(std::abs(results[ 9].GetSpeciesRichness()-12.9071) < 0.0001);
    assert(std::abs(results[10].GetSpeciesRichness()-38.2425) < 0.0001);
    assert(std::abs(results[11].GetSpeciesRichness()-14.5789) < 0.0001);
  }
}
#endif
