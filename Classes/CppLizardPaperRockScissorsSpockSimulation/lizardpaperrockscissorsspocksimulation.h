#ifndef LIZARDPAPERROCKSCISSORSSPOCKSIMULATION_H
#define LIZARDPAPERROCKSCISSORSSPOCKSIMULATION_H

#include <vector>
#include "lizard_paper_rock_scissors_spock.h"

struct LizardPaperRockScissorsSpockSimulation
{
  enum class Initialization
  {
    random,
    vertical_bands
  };

  using CellType = LizardPaperRockScissorsSpock;
  using Init = Initialization;

  LizardPaperRockScissorsSpockSimulation(
    const int width,
    const int height,
    const Initialization initialization
  );

  ///Y-X ordered grid
  const std::vector<std::vector<CellType>>& GetGrid() const noexcept { return m_grid; }

  Initialization GetInitialization() const noexcept { return m_initialization; }

  void Next();

  private:

  std::vector<std::vector<CellType>> m_grid;
  Initialization m_initialization;
};

#endif // LIZARDPAPERROCKSCISSORSSPOCKSIMULATION_H
