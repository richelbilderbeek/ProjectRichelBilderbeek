#include "individual.h"

#include <cassert>

#include "dna.h"
#include "parameters.h"

int Individual::sm_index = 0;

Individual::Individual(
  const Dna& dna,
  const std::shared_ptr<Pedigree>& pedigree
  )
  : m_dna{dna},
    m_index{sm_index++}, //Use the previous value
    m_pedigree{pedigree}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_pedigree);
}

Individual Individual::CreateOffspring(const std::string& name) noexcept
{
  Individual kid(
    m_dna.CreateOffspring(),
    m_pedigree->CreateOffspring(name)
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

void Individual::SetName(const std::string& name) noexcept
{
  m_pedigree->SetName(name);
}

bool operator==(const Individual& lhs, const Individual& rhs) noexcept
{
  return lhs.GetDna() == rhs.GetDna();
}
