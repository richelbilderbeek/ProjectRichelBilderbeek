#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iosfwd>
#include <memory>
#include "speciesdensity.h"
#include "concentration.h"

struct SulfideConsumptionFunction;
struct PoisoningFunction;
struct SeagrassGrowthFunction;
struct SulfideProductionFunction;

struct Parameters
{
  Parameters();
  Parameters(
    const double any_delta_t,
    const double any_detoxification_max_rate,
    const double any_detoxification_minimum,
    const double any_detoxification_rate,
    const ribi::units::SpeciesDensity initial_loripes_density,
    const double any_initial_organic_matter_density,
    const ribi::units::SpeciesDensity initial_seagrass_density,
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
  );

  double GetDeltaT() const noexcept { return delta_t; }

  auto GetInitialLoripesDensity() const noexcept { return initial_loripes_density; }
  auto GetInitialOrganicMatterDensity() const noexcept { return initial_organic_matter_density; }
  auto GetInitialSeagrassDensity() const noexcept { return initial_seagrass_density; }
  auto GetInitialSulfideConcentration() const noexcept { return initial_sulfide_concentration; }

  auto GetNumberOfTimesteps() const noexcept { return n_timesteps; }

  const auto& GetSulfideConsumptionFunction() const noexcept { return m_loripes_consumption_function; }
  const auto& GetPoisoningFunction() const noexcept { return m_poisoning_function; }
  const auto& GetSeagrassGrowthFunction() const noexcept { return m_seagrass_growth_function; }
  const auto& GetSulfideProductionFunction() const noexcept { return m_sulfide_production_function; }

  void SetDeltaT(const double any_delta_t);
  void SetInitialSeagrassDensity(const ribi::units::SpeciesDensity any_initial_seagrass_density) noexcept;

  void SetPoisoningFunction(const std::shared_ptr<PoisoningFunction> any_poisoning_function);

  #ifndef NDEBUG

  static void Test() noexcept;
  ///Create a testing parameter set
  static Parameters GetTest(const int i);
  #endif

  private:
  double delta_t;
  double detoxification_max_rate;
  double detoxification_minimum;
  double detoxification_rate;
  ribi::units::SpeciesDensity initial_loripes_density;
  double initial_organic_matter_density;
  ribi::units::SpeciesDensity initial_seagrass_density;
  ribi::units::Concentration initial_sulfide_concentration;
  std::shared_ptr<SulfideConsumptionFunction> m_loripes_consumption_function;
  double mutualism_breakdown_max;
  double mutualism_breakdown_r0;
  double mutualism_breakdown_rate;
  double organic_matter_addition;
  double organic_matter_breakdown;
  double organic_matter_capture;
  double organic_matter_to_sulfide_factor;
  double organic_matter_to_sulfide_rate;
  std::shared_ptr<PoisoningFunction> m_poisoning_function;

  private:

  double recruitment_max;
  double recruitment_rate;

  std::shared_ptr<SeagrassGrowthFunction> m_seagrass_growth_function;

  ribi::units::SpeciesDensity seagrass_carrying_capacity;
  double seagrass_growth_rate;
  double seagrass_to_organic_matter_factor;
  double sulfide_diffusion_rate;

  std::shared_ptr<SulfideProductionFunction> m_sulfide_production_function;

  int n_timesteps;

  friend std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept;
  friend std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept;
  friend bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept;
};

bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept;
bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept;
std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept;

#endif // PARAMETERS_H
