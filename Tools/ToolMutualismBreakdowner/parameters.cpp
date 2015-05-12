#include "parameters.h"

#include <cassert>
#include <iostream>
#include <boost/units/io.hpp>

#include "sulfideconsumptionfunction.h"
#include "poisoningfunction.h"
#include "seagrassgrowthfunction.h"
#include "sulfideproductionfunction.h"

Parameters::Parameters()
  :
    delta_t{0.1},
    detoxification_max_rate{0.0},
    detoxification_minimum{0.0},
    detoxification_rate{0.0},
    initial_loripes_density{0.0 * boost::units::si::species_per_square_meters},
    initial_organic_matter_density{0.0},
    initial_seagrass_density{0.0 * boost::units::si::species_per_square_meters},
    initial_sulfide_concentration{0.0 * boost::units::si::mole / boost::units::si::cubic_meter},
    m_loripes_consumption_function{new LinearConsumption},
    mutualism_breakdown_max{0.0},
    mutualism_breakdown_r0{0.0},
    mutualism_breakdown_rate{0.0},
    organic_matter_addition{0.0},
    organic_matter_breakdown{0.0},
    organic_matter_capture{0.0},
    organic_matter_to_sulfide_factor{0.0},
    organic_matter_to_sulfide_rate{0.0},
    m_poisoning_function{std::make_shared<InvertedExponentialPoisoning>()},
    recruitment_max{0.1},
    recruitment_rate{0.0},
    m_seagrass_growth_function{std::make_shared<SeagrassStressedLogisticGrowth>()},
    seagrass_carrying_capacity{0.0 * boost::units::si::species_per_square_meters},
    seagrass_growth_rate{0.0},
    seagrass_to_organic_matter_factor{0.0},
    sulfide_diffusion_rate{0.0},
    m_sulfide_production_function{std::make_shared<LinearSulfideProduction>()},
    n_timesteps{1}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_poisoning_function);
  assert(m_seagrass_growth_function);
}

Parameters::Parameters(
  const double any_delta_t,
  const double any_detoxification_max_rate,
  const double any_detoxification_minimum,
  const double any_detoxification_rate,
  const ribi::units::SpeciesDensity any_initial_loripes_density,
  const double any_initial_organic_matter_density,
  const ribi::units::SpeciesDensity any_initial_seagrass_density,
  const ribi::units::Concentration any_initial_sulfide_density,
  const std::shared_ptr<SulfideConsumptionFunction>& any_loripes_consumption_function,
  const double any_mutualism_breakdown_max,
  const double any_mutualism_breakdown_r0,
  const double any_mutualism_breakdown_rate,
  const double any_organic_matter_addition,
  const double any_organic_matter_breakdown,
  const double any_organic_matter_capture,
  const double any_organic_matter_to_sulfide_factor,
  const double any_organic_matter_to_sulfide_rate,
  const std::shared_ptr<PoisoningFunction>& any_poisoning_function,
  const double any_recruitment_max,
  const double any_recruitment_rate,
  std::shared_ptr<SeagrassGrowthFunction> seagrass_growth_function,
  const ribi::units::SpeciesDensity any_seagrass_carrying_capacity,
  const double any_seagrass_growth_rate,
  const double any_seagrass_to_organic_matter_factor,
  const double any_sulfide_diffusion_rate,
  std::shared_ptr<SulfideProductionFunction> sulfide_production_function,
  const int any_n_timesteps
) :
    delta_t{any_delta_t},
    detoxification_max_rate{any_detoxification_max_rate},
    detoxification_minimum{any_detoxification_minimum},
    detoxification_rate{any_detoxification_rate},
    initial_loripes_density{any_initial_loripes_density},
    initial_organic_matter_density{any_initial_organic_matter_density},
    initial_seagrass_density{any_initial_seagrass_density},
    initial_sulfide_concentration{any_initial_sulfide_density},
    m_loripes_consumption_function{any_loripes_consumption_function},
    mutualism_breakdown_max{any_mutualism_breakdown_max},
    mutualism_breakdown_r0{any_mutualism_breakdown_r0},
    mutualism_breakdown_rate{any_mutualism_breakdown_rate},
    organic_matter_addition{any_organic_matter_addition},
    organic_matter_breakdown{any_organic_matter_breakdown},
    organic_matter_capture{any_organic_matter_capture},
    organic_matter_to_sulfide_factor{any_organic_matter_to_sulfide_factor},
    organic_matter_to_sulfide_rate{any_organic_matter_to_sulfide_rate},
    m_poisoning_function{any_poisoning_function},
    recruitment_max{any_recruitment_max},
    recruitment_rate{any_recruitment_rate},
    m_seagrass_growth_function{seagrass_growth_function},
    seagrass_carrying_capacity{any_seagrass_carrying_capacity},
    seagrass_growth_rate{any_seagrass_growth_rate},
    seagrass_to_organic_matter_factor{any_seagrass_to_organic_matter_factor},
    sulfide_diffusion_rate{any_sulfide_diffusion_rate},
    m_sulfide_production_function{sulfide_production_function},
    n_timesteps{any_n_timesteps}
{
  #ifndef NDEBUG
  Test();
  #endif
  using boost::units::si::species_per_square_meter;
  using boost::units::si::mole;
  using boost::units::si::cubic_meter;
  if (delta_t <= 0.0)
  {
    throw std::logic_error("Parameters::Parameters: delta_t must be above zero");
  }
  assert(initial_loripes_density >= 0.0 * species_per_square_meter);
  assert(initial_seagrass_density >= 0.0 * species_per_square_meter);
  assert(initial_sulfide_concentration >= 0.0 * mole / cubic_meter);
  assert(seagrass_carrying_capacity >= 0.0 * species_per_square_meter);
  assert(seagrass_growth_rate >= 0.0);
  assert(m_loripes_consumption_function);
  assert(m_seagrass_growth_function);
  assert(m_poisoning_function);
  assert(m_sulfide_production_function);
}

