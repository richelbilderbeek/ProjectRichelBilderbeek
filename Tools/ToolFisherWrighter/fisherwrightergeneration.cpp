#include "fisherwrightergeneration.h"

#include <algorithm>
#include <cassert>

ribi::fw::Generation::Generation(const std::vector<Individual>& individuals)
  : m_individuals{individuals}
{
  #ifndef NDEBUG
  Test();
  #endif
}


std::vector<ribi::DnaSequence> ribi::fw::Generation::GetSequences() const noexcept
{
  std::vector<ribi::DnaSequence> alignments;
  std::transform(
    std::begin(m_individuals),
    std::end(m_individuals),
    std::back_inserter(alignments),
    [](const Individual& i)
    {
      const std::string description = std::to_string(i.GetIndex());
      assert(std::stoi(description) == i.GetIndex());
      return ribi::DnaSequence(description,i.GetDna().GetSequence());
    }
  );

  return alignments;
}

const ribi::fw::Individual& ribi::fw::Generation::operator[](const int index) const noexcept
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_individuals.size()));
  return m_individuals[index];
}

ribi::fw::Individual& ribi::fw::Generation::operator[](const int index) noexcept
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_individuals.size()));
  return m_individuals[index];
}

bool ribi::fw::operator==(const Generation& lhs, const Generation& rhs) noexcept
{
  return
    lhs.GetIndividuals() == rhs.GetIndividuals()
  ;
}
