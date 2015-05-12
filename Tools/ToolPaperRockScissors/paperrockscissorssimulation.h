#ifndef PAPERROCKSCISSORSSIMULATION_H
#define PAPERROCKSCISSORSSIMULATION_H

#include <vector>
#include "paper_rock_scissors.h"

struct PaperRockScissorsSimulation
{
  using CellType = PaperRockScissors;
  PaperRockScissorsSimulation(const int width, const int height);

  ///Y-X ordered grid
  const std::vector<std::vector<CellType>>& GetGrid() const noexcept { return m_grid; }
  void Next();

  private:

  std::vector<std::vector<CellType>> m_grid;
};

#endif // PAPERROCKSCISSORSSIMULATION_H
