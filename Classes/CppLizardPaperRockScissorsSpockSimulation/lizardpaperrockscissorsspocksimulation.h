#ifndef LIZARDPAPERROCKSCISSORSSPOCKSIMULATION_H
#define LIZARDPAPERROCKSCISSORSSPOCKSIMULATION_H

#include <vector>
#include "lizardpaperrockscissorsspock.h"

namespace ribi {
namespace lprss { //Lizard-Paper-Rock-Scissors-Spock

struct Simulation
{
  enum class Initialization
  {
    random,
    vertical_bands
  };

  using CellType = LizardPaperRockScissorsSpock;
  using Init = Initialization;

  Simulation(
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

} //~namespace lprss { //Lizard-Paper-Rock-Scissors-Spock
} //~namespace ribi {

#endif // LIZARDPAPERROCKSCISSORSSPOCKSIMULATION_H
