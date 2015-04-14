#ifndef SIMULATION_H
#define SIMULATION_H

#include <random>
#include <vector>

#include "generation.h"
#include "individual.h"
#include "parameters.h"
#include "sequence.h"

///Fisher-Wright simulation
///with individuals that only have DNA
struct Simulation
{
  ///Use randomly created individuals
  Simulation(const Parameters& parameters) : Simulation(parameters,CreateFirstGeneration(parameters)) {}

  std::string GetPedigree() noexcept;

  const std::vector<Generation>& GetGenerations() const noexcept { return m_generations; }

  ///Obtain the sequences of the current (most recent) simulation
  ///Equivalent to simulation.GetGenerations().back().GetSequences()
  std::vector<Sequence> GetCurrentSequences() const noexcept;

  //Go to the next generation
  void NextGeneration() noexcept;

  private:
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
  Generation CreateFirstGeneration(
    const Parameters& parameters
  ) noexcept;

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

#endif // SIMULATION_H
