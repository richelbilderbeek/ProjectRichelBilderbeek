#include "parameters.h"

#include <cassert>
#include <iostream>
#include <boost/units/io.hpp>

#include "loripesconsumptionfunction.h"

Parameters::Parameters()
  :
    delta_t{0.0},
    desiccation_stress{0.0},
    initial_organic_matter_density{0.0},
    initial_seagrass_density{0.0 * boost::units::si::species_per_square_meters},
    initial_sulfide_concentration{0.0},
    loripes_consumption_function{new InvertedExponentialConsumption},
    organic_matter_to_sulfide_factor{0.0},
    organic_matter_to_sulfide_rate{0.0},
    seagrass_carrying_capacity{0.0},
    seagrass_growth_rate{0.0},
    seagrass_to_organic_matter_factor{0.0},
    sulfide_consumption_by_loripes_rate{0.0},
    sulfide_diffusion_rate{0.0},
    n_timesteps{0}
{
  #ifndef NDEBUG
  Test();
  #endif
}

Parameters::Parameters(
  const double any_delta_t,
  const double any_desiccation_stress,
  const double any_initial_organic_matter_density,
  const ribi::units::SpeciesDensity any_initial_seagrass_density,
  const double any_initial_sulfide_density,
  const std::shared_ptr<LoripesConsumptionFunction>& any_loripes_consumption_function,
  const double any_organic_matter_to_sulfide_factor,
  const double any_organic_matter_to_sulfide_rate,
  const double any_seagrass_carrying_capacity,
  const double any_seagrass_growth_rate,
  const double any_seagrass_to_organic_matter_factor,
  const double any_sulfide_consumption_by_loripes,
  const double any_sulfide_diffusion_rate,
  const int any_n_timesteps
) :
    delta_t{any_delta_t},
    desiccation_stress{any_desiccation_stress},
    initial_organic_matter_density{any_initial_organic_matter_density},
    initial_seagrass_density{any_initial_seagrass_density},
    initial_sulfide_concentration{any_initial_sulfide_density},
    loripes_consumption_function{any_loripes_consumption_function},
    organic_matter_to_sulfide_factor{any_organic_matter_to_sulfide_factor},
    organic_matter_to_sulfide_rate{any_organic_matter_to_sulfide_rate},
    seagrass_carrying_capacity{any_seagrass_carrying_capacity},
    seagrass_growth_rate{any_seagrass_growth_rate},
    seagrass_to_organic_matter_factor{any_seagrass_to_organic_matter_factor},
    sulfide_consumption_by_loripes_rate{any_sulfide_consumption_by_loripes},
    sulfide_diffusion_rate{any_sulfide_diffusion_rate},
    n_timesteps{any_n_timesteps}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(delta_t > 0.0);
  assert(initial_seagrass_density >= 0.0 * boost::units::si::species_per_square_meter);
  assert(initial_sulfide_concentration >= 0.0);
  assert(seagrass_carrying_capacity >= 0.0);
  assert(seagrass_growth_rate >= 0.0);
}

double Parameters::GetRandom() const noexcept
{
  switch (std::rand() % 8)
  {
    case 0: return 10.0;
    case 1: return  5.0;
    case 2: return  1.0;
    case 3: return  0.1;
    case 4: return  0.5;
    case 5: return  0.01;
    case 6: return  0.005;
    case 7: return  0.001;
  }
  return 0.0;
}

void Parameters::SetRandom()
{
  delta_t = GetRandom();
  desiccation_stress = GetRandom();
  initial_organic_matter_density = GetRandom();
  initial_seagrass_density = GetRandom() * boost::units::si::species_per_square_meter;
  initial_sulfide_concentration = GetRandom();
  organic_matter_to_sulfide_factor = GetRandom();
  organic_matter_to_sulfide_rate = GetRandom();
  seagrass_carrying_capacity = GetRandom();
  seagrass_growth_rate = GetRandom();
  seagrass_to_organic_matter_factor = GetRandom();
  sulfide_consumption_by_loripes_rate = GetRandom();
  sulfide_diffusion_rate = GetRandom();
  n_timesteps = GetRandom();
}


std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept
{
  os
    << parameter.delta_t << " "
    << parameter.desiccation_stress << " "
    << parameter.initial_organic_matter_density << " "
    << parameter.initial_seagrass_density << " "
    << parameter.initial_sulfide_concentration << " "
    << *parameter.loripes_consumption_function << " "
    << parameter.organic_matter_to_sulfide_factor << " "
    << parameter.organic_matter_to_sulfide_rate << " "
    << parameter.seagrass_carrying_capacity << " "
    << parameter.seagrass_growth_rate << " "
    << parameter.seagrass_to_organic_matter_factor << " "
    << parameter.sulfide_consumption_by_loripes_rate << " "
    << parameter.sulfide_diffusion_rate << " "
    << parameter.n_timesteps
  ;
  return os;
}

std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept
{
  is
    >> parameter.delta_t
    >> parameter.desiccation_stress
    >> parameter.initial_organic_matter_density
    >> parameter.initial_seagrass_density
    >> parameter.initial_sulfide_concentration
    >> parameter.loripes_consumption_function
    >> parameter.organic_matter_to_sulfide_factor
    >> parameter.organic_matter_to_sulfide_rate
    >> parameter.seagrass_carrying_capacity
    >> parameter.seagrass_growth_rate
    >> parameter.seagrass_to_organic_matter_factor
    >> parameter.sulfide_consumption_by_loripes_rate
    >> parameter.sulfide_diffusion_rate
    >> parameter.n_timesteps
  ;
  return is;
}

bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return
       lhs.delta_t == rhs.delta_t
    && lhs.desiccation_stress == rhs.desiccation_stress
    && lhs.initial_organic_matter_density == rhs.initial_organic_matter_density
    && lhs.initial_seagrass_density == rhs.initial_seagrass_density
    && lhs.initial_sulfide_concentration == rhs.initial_sulfide_concentration
    && lhs.organic_matter_to_sulfide_factor == rhs.organic_matter_to_sulfide_factor
    && lhs.organic_matter_to_sulfide_rate == rhs.organic_matter_to_sulfide_rate
    && lhs.seagrass_carrying_capacity == rhs.seagrass_carrying_capacity
    && lhs.seagrass_growth_rate == rhs.seagrass_growth_rate
    && lhs.seagrass_to_organic_matter_factor == rhs.seagrass_to_organic_matter_factor
    && lhs.sulfide_consumption_by_loripes_rate == rhs.sulfide_consumption_by_loripes_rate
    && lhs.sulfide_diffusion_rate == rhs.sulfide_diffusion_rate
    && lhs.n_timesteps == rhs.n_timesteps
  ;

}

bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
