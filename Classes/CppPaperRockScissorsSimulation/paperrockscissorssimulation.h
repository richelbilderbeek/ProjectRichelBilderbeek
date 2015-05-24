#ifndef PAPERROCKSCISSORSSIMULATION_H
#define PAPERROCKSCISSORSSIMULATION_H

#include <random>
#include <vector>
#include "paperrockscissors.h"

namespace ribi {
namespace prs {

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
    const Initialization initialization,
    const int rng_seed
  );

  ///Y-X ordered grid
  const std::vector<std::vector<CellType>>& GetGrid() const noexcept { return m_grid; }
  Initialization GetInitialization() const noexcept { return m_initialization; }
  void Next();
  void SetInitialization(const Initialization initialization) noexcept;

  private:

  std::vector<std::vector<CellType>> m_grid;
  Initialization m_initialization;
  int m_rng_seed;
  std::mt19937 m_rng;
};

} //~namespace prs {
} //~namespace ribi {

#endif // PAPERROCKSCISSORSSIMULATION_H
