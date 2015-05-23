#ifndef PAPERROCKSCISSORSWITHTRAITSIMULATION_H
#define PAPERROCKSCISSORSWITHTRAITSIMULATION_H

#include <random>
#include <vector>
#include "paperrockscissorswithtraitindividual.h"

struct PaperRockScissorsSimulation
{
  using Individual = PaperRockScissorsWithTraitIndividual;
  using Prs = PaperRockScissors;

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
  const auto& GetGrid() const noexcept { return m_grid; }
  Initialization GetInitialization() const noexcept { return m_initialization; }
  std::tuple<int,int,int> GetLastPopSizes() const;
  std::tuple<double,double,double> GetLastMeanTraits() const;

  void Next();
  void SetInitialization(const Initialization initialization) noexcept;

  private:

  std::vector<std::vector<Individual>> m_grid;
  int m_width;
  int m_height;
  Initialization m_initialization;
  int m_rng_seed;
  std::mt19937 m_rng;

  std::uniform_int_distribution<int> m_uniform_distribution;
  std::normal_distribution<double> m_normal_distribution;

  std::vector<std::tuple<int,int,int>> m_popsizes;
  std::vector<std::tuple<double,double,double>> m_mean_traits;

};

#endif // PAPERROCKSCISSORSWITHTRAITSIMULATION_H
