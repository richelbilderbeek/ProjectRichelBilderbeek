#ifndef PAPERROCKSCISSORSWITHTRAITSIMULATION_H
#define PAPERROCKSCISSORSWITHTRAITSIMULATION_H

#include <random>
#include <vector>
#include "paperrockscissors.h"
#include "paperrockscissorswithtraitindividual.h"
#include "paperrockscissorswithtraitinitialization.h"
#include "paperrockscissorswithtraitparameters.h"

namespace ribi {
namespace prswt { //Paper-Rock-Scissors-With-Trait

struct Simulation
{
  Simulation(
    const Parameters& parameters
  );

  ///Y-X ordered grid
  const auto& GetGrid() const noexcept { return m_grid; }

  const auto& GetParameters() const noexcept { return m_parameters; }

  //Initialization GetInitialization() const noexcept { return m_initialization; }
  std::tuple<int,int,int> GetLastPopSizes() const;
  std::tuple<double,double,double> GetLastMeanTraits() const;

  void Next();
  void SetInitialization(const Initialization initialization) noexcept;

  private:

  std::vector<std::vector<Individual>> m_grid;
  std::mt19937 m_rng;

  std::uniform_int_distribution<int> m_uniform_distribution;
  std::normal_distribution<double> m_normal_distribution;

  std::vector<std::tuple<int,int,int>> m_popsizes;
  std::vector<std::tuple<double,double,double>> m_mean_traits;

  Parameters m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //namespace prswt { //Paper-Rock-Scissors-With-Trait
} //~namespace ribi

#endif // PAPERROCKSCISSORSWITHTRAITSIMULATION_H
