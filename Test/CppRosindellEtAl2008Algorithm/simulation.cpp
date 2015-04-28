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
  const std::vector<double>& specset,
  const std::string& result_output_filename,
  const int seed,
  const bool verbose
) : m_verbose{verbose}
{
  #ifndef NDEBUG
  Test();
  #endif

  Rng rng(seed);

  // minimum speciation rate required
  const double minspec{
    *std::min_element(std::begin(specset),std::end(specset))
  };

  std::ofstream out;
  out.open(result_output_filename);
  for (const Task& task:tasks)
  {
    Tree tree(
      rng,
      task.m_survey_area_width,
      task.m_survey_area_length,
      minspec,
      task.m_dispersal_distance,
      task.m_tolerance,
      task.m_dispersal_kernel_type
    );
    for (const double spec:specset)
    {
      // evaluate species richness for a variety of different speciation rates
      const double temprichness = tree.get_richness(spec);
      const Result result(
        task.m_survey_area_width,
        task.m_survey_area_length,
        spec,
        task.m_dispersal_distance,
        task.m_dispersal_kernel_type,
        temprichness
      );
      m_results.push_back(result);
      out << result << '\n';
      if (m_verbose) { std::cout << result << std::endl; }
    }
  }
  out.close();
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
  std::vector<double> specset;
  std::ifstream ifdata;
  ifdata.open(speciation_input_filename);
  double tempspec;
  ifdata >> tempspec;
  while(!ifdata.eof())
  {
    specset.push_back(tempspec);
    ifdata >> tempspec;
  }
  ifdata.close();
  return specset;

}
