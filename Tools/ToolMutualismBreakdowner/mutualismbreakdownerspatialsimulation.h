#ifndef SPATIALSIMULATION_H
#define SPATIALSIMULATION_H

#include <vector>

#include "mutualismbreakdownerparameters.h"
#include "ribi_time.h"
#include "mutualismbreakdownerseagrasssystem.h"

namespace ribi {
namespace mb {

struct SpatialSimulation
{
  using Time = ribi::units::Time;
  using System = SeagrassSystem;
  using Grid = std::vector<std::vector<System>>;

  SpatialSimulation(const Parameters& parameters);

  void Change(const Time delta_t);

  const auto& GetGrid() const noexcept { return m_grid; }

  void KillSeagrass(const int x, const int y);

  private:

  Grid m_grid;
  const Parameters m_parameters;
};

} //~namespace mb
} //~namespace ribi

#endif // SPATIALSIMULATION_H
