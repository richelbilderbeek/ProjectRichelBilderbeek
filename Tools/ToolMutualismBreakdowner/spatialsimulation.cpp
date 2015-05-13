#include "spatialsimulation.h"

SpatialSimulation::SpatialSimulation(const Parameters& parameters)
  : m_grid{Grid(parameters.GetSpatialHeight(),std::vector<System>(parameters.GetSpatialWidth(),System(parameters)))},
    m_parameters{parameters}
{

}

void SpatialSimulation::Change(const Time delta_t)
{
  for (auto& line: m_grid)
  {
    for (auto& system: line)
    {
      system.Change(delta_t);
    }
  }

}

void SpatialSimulation::KillSeagrass(const int x, const int y)
{
  m_grid[y][x].SetSeagrassDensity(0.0 * boost::units::si::species_per_square_meter);
}
