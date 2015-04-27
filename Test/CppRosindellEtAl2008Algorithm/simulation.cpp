#include "simulation.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/numeric/conversion/cast.hpp>
#include "fileio.h"
#include "task.h"
#include "tree.h"

Simulation::Simulation(
  const std::vector<Task>& tasks,
  const std::vector<double>& specset,
  const std::string& result_output_filename
)
{
  #ifndef NDEBUG
  Test();
  #endif

  // setup tree object
  tree test;
  test.setseed(4);
  // find minimum speciation rate required
  double minspec = 1.0;
  for (int i = 0 ; i < boost::numeric_cast<int>(specset.size()) ; ++i)
  {
    if (minspec > specset[i])
    {
      minspec = specset[i];}
  }
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
      m_species_richnesses.push_back(temprichness);
      if (tasks[i].type)
      {
        out
          << tasks[i].area1 << " "
          << tasks[i].area2 << " "
          << specset[j] << " "
          << tasks[i].L << " "
          << " normal "
          << temprichness
          << " \n"
        ;
        std::cout
          << tasks[i].area1 << " "
          << tasks[i].area2 << " "
          << specset[j] << " "
          << tasks[i].L << " "
          << " normal "
          << temprichness
          << " \n"
        ;
      }
      else
      {
        out
          << tasks[i].area1 << " "
          << tasks[i].area2 << " "
          << specset[j] << " "
          << tasks[i].L << " "
          << " square "
          << temprichness
          << " \n"
        ;
        std::cout
          << tasks[i].area1 << " "
          << tasks[i].area2 << " "
          << specset[j] << " "
          << tasks[i].L << " "
          << " square "
          << temprichness
          << " \n"
        ;
      }
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
