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
  const Parameters parameters(
    0.01, //const double any_delta_t,
    0.02, //const double any_desiccation_stress,
    0.03, //const double any_initial_organic_matter_density,
    0.04, //const double any_initial_seagrass_density,
    0.05, //const double any_initial_sulfide_density,
    0.06, //const double any_loripes_density,
    0.07, //const double any_organic_matter_to_sulfide_factor,
    0.08, //const double any_organic_matter_to_sulfide_rate,
    0.09, //const double any_seagrass_carrying_capacity,
    0.10, //const double any_seagrass_growth_rate,
    0.11, //const double any_seagrass_to_organic_matter_factor,
    0.12, //const double any_sulfide_consumption_by_loripes,
    0.13, //const double any_sulfide_toxicity,
    14 //const int any_n_timesteps
  );
  {
    Parameters p(parameters);
    assert(p == parameters);
    p.delta_t += 1;
    assert(p != parameters);
  }
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
}
#endif

