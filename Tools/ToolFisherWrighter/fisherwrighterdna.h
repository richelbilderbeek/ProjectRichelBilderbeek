#ifndef DNA_H
#define DNA_H

#include <random>
#include <string>

namespace ribi {
namespace fw {

struct Dna
{
  ///Put in your own sequence
  explicit Dna(
    const double mutation_rate,
    std::mt19937& rnd_engine,
    const std::string& sequence
  );

  ///Creates random DNA sequence
  explicit Dna(
    const double mutation_rate,
    std::mt19937& rnd_engine,
    const int dna_length
  ) : Dna(mutation_rate,rnd_engine,CreateRandomDna(dna_length,rnd_engine)) {}

  Dna CreateOffspring() noexcept;

  double GetMutationRate() const noexcept { return m_mutation_rate; }

  std::mt19937& GetRndEngine() noexcept { return m_rnd_engine; }

  const std::string& GetSequence() const noexcept { return m_sequence; }

  private:

  const double m_mutation_rate;
  std::mt19937& m_rnd_engine;
  const std::string m_sequence;

  ///Must be static, because this is used in the constructor
  static char CreateRandomBasePair(std::mt19937& rnd_engine) noexcept;

  char CreateRandomBasePair() noexcept;
  std::string CreateRandomDna(const int dna_length) noexcept;

  ///Must be static, because this is used in the constructor
  static std::string CreateRandomDna(const int dna_length,std::mt19937& rnd_engine) noexcept;

  double GetRandomFraction() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

///Checks if different DNA have the same attributes (DNA and mutation rate)
///This does not take the random number generator into accoun
bool operator==(const Dna& lhs, const Dna& rhs) noexcept;
bool operator!=(const Dna& lhs, const Dna& rhs) noexcept;

} //~namespace fw
} //~namespace ribi

#endif // DNA_H
