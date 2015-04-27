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

  // setup tree object
  tree test(seed);

  // find minimum speciation rate required
  const double minspec{
    *std::min_element(std::begin(specset),std::end(specset))
  };
  // do the calculations in a big double loop
  std::ofstream out;
  out.open(result_output_filename);
  for (int i = 0 ; i < boost::numeric_cast<int>(tasks.size()) ; ++i)
  {
    // produce tree
    test.maketree(
      tasks[i].area1,
      tasks[i].area2,
      minspec,
      tasks[i].L,
      tasks[i].tol,
      tasks[i].type
    );
    for (int j = 0 ; j < boost::numeric_cast<int>(specset.size()) ; j ++)
    {
      // evaluate species richness for a variety of different speciation rates
      const double temprichness = test.get_richness(specset[j]);
      const Result result(
        tasks[i].area1,
        tasks[i].area2,
        specset[j],
        tasks[i].L,
        tasks[i].type,
        temprichness
      );
      m_results.push_back(result);
      out << result;
      if (m_verbose) { std::cout << result; }
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
