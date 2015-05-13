#ifndef SPATIALSIMULATION_H
#define SPATIALSIMULATION_H

#include <vector>

#include "parameters.h"
#include "ribi_time.h"
#include "seagrasssystem.h"

struct SpatialSimulation
{
  using Time = ribi::units::Time;
  using System = SeagrassSystem;
  using Grid = std::vector<std::vector<System>>;

  SpatialSimulation(const Parameters& parameters);

  void Change(const Time delta_t);

  const auto& GetGrid() const noexcept { return m_grid; }

  private:

  Grid m_grid;
  const Parameters m_parameters;
};

#endif // SPATIALSIMULATION_H
