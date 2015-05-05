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
#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>

#include "rng.h"
#include "task.h"
#include "result.h"

std::vector<double> ReadSpeciationRatesFromFile(
  const std::string& speciation_input_filename
);

struct Simulation
{
  ///Maintain interface of original article
  ///tasks_input_filename: the file that contains a list of simulations that are required
  ///speciation_input_filename: a list of speciation rates we wish to simulate
  ///result_output_filename: the file that will output the results of the simulations to
  Simulation(
    const Rng::Type rng_type,
    const std::string& tasks_input_filename = "tasksfile.txt",
    const std::string& speciation_input_filename = "speciationrates.txt",
    const std::string& result_output_filename = "resultsfile.txt",
    const int seed = 4,
    const bool verbose = true
  ) : Simulation(
    ReadTasksFromFile(tasks_input_filename),
    ReadSpeciationRatesFromFile(speciation_input_filename),
    rng_type,
    result_output_filename,
    seed,
    verbose
  )
  {}

  ///Cleaner interface
  Simulation(
    const std::vector<Task>& tasks,
    const std::vector<double>& speciation_rates,
    const Rng::Type rng_type = Rng::Type::rosindell,
    const std::string& result_output_filename = "resultsfile.txt",
    const int seed = 4,
    const bool verbose = true
  );


  std::vector<Result> GetResults() const noexcept { return m_results; }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:

  std::vector<Result> m_results;

  const bool m_verbose;

};


#endif // SIMULATION_H
