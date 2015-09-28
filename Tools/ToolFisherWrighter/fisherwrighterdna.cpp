#include "fisherwrighterdna.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

#include "trace.h"

ribi::fw::Dna::Dna(
  const double mutation_rate,
  std::mt19937& rnd_engine,
  const std::string& sequence
)
  : m_mutation_rate{mutation_rate},
    m_rnd_engine(rnd_engine),
    m_sequence{sequence}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::fw::Dna ribi::fw::Dna::CreateOffspring() noexcept
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
      const char c{CreateRandomBasePair()};
      next_sequence[i] = c;
    }
  }
  const Dna offspring(
    m_mutation_rate,
    m_rnd_engine,
    next_sequence
  );
  return offspring;
}


char ribi::fw::Dna::CreateRandomBasePair(std::mt19937& rnd_engine) noexcept
{
  std::uniform_int_distribution<int> d(0,3);
  const int i{d(rnd_engine)};
  switch (i)
  {
    case 0: return 'A';
    case 1: return 'C';
    case 2: return 'G';
    case 3: return 'T';
  }
  assert(!"Should not get here");
  throw std::logic_error("Dna::CreateRandomBasePair: should not get here");
}

char ribi::fw::Dna::CreateRandomBasePair() noexcept
{
  return CreateRandomBasePair(m_rnd_engine);
}


std::string ribi::fw::Dna::CreateRandomDna(
  const int dna_length,
  std::mt19937& rnd_engine
) noexcept
{
  assert(dna_length >= 0);
  std::string s(dna_length,0);
  std::generate(std::begin(s),std::end(s),
    [&rnd_engine]() { return Dna::CreateRandomBasePair(rnd_engine); }
  );
  return s;
}

std::string ribi::fw::Dna::CreateRandomDna(
  const int dna_length
) noexcept
{
  return CreateRandomDna(dna_length,m_rnd_engine);
}

double ribi::fw::Dna::GetRandomFraction() noexcept
{
  //Can use static here? Added to Dna::Test
  static std::uniform_real_distribution<double> d(0.0,1.0);
  //The random value x gets drawn here
  const double f{d(m_rnd_engine)};

  assert(f >= 0.0);
  assert(f <= 1.0);
  return f;
}



bool ribi::fw::operator==(const Dna& lhs, const Dna& rhs) noexcept
{
  return
       lhs.GetSequence() == rhs.GetSequence() //Sequence first, because that is expected to vary more
    && lhs.GetMutationRate() == rhs.GetMutationRate()
  ;
}

bool ribi::fw::operator!=(const Dna& lhs, const Dna& rhs) noexcept
{
  return !(lhs == rhs);
}
