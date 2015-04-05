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

  std::vector<Individual> GetCurrentGeneration() const noexcept { return m_current_generation; }

  std::vector<Sequence> GetSequences() const noexcept;

  //Go to the next generation
  void NextGeneration() noexcept;

  private:
  ///The alignments created at the end of Run
  //std::vector<std::string> m_alignments;
  std::vector<Individual> m_current_generation;

  const Parameters m_parameters;

  ///Random number generator engine
  std::mt19937 m_rnd_engine;

  ///Create initial population of individuals with random DNA sequences
  static std::vector<Individual> CreateIndividuals(
    const Parameters& parameters
  ) noexcept;

  ///Create initial population of individuals with random DNA sequences
  ///Non-const, because random numbers are used
  std::vector<Individual> CreateNextGeneration(
    const std::vector<Individual>& current_generation
  ) noexcept;

  std::string CreateMutatedDna(
    const std::string& dna,
    const double mutation_rate_per_base_pair
  ) noexcept;

  static char CreateRandomBasePair() noexcept;

  static std::string CreateRandomDna(const int dna_length) noexcept;

  static std::vector<Parameters> CreateTestParameters() noexcept;

  double GetRandomFraction() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // SIMULATION_H
