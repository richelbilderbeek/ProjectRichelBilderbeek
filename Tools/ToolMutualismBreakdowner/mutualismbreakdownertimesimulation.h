#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "mutualismbreakdownerparameters.h"

namespace ribi {
namespace mb {

struct TimeSimulation
{
  TimeSimulation(const Parameters& parameters);

  const Parameters& GetParameters() const noexcept { return m_parameters; }
  const auto& GetSeagrassDensities() const noexcept { return m_seagrass_densities; }
  const auto& GetSulfideConcentrations() const noexcept { return m_sulfide_concentrations; }
  const std::vector<double>& GetTimeSeries() const noexcept { return m_timeseries; }

  void Run();

  private:
  const Parameters m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  std::vector<ribi::units::SpeciesDensity> m_seagrass_densities;
  std::vector<ribi::units::Concentration> m_sulfide_concentrations;
  std::vector<double> m_timeseries;
};

std::ostream& operator<<(std::ostream& os, const TimeSimulation& simulation) noexcept;

} //~namespace mb
} //~namespace ribi

#endif // SIMULATION_H
