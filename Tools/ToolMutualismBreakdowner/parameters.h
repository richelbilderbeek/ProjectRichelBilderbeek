#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iosfwd>
#include <memory>
#include "speciesdensity.h"
#include "concentration.h"

struct PoisoningFunction;
struct SeagrassGrowthFunction;
struct SulfideConsumptionFunction;
struct SulfideDetoxificationFunction;
struct SulfideDiffusionFunction;
struct SulfideProductionFunction;

struct Parameters
{
  Parameters();
  Parameters(
    const double any_delta_t,
    const ribi::units::SpeciesDensity m_initial_loripes_density,
    const ribi::units::SpeciesDensity m_initial_seagrass_density,
    const ribi::units::Concentration any_initial_loripes_density,
    std::shared_ptr<PoisoningFunction> any_poisoning_function,
    std::shared_ptr<SeagrassGrowthFunction> seagrass_growth_function,
    std::shared_ptr<SulfideConsumptionFunction> sulfide_consumption_function,
    std::shared_ptr<SulfideDetoxificationFunction> sulfide_detoxification_function,
    std::shared_ptr<SulfideDiffusionFunction> sulfide_diffusion_function,
    std::shared_ptr<SulfideProductionFunction> sulfide_production_function,
    const int any_n_timesteps
  );

  double GetDeltaT() const noexcept { return m_delta_t; }

  auto GetInitialLoripesDensity() const noexcept { return m_initial_loripes_density; }
  auto GetInitialSeagrassDensity() const noexcept { return m_initial_seagrass_density; }
  auto GetInitialSulfideConcentration() const noexcept { return m_initial_sulfide_concentration; }

  auto GetNumberOfTimesteps() const noexcept { return n_timesteps; }

  const auto& GetPoisoningFunction() const noexcept { return m_poisoning_function; }
  const auto& GetSeagrassGrowthFunction() const noexcept { return m_seagrass_growth_function; }
  const auto& GetSulfideConsumptionFunction() const noexcept { return m_sulfide_consumption_function; }
  const auto& GetSulfideDetoxificationFunction() const noexcept { return m_sulfide_detoxification_function; }
  const auto& GetSulfideDiffusionFunction() const noexcept { return m_sulfide_diffusion_function; }
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
  double m_delta_t;

  ribi::units::SpeciesDensity m_initial_loripes_density;
  ribi::units::SpeciesDensity m_initial_seagrass_density;
  ribi::units::Concentration m_initial_sulfide_concentration;

  std::shared_ptr<PoisoningFunction> m_poisoning_function;
  std::shared_ptr<SeagrassGrowthFunction> m_seagrass_growth_function;
  std::shared_ptr<SulfideConsumptionFunction> m_sulfide_consumption_function;
  std::shared_ptr<SulfideDetoxificationFunction> m_sulfide_detoxification_function;
  std::shared_ptr<SulfideDiffusionFunction> m_sulfide_diffusion_function;
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
