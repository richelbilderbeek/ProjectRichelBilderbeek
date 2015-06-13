#include "mutualismbreakdownerparameters.h"

#include <cassert>
#include <iostream>
#include <boost/units/io.hpp>

#include "mutualismbreakdownerpoisoningfunction.h"
#include "mutualismbreakdownerseagrassgrowthfunction.h"
#include "mutualismbreakdownerseagrasscolonisationfunction.h"
#include "mutualismbreakdownersulfideconsumptionfunction.h"
#include "mutualismbreakdownersulfidedetoxificationfunction.h"
#include "mutualismbreakdownersulfidediffusionfunction.h"
#include "mutualismbreakdownersulfideproductionfunction.h"

ribi::mb::Parameters::Parameters()
  :
    m_spatial_delta_t{0.1 * boost::units::si::seconds},
    m_spatial_height{10},
    m_spatial_width{10},
    m_timeplot_delta_t{0.1 * boost::units::si::seconds},
    m_initial_loripes_density{0.0 * boost::units::si::species_per_square_meters},
    m_initial_seagrass_density{0.0 * boost::units::si::species_per_square_meters},
    m_initial_sulfide_concentration{0.0 * boost::units::si::mole / boost::units::si::cubic_meter},
    m_poisoning_function{std::make_shared<InvertedExponentialPoisoning>()},
    m_seagrass_colonisation_function{std::make_shared<SeagrassInvertedExponential>()},
    m_seagrass_growth_function{std::make_shared<SeagrassStressedLogisticGrowth>()},
    m_sulfide_consumption_function{new LinearConsumption},
    m_sulfide_detoxification_function{new LinearSulfideDetoxification},
    m_sulfide_diffusion_function{new LinearSulfideDiffusion},
    m_sulfide_production_function{std::make_shared<LinearSulfideProduction>()},
    n_timesteps{1}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_poisoning_function);
  assert(m_seagrass_growth_function);
}

ribi::mb::Parameters::Parameters(
  const Time spatial_delta_t,
  const int spatial_height,
  const int spatial_width,
  const Time timeplot_delta_t,
  const ribi::units::SpeciesDensity initial_loripes_density,
  const ribi::units::SpeciesDensity initial_seagrass_density,
  const ribi::units::Concentration initial_sulfide_concentration,
  std::shared_ptr<PoisoningFunction> poisoning_function,
  std::shared_ptr<SeagrassColonisationFunction> seagrass_colonisation_function,
  std::shared_ptr<SeagrassGrowthFunction> seagrass_growth_function,
  std::shared_ptr<SulfideConsumptionFunction> sulfide_consumption_function,
  std::shared_ptr<SulfideDetoxificationFunction> sulfide_detoxification_function,
  std::shared_ptr<SulfideDiffusionFunction> sulfide_diffusion_function,
  std::shared_ptr<SulfideProductionFunction> sulfide_production_function,
  const int any_n_timesteps
) :
    m_spatial_delta_t{spatial_delta_t},
    m_spatial_height{spatial_height},
    m_spatial_width{spatial_width},
    m_timeplot_delta_t{timeplot_delta_t},
    m_initial_loripes_density{initial_loripes_density},
    m_initial_seagrass_density{initial_seagrass_density},
    m_initial_sulfide_concentration{initial_sulfide_concentration},
    m_poisoning_function{poisoning_function},
    m_seagrass_colonisation_function{seagrass_colonisation_function},
    m_seagrass_growth_function{seagrass_growth_function},
    m_sulfide_consumption_function{sulfide_consumption_function},
    m_sulfide_detoxification_function{sulfide_detoxification_function},
    m_sulfide_diffusion_function{sulfide_diffusion_function},
    m_sulfide_production_function{sulfide_production_function},
    n_timesteps{any_n_timesteps}
{
  #ifndef NDEBUG
  Test();
  #endif
  using boost::units::si::species_per_square_meter;
  using boost::units::si::mole;
  using boost::units::si::cubic_meter;
  using boost::units::si::seconds;
  if (m_spatial_delta_t <= 0.0 * seconds)
  {
    throw std::logic_error("Parameters::Parameters: spatial_delta_t must be above zero");
  }
  if (m_timeplot_delta_t <= 0.0 * seconds)
  {
    throw std::logic_error("Parameters::Parameters: timeplot_delta_t must be above zero");
  }
  assert(m_initial_loripes_density >= 0.0 * species_per_square_meter);
  assert(m_initial_seagrass_density >= 0.0 * species_per_square_meter);
  assert(m_initial_sulfide_concentration >= 0.0 * mole / cubic_meter);
  assert(m_sulfide_consumption_function);
  assert(m_seagrass_colonisation_function);
  assert(m_seagrass_growth_function);
  assert(m_poisoning_function);
  assert(m_sulfide_production_function);
}

