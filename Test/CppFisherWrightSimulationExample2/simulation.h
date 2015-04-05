#ifndef SIMULATION_H
#define SIMULATION_H

#include <random>
#include <vector>

#include "individual.h"
#include "parameters.h"
#include "sequence.h"

///Fisher-Wright simulation
///with individuals that only have DNA
struct Simulation
{
  ///Use randomly created individuals
  Simulation(
    const Parameters& parameters
  ) : Simulation(parameters,CreateIndividuals(parameters)) {}

  ///Put in your own individuals
  Simulation(
    const Parameters& parameters,
    const std::vector<Individual>& individuals
  );

  std::string GetPedigree() const noexcept;

  const std::vector<std::vector<Individual>>& GetGenerations() const noexcept { return m_generations; }

  std::vector<Sequence> GetSequences() const noexcept;

  //Go to the next generation
  void NextGeneration() noexcept;

  private:
  std::vector<std::vector<Individual>> m_generations;

  const Parameters m_parameters;

  ///Random number generator engine
  std::mt19937 m_rnd_engine;

  ///Create initial population of individuals with random DNA sequences
  std::vector<Individual> CreateIndividuals(
    const Parameters& parameters
  ) noexcept;

  ///Create initial population of individuals with random DNA sequences
  ///Non-const, because random numbers are used
  std::vector<Individual> CreateNextGeneration(
    std::vector<Individual>& current_generation
  ) noexcept;

  static std::vector<Parameters> CreateTestParameters() noexcept;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // SIMULATION_H
