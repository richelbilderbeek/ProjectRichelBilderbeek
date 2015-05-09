#ifndef NDEBUG
#include "parameters.h"

#include <cassert>
#include <fstream>
#include "fileio.h"

void Parameters::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  Parameters parameters; parameters.SetRandom();
  {
    Parameters p(parameters);
    assert(p == parameters);
    p.sulfide_diffusion_rate += 0.1;
    assert(p != parameters);
  }
  //File I/O
  {
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters;
    }
    std::ifstream f(filename);
    Parameters parameters_too;
    f >> parameters_too;
    assert(parameters_too == parameters);
  }
  //File I/O of initial_species_density
  {

    ribi::units::SpeciesDensity d{
      23.45 * boost::units::si::species_per_square_meter
    };
    parameters.initial_seagrass_density = d;

    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters;
    }
    std::ifstream f(filename);
    Parameters parameters_too;
    f >> parameters_too;
    assert(parameters_too == parameters);
    assert(parameters_too.initial_seagrass_density == d);
  }
}
#endif

