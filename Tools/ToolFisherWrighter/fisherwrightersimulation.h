#ifndef SIMULATION_H
#define SIMULATION_H

#include <random>
#include <vector>

#include "counter.h"
#include "fisherwrightergeneration.h"
#include "fisherwrighterindividual.h"
#include "fisherwrighterparameters.h"
#include "dnasequence.h"

namespace ribi {
namespace fw {

///Fisher-Wright simulation
///with individuals that only have DNA
struct Simulation
{
  ///Use randomly created individuals
  Simulation(const Parameters& parameters);

  std::string GetPedigree() noexcept;


  ///Obtain the sequences of the current (most recent) simulation
  ///Equivalent to simulation.GetGenerations().back().GetSequences()
  std::vector<ribi::DnaSequence> GetCurrentSequences() const noexcept;

  const std::vector<Generation>& GetGenerations() const noexcept { return m_generations; }

  const Parameters& GetParameters() const noexcept { return m_parameters; }

  //Go to the next generation
  void NextGeneration() noexcept;

  private:
  ribi::Counter m_counter;

  std::vector<Generation> m_generations;

  const Parameters m_parameters;

  ///Random number generator engine
  std::mt19937 m_rnd_engine;

  ///Put in your own individuals
  Simulation(
    const Parameters& parameters,
    const Generation& generation
  );

  ///Create initial population of individuals with random DNA sequences
  ///Non-const, because random numbers are used
  Generation CreateNextGeneration(
    Generation& current_generation
  ) noexcept;

  static std::vector<Parameters> CreateTestParameters() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Simulation& lhs, const Simulation& rhs) noexcept;
bool operator!=(const Simulation& lhs, const Simulation& rhs) noexcept;

} //~namespace fw
} //~namespace ribi

#endif // SIMULATION_H
