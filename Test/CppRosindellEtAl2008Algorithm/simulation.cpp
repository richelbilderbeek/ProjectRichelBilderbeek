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
  const std::string& result_output_filename,
  const int seed,
  const bool verbose
) : m_verbose{verbose}
{
  #ifndef NDEBUG
  Test();
  #endif

  Rng rng(seed);

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
    for (const double spec:speciation_rates)
    {
      const double richness{tree.GetRichness(spec)};
      const Result result(
        task.m_survey_area_width,
        task.m_survey_area_length,
        spec,
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
