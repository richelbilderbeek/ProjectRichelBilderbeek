#ifndef DNA_H
#define DNA_H

#include <random>
#include <string>

struct Dna
{
  Dna(
    const double mutation_rate,
    std::mt19937& rnd_engine,
    const std::string& sequence
  );

  Dna CreateOffspring() noexcept;

  /*
  std::string CreateMutatedDna(
    const std::string& dna,
    const double mutation_rate_per_base_pair
  ) noexcept;
  */
  static char CreateRandomBasePair() noexcept;

  static std::string CreateRandomDna(const int dna_length) noexcept;


  double GetMutationRate() const noexcept { return m_mutation_rate; }

  double GetRandomFraction() noexcept;
  std::mt19937& GetRndEngine() noexcept { return m_rnd_engine; }

  const std::string& GetSequence() const noexcept { return m_sequence; }

  private:

  const double m_mutation_rate;
  std::mt19937& m_rnd_engine;
  const std::string m_sequence;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

///Checks if different DNA have the same attributes (DNA and mutation rate)
///This does not take the random number generator into accoun
bool operator==(const Dna& lhs, const Dna& rhs) noexcept;

#endif // DNA_H
