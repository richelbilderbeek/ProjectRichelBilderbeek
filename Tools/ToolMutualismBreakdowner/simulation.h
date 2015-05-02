#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "parameters.h"

struct Simulation
{
  Simulation(const Parameters& parameters);

  const std::vector<double>& GetSeagrassDensities() const noexcept { return m_seagrass_densities; }
  const std::vector<double>& GetSulfideConcentrations() const noexcept { return m_sulfide_concentrations; }
  const std::vector<double>& GetOrganicMatterDensities() const noexcept { return m_organic_matter_densities; }
  const std::vector<double>& GetTimeSeries() const noexcept { return m_timeseries; }

  void Run() noexcept;

  private:
  const Parameters m_parameters;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  std::vector<double> m_seagrass_densities;
  std::vector<double> m_sulfide_concentrations;
  std::vector<double> m_organic_matter_densities;
  std::vector<double> m_timeseries;
};

#endif // SIMULATION_H
