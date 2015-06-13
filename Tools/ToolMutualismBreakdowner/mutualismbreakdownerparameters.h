#ifndef MUTUALISMBREAKDOWNER_PARAMETERS_H
#define MUTUALISMBREAKDOWNER_PARAMETERS_H

#include <iosfwd>
#include <memory>
#include "speciesdensity.h"
#include "concentration.h"
#include "ribi_time.h"

namespace ribi {
namespace mb {

struct PoisoningFunction;
struct SeagrassColonisationFunction;
struct SeagrassGrowthFunction;
struct SulfideConsumptionFunction;
struct SulfideDetoxificationFunction;
struct SulfideDiffusionFunction;
struct SulfideProductionFunction;


struct Parameters
{
  using SpeciesDensity = ribi::units::SpeciesDensity;
  using Concentration = ribi::units::Concentration;
  using Time = ribi::units::Time;

  Parameters();
  Parameters(
    const Time spatial_delta_t,
    const int spatial_height,
    const int spatial_width,
    const Time timeplot_delta_t,
    const SpeciesDensity m_initial_loripes_density,
    const SpeciesDensity m_initial_seagrass_density,
    const Concentration any_initial_loripes_density,
    std::shared_ptr<PoisoningFunction> any_poisoning_function,
    std::shared_ptr<SeagrassColonisationFunction> seagrass_colonisation_function,
    std::shared_ptr<SeagrassGrowthFunction> seagrass_growth_function,
    std::shared_ptr<SulfideConsumptionFunction> sulfide_consumption_function,
    std::shared_ptr<SulfideDetoxificationFunction> sulfide_detoxification_function,
    std::shared_ptr<SulfideDiffusionFunction> sulfide_diffusion_function,
    std::shared_ptr<SulfideProductionFunction> sulfide_production_function,
    const int any_n_timesteps
  );

  auto GetSpatialDeltaT() const noexcept { return m_spatial_delta_t; }
  auto GetSpatialHeight() const noexcept { return m_spatial_height; }
  auto GetSpatialWidth() const noexcept { return m_spatial_width; }
  auto GetTimeplotDeltaT() const noexcept { return m_timeplot_delta_t; }

  auto GetInitialLoripesDensity() const noexcept { return m_initial_loripes_density; }
  auto GetInitialSeagrassDensity() const noexcept { return m_initial_seagrass_density; }
  auto GetInitialSulfideConcentration() const noexcept { return m_initial_sulfide_concentration; }

  auto GetNumberOfTimesteps() const noexcept { return n_timesteps; }

  const auto& GetPoisoningFunction() const noexcept { return m_poisoning_function; }
  const auto& GetSeagrassColonisationFunction() const noexcept { return m_seagrass_colonisation_function; }
  const auto& GetSeagrassGrowthFunction() const noexcept { return m_seagrass_growth_function; }
  const auto& GetSulfideConsumptionFunction() const noexcept { return m_sulfide_consumption_function; }
  const auto& GetSulfideDetoxificationFunction() const noexcept { return m_sulfide_detoxification_function; }
  const auto& GetSulfideDiffusionFunction() const noexcept { return m_sulfide_diffusion_function; }
  const auto& GetSulfideProductionFunction() const noexcept { return m_sulfide_production_function; }

  ///Create a testing parameter set
  static Parameters GetTest(const int i);

  void SetTimeplotDeltaT(const Time any_delta_t);
  void SetInitialSeagrassDensity(const ribi::units::SpeciesDensity any_initial_seagrass_density) noexcept;
  void SetPoisoningFunction(const std::shared_ptr<PoisoningFunction> any_poisoning_function);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif


  private:
  Time m_spatial_delta_t;
  int m_spatial_height;
  int m_spatial_width;
  Time m_timeplot_delta_t;

  ribi::units::SpeciesDensity m_initial_loripes_density;
  ribi::units::SpeciesDensity m_initial_seagrass_density;
  ribi::units::Concentration m_initial_sulfide_concentration;

  std::shared_ptr<PoisoningFunction> m_poisoning_function;
  std::shared_ptr<SeagrassColonisationFunction> m_seagrass_colonisation_function;
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

} //~namespace mb
} //~namespace ribi

#endif // MUTUALISMBREAKDOWNER_PARAMETERS_H
