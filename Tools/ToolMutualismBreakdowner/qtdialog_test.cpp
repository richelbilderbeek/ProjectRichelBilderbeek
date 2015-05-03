#ifndef NDEBUG
#include "qtdialog.h"

#include <cassert>
#include <fstream>
#include "fileio.h"

void QtDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  const Parameters parameters(
    0.01, //const double any_delta_t,
    0.12, //const double any_desiccation_stress,
    0.23, //const double any_initial_organic_matter_density,
    0.34, //const double any_initial_seagrass_density,
    0.45, //const double any_initial_sulfide_density,
    0.56, //const double any_loripes_density,
    0.67, //const double any_organic_matter_to_sulfide_factor,
    0.78, //const double any_organic_matter_to_sulfide_rate,
    0.89, //const double any_seagrass_carrying_capacity,
    0.90, //const double any_seagrass_growth_rate,
    0.01, //const double any_seagrass_to_organic_matter_factor,
    0.22, //const double any_sulfide_consumption_by_loripes,
    0.23, //const double any_sulfide_toxicity,
    14 //const int any_n_timesteps
  );
  {
    QtDialog d;
    d.SetParameters(parameters);
    assert(d.GetParameters() == parameters);
  }
}
#endif


