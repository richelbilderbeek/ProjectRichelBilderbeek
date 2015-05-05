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
#include "simulation.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/numeric/conversion/cast.hpp>
#include "fileio.h"
#include "task.h"
#include "tree.h"
#include "result.h"
#include "dispersalkernel.h"

Simulation::Simulation(
  const std::vector<Task>& tasks,
  const std::vector<double>& speciation_rates,
  const Rng::Type rng_type,
  const std::string& result_output_filename,
  const int seed,
  const bool verbose
) : m_verbose{verbose}
{
  #ifndef NDEBUG
  Rng::Test();
  Test();
  #endif

  Rng rng(seed,rng_type);

  const double minimum_speciation_rate{
    *std::min_element(std::begin(speciation_rates),std::end(speciation_rates))
  };

  std::ofstream out(result_output_filename);
  for (const Task& task:tasks)
  {
    Tree tree(
      rng,
      task.m_survey_area_width,
      task.m_survey_area_length,
      minimum_speciation_rate,
      task.m_dispersal_distance,
      task.m_tolerance,
      task.m_dispersal_kernel_type
    );

    for (int i=1; ;++i)
    {
      tree.Update();
      if (i %
          (task.m_survey_area_width*task.m_survey_area_length*250)
        == 0
      )
      {
        if (tree.IsDone()) { break; }
      }
    }

    for (const double speciation_rate:speciation_rates)
    {
      const double richness{tree.GetRichness(speciation_rate)};
      const Result result(
        task.m_survey_area_width,
        task.m_survey_area_length,
        speciation_rate,
        task.m_dispersal_distance,
        task.m_dispersal_kernel_type,
        richness
      );
      m_results.push_back(result);
      out << result << '\n';
      if (m_verbose) { std::cout << result << std::endl; }
    }
  }
}


std::vector<double> ReadSpeciationRatesFromFile(
  const std::string& speciation_input_filename
)
{
  using ribi::fileio::FileIo;
  if (!FileIo().IsRegularFile(speciation_input_filename))
  {
    std::stringstream s;
    s << "speciation_input_filename '" << speciation_input_filename << "' not found" << '\n';
    throw std::runtime_error(s.str());
  }
  std::vector<double> speciation_rates;
  std::ifstream f(speciation_input_filename);
  while(!f.eof())
  {
    double speciation_rate = 0.0;
    f >> speciation_rate;
    speciation_rates.push_back(speciation_rate);
  }
  if (!speciation_rates.empty()) { speciation_rates.pop_back(); }
  return speciation_rates;
}
