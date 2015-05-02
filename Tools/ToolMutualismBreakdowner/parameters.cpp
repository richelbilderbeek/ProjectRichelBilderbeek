#include "parameters.h"

Parameters::Parameters(
  const double any_desiccation_stress,
  const double any_initial_seagrass_density,
  const double any_initial_sulfide_density,
  const double any_oxygen_inhibition_strength,
  const double any_oxygen_production,
  const double any_seagrass_carrying_capacity,
  const double any_seagrass_growth_rate,
  const double any_sulfide_mol_per_seagrass_density,
  const double any_sulfide_toxicity,
  const int any_n_timesteps
) :
    desiccation_stress{any_desiccation_stress},
    initial_seagrass_density{any_initial_seagrass_density},
    initial_sulfide_density{any_initial_sulfide_density},
    oxygen_inhibition_strength{any_oxygen_inhibition_strength},
    oxygen_production{any_oxygen_production},
    seagrass_carrying_capacity{any_seagrass_carrying_capacity},
    seagrass_growth_rate{any_seagrass_growth_rate},
    sulfide_mol_per_seagrass_density{any_sulfide_mol_per_seagrass_density},
    sulfide_toxicity{any_sulfide_toxicity},
    n_timesteps{any_n_timesteps}
{

}
