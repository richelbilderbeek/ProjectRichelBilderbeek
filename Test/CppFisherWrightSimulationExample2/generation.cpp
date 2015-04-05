#include "generation.h"

#include <algorithm>
#include <cassert>


std::vector<Sequence> Generation::GetSequences() const noexcept
{
  std::vector<Sequence> alignments;
  std::transform(
    std::begin(m_individuals),
    std::end(m_individuals),
    std::back_inserter(alignments),
    [](const Individual& i)
    {
      const std::string description = std::to_string(i.GetIndex());
      assert(std::stoi(description) == i.GetIndex());
      return Sequence(description,i.GetDna().GetSequence());
    }
  );

  return alignments;
}

const Individual& Generation::operator[](const int index) const noexcept
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_individuals.size()));
  return m_individuals[index];
}

Individual& Generation::operator[](const int index) noexcept
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_individuals.size()));
  return m_individuals[index];
}
