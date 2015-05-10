#include "parameters.h"

#include <cassert>
#include <iostream>
#include <boost/units/io.hpp>

#include "loripesconsumptionfunction.h"
#include "poisoningfunction.h"
Parameters::Parameters()
  :
    delta_t{0.1},
    desiccation_stress{0.0},
    initial_loripes_density{0.0 * boost::units::si::species_per_square_meters},
    initial_organic_matter_density{0.0},
    initial_seagrass_density{0.0 * boost::units::si::species_per_square_meters},
    initial_sulfide_concentration{0.0 * boost::units::si::mole / boost::units::si::cubic_meter},
    loripes_consumption_function{new InvertedExponentialConsumption},
    organic_matter_to_sulfide_factor{0.0},
    organic_matter_to_sulfide_rate{0.0},
    poisoning_function{new InvertedExponentialPoisoning},
    seagrass_carrying_capacity{0.0 * boost::units::si::species_per_square_meters},
    seagrass_growth_rate{0.0},
    seagrass_to_organic_matter_factor{0.0},
    sulfide_consumption_by_loripes_rate{0.0},
    sulfide_diffusion_rate{0.0},
    n_timesteps{1}
{
  #ifndef NDEBUG
  Test();
  #endif
}

Parameters::Parameters(
  const double any_delta_t,
  const double any_desiccation_stress,
  const ribi::units::SpeciesDensity any_initial_loripes_density,
  const double any_initial_organic_matter_density,
  const ribi::units::SpeciesDensity any_initial_seagrass_density,
  const ribi::units::Concentration any_initial_sulfide_density,
  const std::shared_ptr<LoripesConsumptionFunction>& any_loripes_consumption_function,
  const double any_organic_matter_to_sulfide_factor,
  const double any_organic_matter_to_sulfide_rate,
  const std::shared_ptr<PoisoningFunction>& any_poisoning_function,
  const ribi::units::SpeciesDensity any_seagrass_carrying_capacity,
  const double any_seagrass_growth_rate,
  const double any_seagrass_to_organic_matter_factor,
  const double any_sulfide_consumption_by_loripes,
  const double any_sulfide_diffusion_rate,
  const int any_n_timesteps
) :
    delta_t{any_delta_t},
    desiccation_stress{any_desiccation_stress},
    initial_loripes_density{any_initial_loripes_density},
    initial_organic_matter_density{any_initial_organic_matter_density},
    initial_seagrass_density{any_initial_seagrass_density},
    initial_sulfide_concentration{any_initial_sulfide_density},
    loripes_consumption_function{any_loripes_consumption_function},
    organic_matter_to_sulfide_factor{any_organic_matter_to_sulfide_factor},
    organic_matter_to_sulfide_rate{any_organic_matter_to_sulfide_rate},
    poisoning_function{any_poisoning_function},
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
  using boost::units::si::species_per_square_meter;
  using boost::units::si::mole;
  using boost::units::si::cubic_meter;
  assert(delta_t > 0.0);
  assert(initial_loripes_density >= 0.0 * species_per_square_meter);
  assert(initial_seagrass_density >= 0.0 * species_per_square_meter);
  assert(initial_sulfide_concentration >= 0.0 * mole / cubic_meter);
  assert(seagrass_carrying_capacity >= 0.0 * species_per_square_meter);
  assert(seagrass_growth_rate >= 0.0);
  assert(loripes_consumption_function);
  assert(poisoning_function);
}

Parameters Parameters::GetTest(const int /* i */)
{
  const auto loripes_consumption_function
    = std::make_shared<InvertedExponentialConsumption>(0.05);
  assert(loripes_consumption_function);
  assert(loripes_consumption_function.get());
  const auto poisoning_function
    = std::make_shared<InvertedExponentialPoisoning>(0.05,1.0);
  assert(poisoning_function);
  assert(poisoning_function.get());
  using boost::units::si::species_per_square_meters;
  using boost::units::si::mole;
  using boost::units::si::cubic_meter;
  const Parameters p(
    0.1, //any_delta_t,
    0.1, //any_desiccation_stress,
    0.1 * species_per_square_meters, //initial_loripes_density,
    0.0, //any_initial_organic_matter_density,
    0.1 * species_per_square_meters, //initial_seagrass_density,
    0.0 * mole / cubic_meter, //any_initial_sulfide_density,
    loripes_consumption_function,
    0.1, //const double any_organic_matter_to_sulfide_factor,
    0.1, //const double any_organic_matter_to_sulfide_rate,
    poisoning_function,
    1.0 * species_per_square_meters, //any_seagrass_carrying_capacity,
    0.1, //const double any_seagrass_growth_rate,
    0.1, //any_seagrass_to_organic_matter_factor,
    0.1, //any_sulfide_consumption_by_loripes,
    0.1, //any_sulfide_diffusion_rate,
    100 //any_n_timesteps
  );
  return p;
}

void Parameters::SetDeltaT(const double any_delta_t)
{
  if (any_delta_t <= 0.0)
  {
    std::stringstream s;
    s << "Parameters::SetDeltaT: "
      << "any_delta_t cannot be less or equal to zero, "
      << "obtained value " << any_delta_t;
    throw std::logic_error(s.str());
  }
}

std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept
{
  os
    << parameter.GetDeltaT() << " "
    << parameter.desiccation_stress << " "
    << parameter.initial_loripes_density << " "
    << parameter.initial_organic_matter_density << " "
    << parameter.initial_seagrass_density << " "
    << parameter.initial_sulfide_concentration << " "
    << *parameter.loripes_consumption_function << " "
    << parameter.organic_matter_to_sulfide_factor << " "
    << parameter.organic_matter_to_sulfide_rate << " "
    << *parameter.poisoning_function << " "
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
  {
    double delta_t{0.0};
    is >> delta_t;
    parameter.SetDeltaT(delta_t);
  }
  is
    >> parameter.desiccation_stress
    >> parameter.initial_loripes_density
    >> parameter.initial_organic_matter_density
    >> parameter.initial_seagrass_density
    >> parameter.initial_sulfide_concentration
    >> parameter.loripes_consumption_function
    >> parameter.organic_matter_to_sulfide_factor
    >> parameter.organic_matter_to_sulfide_rate
    >> parameter.poisoning_function
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
       lhs.GetDeltaT() == rhs.GetDeltaT()
    && lhs.desiccation_stress == rhs.desiccation_stress
    && lhs.initial_loripes_density == rhs.initial_loripes_density
    && lhs.initial_organic_matter_density == rhs.initial_organic_matter_density
    && lhs.initial_seagrass_density == rhs.initial_seagrass_density
    && lhs.initial_sulfide_concentration == rhs.initial_sulfide_concentration
    && lhs.loripes_consumption_function->ToStr() == rhs.loripes_consumption_function->ToStr()
    && lhs.organic_matter_to_sulfide_factor == rhs.organic_matter_to_sulfide_factor
    && lhs.organic_matter_to_sulfide_rate == rhs.organic_matter_to_sulfide_rate
    && lhs.poisoning_function->ToStr() == rhs.poisoning_function->ToStr()
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
