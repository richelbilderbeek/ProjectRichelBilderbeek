#include "parameters.h"
#include <cassert>

Parameters::Parameters(
  const double any_delta_t,
  const double any_desiccation_stress,
  const double any_initial_organic_matter_density,
  const double any_initial_seagrass_density,
  const double any_initial_sulfide_density,
  const double any_loripes_density,
  const double any_organic_matter_to_sulfide_factor,
  const double any_organic_matter_to_sulfide_rate,
  const double any_seagrass_carrying_capacity,
  const double any_seagrass_growth_rate,
  const double any_seagrass_to_organic_matter_factor,
  const double any_sulfide_consumption_by_loripes,
  const double any_sulfide_toxicity,
  const int any_n_timesteps
) :
    delta_t{any_delta_t},
    desiccation_stress{any_desiccation_stress},
    initial_organic_matter_density{any_initial_organic_matter_density},
    initial_seagrass_density{any_initial_seagrass_density},
    initial_sulfide_concentration{any_initial_sulfide_density},
    loripes_density{any_loripes_density},
    organic_matter_to_sulfide_factor{any_organic_matter_to_sulfide_factor},
    organic_matter_to_sulfide_rate{any_organic_matter_to_sulfide_rate},
    seagrass_carrying_capacity{any_seagrass_carrying_capacity},
    seagrass_growth_rate{any_seagrass_growth_rate},
    seagrass_to_organic_matter_factor{any_seagrass_to_organic_matter_factor},
    sulfide_consumption_by_loripes_rate{any_sulfide_consumption_by_loripes},
    sulfide_toxicity{any_sulfide_toxicity},
    n_timesteps{any_n_timesteps}
{
  assert(delta_t > 0.0);
  assert(initial_seagrass_density >= 0.0);
  assert(initial_sulfide_concentration >= 0.0);
  assert(seagrass_carrying_capacity >= 0.0);
  assert(seagrass_growth_rate >= 0.0);
}
