#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "lizard_paper_rock_scissors_spock.h"

struct Simulation
{
  using CellType = LizardPaperRockScissorsSpock;
  Simulation(const int width, const int height);

  ///Y-X ordered grid
  const std::vector<std::vector<CellType>>& GetGrid() const noexcept { return m_grid; }
  void Next();

  private:

  std::vector<std::vector<CellType>> m_grid;
};

#endif // SIMULATION_H
