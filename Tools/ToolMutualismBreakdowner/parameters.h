#ifndef PARAMETERS_H
#define PARAMETERS_H

struct Parameters
{
  Parameters(
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
  );
  const double delta_t;
  const double desiccation_stress;
  const double initial_organic_matter_density;
  const double initial_seagrass_density;
  const double initial_sulfide_concentration;
  const double loripes_density;
  const double organic_matter_to_sulfide_factor;
  const double organic_matter_to_sulfide_rate;
  const double seagrass_carrying_capacity;
  const double seagrass_growth_rate;
  const double seagrass_to_organic_matter_factor;
  const double sulfide_consumption_by_loripes_rate;
  const double sulfide_toxicity;
  const int n_timesteps;

};

#endif // PARAMETERS_H
