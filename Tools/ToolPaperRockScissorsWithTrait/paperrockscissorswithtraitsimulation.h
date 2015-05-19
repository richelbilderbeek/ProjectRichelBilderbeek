#ifndef PAPERROCKSCISSORSWITHTRAITSIMULATION_H
#define PAPERROCKSCISSORSWITHTRAITSIMULATION_H

#include <vector>
#include "individual.h"

struct PaperRockScissorsSimulation
{
  using CellType = Individual;
  PaperRockScissorsSimulation(const int width, const int height);

  ///Y-X ordered grid
  const std::vector<std::vector<CellType>>& GetGrid() const noexcept { return m_grid; }
  void Next();

  private:

  std::vector<std::vector<CellType>> m_grid;
};

#endif // PAPERROCKSCISSORSWITHTRAITSIMULATION_H