ribi::mb::Parameters ribi::mb::Parameters::GetTest(const int /* i */)
{
  const auto poisoning_function
    = std::make_shared<InvertedExponentialPoisoning>(0.01,0.05,1.0);
  const auto seagrass_colonisation_function
    = std::make_shared<SeagrassInvertedExponential>(
      0.1, //alpha
      0.1 * boost::units::si::per_second //growth_rate
    );
  const auto seagrass_growth_function
    = std::make_shared<SeagrassStressedLogisticGrowth>(
      0.5 * boost::units::si::species_per_square_meter, //carrying_capacity
      1.1 * boost::units::si::per_second, //growth_rate
      0.1 * boost::units::si::per_second //stress_rate
    );
  const auto sulfide_consumption_function
    = std::make_shared<LinearConsumption>(0.05);
  const auto sulfide_detoxification_function
    = std::make_shared<LinearSulfideDetoxification>(0.05);
  const auto sulfide_diffusion_function
    = std::make_shared<LinearSulfideDiffusion>(0.05);
  const auto sulfide_production_function
    = std::make_shared<LinearSulfideProduction>(
      0.5
    );


  using boost::units::si::species_per_square_meters;
  using boost::units::si::mole;
  using boost::units::si::cubic_meter;
  using boost::units::si::seconds;
  const Parameters p(
    0.1 * seconds, //spatial_delta_t,
    10, //spatial_height
    10, //spatial_width
    0.1 * seconds, //timeplot_delta_t,
    0.1 * species_per_square_meters, //initial_loripes_density,
    0.1 * species_per_square_meters, //initial_seagrass_density,
    0.0 * mole / cubic_meter, //any_initial_loripes_density,
    poisoning_function,
    seagrass_colonisation_function,
    seagrass_growth_function,
    sulfide_consumption_function,
    sulfide_detoxification_function,
    sulfide_diffusion_function,
    sulfide_production_function,
    100 //any_n_timesteps
  );
  return p;
}

void ribi::mb::Parameters::SetTimeplotDeltaT(const Time any_delta_t)
{
  if (any_delta_t <= 0.0 * boost::units::si::seconds)
  {
    std::stringstream s;
    s << "Parameters::SetDeltaT: "
      << "any_delta_t cannot be less or equal to zero, "
      << "obtained value " << any_delta_t;
    throw std::logic_error(s.str());
  }
  m_timeplot_delta_t = any_delta_t;
}

void ribi::mb::Parameters::SetInitialSeagrassDensity(const ribi::units::SpeciesDensity any_initial_seagrass_density) noexcept
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
  m_initial_seagrass_density = any_initial_seagrass_density;
}

void ribi::mb::Parameters::SetPoisoningFunction(const std::shared_ptr<PoisoningFunction> any_poisoning_function)
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

std::ostream& ribi::mb::operator<<(std::ostream& os, const Parameters& parameter) noexcept
{
  os
    << parameter.GetSpatialDeltaT() << " "
    << parameter.GetSpatialHeight() << " "
    << parameter.GetSpatialWidth() << " "
    << parameter.GetTimeplotDeltaT() << " "
    << parameter.GetInitialLoripesDensity() << " "
    << parameter.GetInitialSeagrassDensity() << " "
    << parameter.GetInitialSulfideConcentration() << " "
    << *parameter.GetPoisoningFunction() << " "
    << *parameter.GetSulfideConsumptionFunction() << " "
    << *parameter.GetSulfideDetoxificationFunction() << " "
    << *parameter.GetSulfideDiffusionFunction() << " "
    << *parameter.GetSulfideProductionFunction() << " "
    << parameter.n_timesteps
  ;
  return os;
}

std::istream& ribi::mb::operator>>(std::istream& is, Parameters& parameter) noexcept
{
  is
    >> parameter.m_spatial_delta_t
    >> parameter.m_spatial_height
    >> parameter.m_spatial_width
    >> parameter.m_timeplot_delta_t
    >> parameter.m_initial_loripes_density
    >> parameter.m_initial_seagrass_density
    >> parameter.m_initial_sulfide_concentration
    >> parameter.m_poisoning_function
    >> parameter.m_sulfide_consumption_function
    >> parameter.m_sulfide_detoxification_function
    >> parameter.m_sulfide_diffusion_function
    >> parameter.m_sulfide_production_function
    >> parameter.n_timesteps
  ;
  return is;
}

bool ribi::mb::operator==(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return
       lhs.GetSpatialDeltaT() == rhs.GetSpatialDeltaT()
    && lhs.GetSpatialHeight() == rhs.GetSpatialHeight()
    && lhs.GetSpatialWidth() == rhs.GetSpatialWidth()
    && lhs.GetTimeplotDeltaT() == rhs.GetTimeplotDeltaT()
    && lhs.m_initial_loripes_density == rhs.m_initial_loripes_density
    && lhs.m_initial_seagrass_density == rhs.m_initial_seagrass_density
    && lhs.m_initial_sulfide_concentration == rhs.m_initial_sulfide_concentration
    && lhs.GetPoisoningFunction()->ToStr() == rhs.GetPoisoningFunction()->ToStr()
    && lhs.m_sulfide_consumption_function->ToStr() == rhs.m_sulfide_consumption_function->ToStr()
    && lhs.m_sulfide_detoxification_function->ToStr() == rhs.m_sulfide_detoxification_function->ToStr()
    && lhs.m_sulfide_diffusion_function->ToStr() == rhs.m_sulfide_diffusion_function->ToStr()
    && lhs.m_sulfide_production_function->ToStr() == rhs.m_sulfide_production_function->ToStr()
    && lhs.n_timesteps == rhs.n_timesteps
  ;

}

bool ribi::mb::operator!=(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
