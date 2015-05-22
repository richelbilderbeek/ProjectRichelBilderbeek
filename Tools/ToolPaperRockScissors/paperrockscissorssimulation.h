#ifndef PAPERROCKSCISSORSSIMULATION_H
#define PAPERROCKSCISSORSSIMULATION_H

#include <vector>
#include "paper_rock_scissors.h"

struct PaperRockScissorsSimulation
{
  using CellType = PaperRockScissors;

  enum class Initialization
  {
    random,
    vertical_bands
  };

  PaperRockScissorsSimulation(
    const int width,
    const int height,
    const Initialization initialization
  );

  ///Y-X ordered grid
  const std::vector<std::vector<CellType>>& GetGrid() const noexcept { return m_grid; }
  Initialization GetInitialization() const noexcept { return m_initialization; }
  void Next();
  void SetInitialization(const Initialization initialization) noexcept;

  private:

  std::vector<std::vector<CellType>> m_grid;
  Initialization m_initialization;
};

#endif // PAPERROCKSCISSORSSIMULATION_H
