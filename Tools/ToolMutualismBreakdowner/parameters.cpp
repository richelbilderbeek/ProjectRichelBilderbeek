#include "parameters.h"
#include <cassert>

Parameters::Parameters(
  const double any_delta_t,
  const double any_desiccation_stress,
  const double any_initial_seagrass_density,
  const double any_initial_sulfide_density,
  const double any_loripes_density,
  const double any_oxygen_production,
  const double any_seagrass_carrying_capacity,
  const double any_seagrass_growth_rate,
  const double any_sulfide_consumption_by_loripes,
  const double any_sulfide_mol_per_seagrass_density,
  const double any_sulfide_toxicity,
  const int any_n_timesteps
) :
    delta_t{any_delta_t},
    desiccation_stress{any_desiccation_stress},
    initial_seagrass_density{any_initial_seagrass_density},
    initial_sulfide_concentration{any_initial_sulfide_density},
    loripes_density{any_loripes_density},
    oxygen_production{any_oxygen_production},
    seagrass_carrying_capacity{any_seagrass_carrying_capacity},
    seagrass_growth_rate{any_seagrass_growth_rate},
    sulfide_consumption_by_loripes{any_sulfide_consumption_by_loripes},
    sulfide_mol_per_seagrass_density{any_sulfide_mol_per_seagrass_density},
    sulfide_toxicity{any_sulfide_toxicity},
    n_timesteps{any_n_timesteps}
{
  assert(initial_seagrass_density == 1.0);
  assert(initial_sulfide_concentration == 0.0);
  assert(seagrass_growth_rate >= 0.0);
  assert(seagrass_carrying_capacity == 1.0);
  assert(oxygen_production >= 0.0);
}
