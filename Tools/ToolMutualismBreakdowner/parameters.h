#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iosfwd>

struct Parameters
{
  Parameters()
    :
      delta_t{0.0},
      desiccation_stress{0.0},
      initial_organic_matter_density{0.0},
      initial_seagrass_density{0.0},
      initial_sulfide_concentration{0.0},
      //loripes_density{0.0},
      organic_matter_to_sulfide_factor{0.0},
      organic_matter_to_sulfide_rate{0.0},
      seagrass_carrying_capacity{0.0},
      seagrass_growth_rate{0.0},
      seagrass_to_organic_matter_factor{0.0},
      sulfide_consumption_by_loripes_rate{0.0},
      sulfide_diffusion_rate{0.0},
      //sulfide_toxicity{0.0},
      n_timesteps{0}
  {

  }
  Parameters(
    const double any_delta_t,
    const double any_desiccation_stress,
    const double any_initial_organic_matter_density,
    const double any_initial_seagrass_density,
    const double any_initial_sulfide_density,
    //const double any_loripes_density,
    const double any_organic_matter_to_sulfide_factor,
    const double any_organic_matter_to_sulfide_rate,
    const double any_seagrass_carrying_capacity,
    const double any_seagrass_growth_rate,
    const double any_seagrass_to_organic_matter_factor,
    const double any_sulfide_consumption_by_loripes,
    const double any_sulfide_diffusion_rate,
    //const double any_sulfide_toxicity,
    const int any_n_timesteps
  );
  double delta_t;
  double desiccation_stress;
  double initial_organic_matter_density;
  double initial_seagrass_density;
  double initial_sulfide_concentration;
  //double loripes_density;
  double organic_matter_to_sulfide_factor;
  double organic_matter_to_sulfide_rate;
  double seagrass_carrying_capacity;
  double seagrass_growth_rate;
  double seagrass_to_organic_matter_factor;
  double sulfide_consumption_by_loripes_rate;
  double sulfide_diffusion_rate;
  //double sulfide_toxicity;
  int n_timesteps;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept;
bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept;
std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept;

#endif // PARAMETERS_H
