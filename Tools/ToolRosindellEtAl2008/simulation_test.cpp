//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek
Original version by James Rosindell

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//---------------------------------------------------------------------------
#ifndef NDEBUG
#include "simulation.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iterator>

#include "fileio.h"
#include "testtimer.h"
#include "tree.h"

void Simulation::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
    Rng::Test();
    Tree::Test();
  }
  const bool thorough{true};
  const ribi::TestTimer test_timer(__func__,__FILE__,thorough ? 20.0 : 10.0);
  //Test some known runs
  {
    std::vector<double> specset;
    {
      specset.push_back(0.1);
      specset.push_back(0.01);
    }
    std::vector<Task> tasks;
    tasks.push_back(Task(10,10,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(20,10,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,20,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,10,2,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,10,1,DispersalKernel::square,0.1));
    tasks.push_back(Task(10,10,1,DispersalKernel::normal,0.01));

    Simulation simulation(
      tasks,
      specset,
      Rng::Type::rosindell,
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
  //Test some known runs from file
  if (thorough)
  {
    using ribi::fileio::FileIo;

    const std::string tasks_input_filename{"tmp_tasksfile.txt"};
    const std::string speciation_input_filename{"tmp_speciationrates.txt"};
    const std::string results_output_filename{"tmp_resultsfile.txt"};

    {
      std::vector<double> speciation_rates;
      {
        speciation_rates.push_back(0.1);
        speciation_rates.push_back(0.01);
      }
      std::ofstream f(speciation_input_filename);
      std::copy(std::begin(speciation_rates),std::end(speciation_rates),std::ostream_iterator<double>(f," "));
    }
    assert(FileIo().IsRegularFile(speciation_input_filename));

    {
      std::vector<Task> tasks;
      tasks.push_back(Task(10,10,1,DispersalKernel::normal,0.1));
      tasks.push_back(Task(20,10,1,DispersalKernel::normal,0.1));
      tasks.push_back(Task(10,20,1,DispersalKernel::normal,0.1));
      tasks.push_back(Task(10,10,2,DispersalKernel::normal,0.1));
      tasks.push_back(Task(10,10,1,DispersalKernel::square,0.1));
      tasks.push_back(Task(10,10,1,DispersalKernel::normal,0.01));
      std::ofstream f(tasks_input_filename);
      std::copy(std::begin(tasks),std::end(tasks),std::ostream_iterator<Task>(f,"\n"));
    }

    assert(FileIo().IsRegularFile(tasks_input_filename));

    Simulation simulation(
      Rng::Type::rosindell,
      tasks_input_filename,
      speciation_input_filename,
      results_output_filename,
      4,
      true
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
  {
    std::vector<double> specset;
    {
      specset.push_back(0.1);
      specset.push_back(0.01);
    }
    std::vector<Task> tasks;
    tasks.push_back(Task(10,10,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(20,10,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,20,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,10,2,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,10,1,DispersalKernel::square,0.1));
    tasks.push_back(Task(10,10,1,DispersalKernel::normal,0.01));

    Simulation simulation(
      tasks,
      specset,
      Rng::Type::bilderbeek,
      "resultsfile.txt", //results_output_filename
      4, //seed
      true //verbose
    );

    const std::vector<Result> results{
      simulation.GetResults()
    };
  }
}
#endif
