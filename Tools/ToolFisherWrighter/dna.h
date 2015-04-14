#ifndef DNA_H
#define DNA_H

#include <random>
#include <string>

struct Dna
{
  explicit Dna(
    const double mutation_rate,
    std::mt19937& rnd_engine,
    const std::string& sequence
  );

  //Creates random DNA
  explicit Dna(
    const double mutation_rate,
    std::mt19937& rnd_engine,
    const int dna_length
  ) : Dna(mutation_rate,rnd_engine,CreateRandomDna(dna_length)) {}

  Dna CreateOffspring() noexcept;

  double GetMutationRate() const noexcept { return m_mutation_rate; }

  std::mt19937& GetRndEngine() noexcept { return m_rnd_engine; }

  const std::string& GetSequence() const noexcept { return m_sequence; }

  private:

  const double m_mutation_rate;
  std::mt19937& m_rnd_engine;
  const std::string m_sequence;

  static char CreateRandomBasePair() noexcept;
  static std::string CreateRandomDna(const int dna_length) noexcept;
  double GetRandomFraction() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

///Checks if different DNA have the same attributes (DNA and mutation rate)
///This does not take the random number generator into accoun
bool operator==(const Dna& lhs, const Dna& rhs) noexcept;

#endif // DNA_H