Parameters Parameters::GetTest(const int /* i */)
{
  const auto loripes_consumption_function
    = std::make_shared<LinearConsumption>(0.05);
  const auto poisoning_function
    = std::make_shared<InvertedExponentialPoisoning>(0.01,0.05,1.0);
  const auto seagrass_growth_function
    = std::make_shared<SeagrassStressedLogisticGrowth>(
      0.5 * boost::units::si::species_per_square_meter, //carrying_capacity
      1.1 * boost::units::si::per_second, //growth_rate
      0.1 * boost::units::si::per_second //stress_rate
    );
  const auto sulfide_production_function
    = std::make_shared<LinearSulfideProduction>(
      0.5
    );


  using boost::units::si::species_per_square_meters;
  using boost::units::si::mole;
  using boost::units::si::cubic_meter;
  const Parameters p(
    0.1, //any_delta_t,
    0.1, //const double any_detoxification_max_rate,
    0.1, //const double any_detoxification_minimum,
    0.1, //const double any_detoxification_rate,
    0.1 * species_per_square_meters, //initial_loripes_density,
    0.0, //any_initial_organic_matter_density,
    0.1 * species_per_square_meters, //initial_seagrass_density,
    0.0 * mole / cubic_meter, //any_initial_sulfide_density,
    loripes_consumption_function,
    0.1, //const double any_mutualism_breakdown_max,
    0.1, //const double any_mutualism_breakdown_r0,
    0.1, //const double any_mutualism_breakdown_rate,
    0.1, //const double any_organic_matter_addition,
    0.1, //const double any_organic_matter_breakdown,
    0.1, //const double any_organic_matter_capture,
    0.1, //const double any_organic_matter_to_sulfide_factor,
    0.1, //const double any_organic_matter_to_sulfide_rate,
    poisoning_function,
    0.1, //const double any_recruitment_max,
    0.1, //const double any_recruitment_rate,
    seagrass_growth_function,
    1.0 * species_per_square_meters, //any_seagrass_carrying_capacity,
    0.1, //const double any_seagrass_growth_rate,
    0.1, //any_seagrass_to_organic_matter_factor,
    0.1, //any_sulfide_diffusion_rate,
    sulfide_production_function,
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
  delta_t = any_delta_t;
}

void Parameters::SetInitialSeagrassDensity(const ribi::units::SpeciesDensity any_initial_seagrass_density) noexcept
{
  if (any_initial_seagrass_density < 0.0 * boost::units::si::species_per_square_meter)
  {
    std::stringstream s;
    s << "SetInitialSeagrassDensity: "
      << "any_initial_seagrass_density cannot be less than zero, "
      << "obtained value " << any_initial_seagrass_density
    ;
    throw std::logic_error(s.str());
  }
  initial_seagrass_density = any_initial_seagrass_density;
}

void Parameters::SetPoisoningFunction(const std::shared_ptr<PoisoningFunction> any_poisoning_function)
{
  if (!any_poisoning_function)
  {
    std::stringstream s;
    s << "Parameters::SetPoisoningFunction: "
      << "any_poisoning_function must not be null";
    throw std::logic_error(s.str());
  }
  this->m_poisoning_function = any_poisoning_function;
}

std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept
{
  os
    << parameter.GetDeltaT() << " "
    << parameter.GetInitialLoripesDensity() << " "
    << parameter.GetInitialOrganicMatterDensity() << " "
    << parameter.GetInitialSeagrassDensity() << " "
    << parameter.GetInitialSulfideConcentration() << " "
    << *parameter.GetSulfideConsumptionFunction() << " "
    << parameter.organic_matter_addition << " "
    << parameter.organic_matter_breakdown << " "
    << parameter.organic_matter_capture << " "
    << parameter.organic_matter_to_sulfide_factor << " "
    << parameter.organic_matter_to_sulfide_rate << " "
    << *parameter.GetPoisoningFunction() << " "
    << parameter.seagrass_carrying_capacity << " "
    << parameter.seagrass_growth_rate << " "
    << parameter.seagrass_to_organic_matter_factor << " "
    << parameter.sulfide_diffusion_rate << " "
    << parameter.n_timesteps
  ;
  return os;
}

std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept
{
  is
    >> parameter.delta_t
    >> parameter.initial_loripes_density
    >> parameter.initial_organic_matter_density
    >> parameter.initial_seagrass_density
    >> parameter.initial_sulfide_concentration
    >> parameter.m_loripes_consumption_function
    >> parameter.organic_matter_addition
    >> parameter.organic_matter_breakdown
    >> parameter.organic_matter_capture
    >> parameter.organic_matter_to_sulfide_factor
    >> parameter.organic_matter_to_sulfide_rate
    >> parameter.m_poisoning_function
    >> parameter.seagrass_carrying_capacity
    >> parameter.seagrass_growth_rate
    >> parameter.seagrass_to_organic_matter_factor
    >> parameter.sulfide_diffusion_rate
    >> parameter.n_timesteps
  ;
  return is;
}

bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return
       lhs.GetDeltaT() == rhs.GetDeltaT()
    && lhs.initial_loripes_density == rhs.initial_loripes_density
    && lhs.initial_organic_matter_density == rhs.initial_organic_matter_density
    && lhs.initial_seagrass_density == rhs.initial_seagrass_density
    && lhs.initial_sulfide_concentration == rhs.initial_sulfide_concentration
    && lhs.m_loripes_consumption_function->ToStr() == rhs.m_loripes_consumption_function->ToStr()
    && lhs.organic_matter_addition == rhs.organic_matter_addition
    && lhs.organic_matter_breakdown == rhs.organic_matter_breakdown
    && lhs.organic_matter_capture == rhs.organic_matter_capture
    && lhs.organic_matter_to_sulfide_factor == rhs.organic_matter_to_sulfide_factor
    && lhs.organic_matter_to_sulfide_rate == rhs.organic_matter_to_sulfide_rate
    && lhs.GetPoisoningFunction()->ToStr() == rhs.GetPoisoningFunction()->ToStr()
    && lhs.seagrass_carrying_capacity == rhs.seagrass_carrying_capacity
    && lhs.seagrass_growth_rate == rhs.seagrass_growth_rate
    && lhs.seagrass_to_organic_matter_factor == rhs.seagrass_to_organic_matter_factor
    && lhs.sulfide_diffusion_rate == rhs.sulfide_diffusion_rate
    && lhs.n_timesteps == rhs.n_timesteps
  ;

}

bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
