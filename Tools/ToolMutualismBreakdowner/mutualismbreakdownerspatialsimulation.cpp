#include "mutualismbreakdownerspatialsimulation.h"

#include "mutualismbreakdownerseagrasscolonisationfunction.h"

ribi::mb::SpatialSimulation::SpatialSimulation(const Parameters& parameters)
  : m_grid{Grid(parameters.GetSpatialHeight(),std::vector<System>(parameters.GetSpatialWidth(),System(parameters)))},
    m_parameters{parameters}
{

}

void ribi::mb::SpatialSimulation::Change(const Time delta_t)
{
  using ribi::units::Rate;
  using Growth = ribi::units::SpeciesGrowth;

  for (auto& line: m_grid)
  {
    for (auto& system: line)
    {
      system.Change(delta_t);
    }
  }

  const auto seagrass_colonisation_function
    = m_parameters.GetSeagrassColonisationFunction();

  using Density = ribi::units::SpeciesDensity;
  const int height{static_cast<int>(m_grid.size())};
  const int width{static_cast<int>(m_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const std::vector<Density> neigbour_seagrass_densities
        =
        {
          m_grid[y][(x-1+width)%width].GetSeagrassDensity(),
          m_grid[y][(x+1+width)%width].GetSeagrassDensity(),
          m_grid[(y-1+height)%height][x].GetSeagrassDensity(),
          m_grid[(y+1+height)%height][x].GetSeagrassDensity()
        }
      ;
      const Growth colonization
        = seagrass_colonisation_function->CalculateColonisation(
          neigbour_seagrass_densities
        )
      ;
      m_grid[y][x].AddSeagrassDensity(colonization * delta_t);
    }
  }
}

void ribi::mb::SpatialSimulation::KillSeagrass(const int x, const int y)
{
  m_grid[y][x].SetSeagrassDensity(0.0 * boost::units::si::species_per_square_meter);
}
