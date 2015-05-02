#ifndef PARAMETERS_H
#define PARAMETERS_H

struct Parameters
{
  Parameters(
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
  );
  const double desiccation_stress;
  const double initial_seagrass_density;
  const double initial_sulfide_density;
  const double oxygen_inhibition_strength;
  const double oxygen_production;
  const double seagrass_carrying_capacity;
  const double seagrass_growth_rate;
  const double sulfide_mol_per_seagrass_density;
  const double sulfide_toxicity;
  const int n_timesteps;

};

#endif // PARAMETERS_H
