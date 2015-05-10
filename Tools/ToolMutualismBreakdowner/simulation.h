#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "parameters.h"

struct Simulation
{
  Simulation(const Parameters& parameters);

  const Parameters& GetParameters() const noexcept { return m_parameters; }
  const auto& GetLoripesDensities() const noexcept { return m_loripes_densities; }
  const auto& GetSeagrassDensities() const noexcept { return m_seagrass_densities; }
  const auto& GetSulfideConcentrations() const noexcept { return m_sulfide_concentrations; }
  const std::vector<double>& GetOrganicMatterDensities() const noexcept { return m_organic_matter_densities; }
  const std::vector<double>& GetTimeSeries() const noexcept { return m_timeseries; }

  void Run();

  private:
  const Parameters m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  std::vector<ribi::units::SpeciesDensity> m_loripes_densities;
  std::vector<ribi::units::SpeciesDensity> m_seagrass_densities;
  std::vector<ribi::units::Concentration> m_sulfide_concentrations;
  std::vector<double> m_organic_matter_densities;
  std::vector<double> m_timeseries;
};

std::ostream& operator<<(std::ostream& os, const Simulation& simulation) noexcept;

#endif // SIMULATION_H
