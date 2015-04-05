#include "dna.h"

#include <algorithm>
#include <cassert>

Dna::Dna(
  const double mutation_rate,
  std::mt19937& rnd_engine,
  const std::string& sequence
)
  : m_mutation_rate{mutation_rate},
    m_rnd_engine{rnd_engine},
    m_sequence{sequence}
{
  #ifndef NDEBUG
  Test();
  #endif
}

Dna Dna::CreateOffspring() noexcept
{
  //Go through all nucleotides,
  //overwrite with a random base pair by chance
  //(note: the might result in an A being overwritten by an A)
  std::string next_sequence{m_sequence};
  const int sz{static_cast<int>(next_sequence.size())};
  for (int i=0; i!=sz; ++i)
  {
    const double p{GetRandomFraction()};
    if (p < m_mutation_rate)
    {
      assert(i >= 0);
      assert(i < static_cast<int>(next_sequence.size()));
      next_sequence[i] = CreateRandomBasePair();
    }
  }
  const Dna offspring(
    m_mutation_rate,
    m_rnd_engine,
    next_sequence
  );
  return offspring;
}

char Dna::CreateRandomBasePair() noexcept
{
  switch (std::rand() % 4)
  {
    case 0: return 'A';
    case 1: return 'C';
    case 2: return 'G';
    case 3: return 'T';
  }
  assert(!"Should not get here");
}

std::string Dna::CreateRandomDna(
  const int dna_length
) noexcept
{
  assert(dna_length >= 0);
  std::string s(dna_length,0);
  std::generate(std::begin(s),std::end(s),CreateRandomBasePair);
  return s;
}

double Dna::GetRandomFraction() noexcept
{
  static std::uniform_real_distribution<double> d(0.0,1.0);
  //The random value x gets drawn here
  const double f{d(m_rnd_engine)};

  assert(f >= 0.0);
  assert(f <= 1.0);
  return f;
}


#ifndef NDEBUG
void Dna::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Create random DNA
  std::mt19937 rnd_engine;
  {
    const int dna_length{3};
    const std::string dna{Dna::CreateRandomDna(dna_length)};
    assert(dna_length == static_cast<int>(dna.size()));
  }
}
#endif

bool operator==(const Dna& lhs, const Dna& rhs) noexcept
{
  return
       lhs.GetSequence() == rhs.GetSequence() //Sequence first, because that is expected to vary more
    && lhs.GetMutationRate() == rhs.GetMutationRate()
  ;
}
