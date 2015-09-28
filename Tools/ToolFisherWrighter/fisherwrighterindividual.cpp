#include "fisherwrighterindividual.h"

#include <cassert>

#include "counter.h"
#include "fisherwrighterdna.h"
#include "fisherwrighterparameters.h"

ribi::fw::Individual::Individual(
  const Dna& dna,
  const std::shared_ptr<Pedigree>& pedigree,
  ribi::Counter& counter
  )
  : m_counter(counter),
    m_dna{dna},
    m_index{counter.Get()}, //Use the previous value
    m_pedigree{pedigree}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_pedigree);

  ++counter;
}

ribi::fw::Individual ribi::fw::Individual::CreateOffspring(const std::string& name) noexcept
{
  Individual kid(
    m_dna.CreateOffspring(),
    m_pedigree->CreateOffspring(name),
    m_counter
  );
  if (name.empty())
  {
    int index = kid.GetIndex();
    std::string name;
    while (index != 0)
    {
      name += std::string(1,'A' + (index % 26));
      index /= 26;
    }
    kid.SetName(name);
  }

  return kid;
}

void ribi::fw::Individual::SetName(const std::string& name) noexcept
{
  m_pedigree->SetName(name);
}

bool ribi::fw::operator==(const Individual& lhs, const Individual& rhs) noexcept
{
  return lhs.GetDna() == rhs.GetDna();
}

bool ribi::fw::operator!=(const Individual& lhs, const Individual& rhs) noexcept
{
  return !(lhs == rhs);
}
