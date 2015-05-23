#include "paperrockscissorswithtraitindividual.h"

#include <cassert>

PaperRockScissorsWithTraitIndividual::PaperRockScissorsWithTraitIndividual(
    const PaperRockScissors prs,
    const double trait
  )
  : m_prs(prs), m_trait(trait)
{
  #ifndef NDEBUG
  Test();
  #endif
}

PaperRockScissorsWithTraitIndividual::PaperRockScissorsWithTraitIndividual(
  const Individual& other)
  : m_prs(other.m_prs),
    m_trait(other.m_trait)
{

}

PaperRockScissorsWithTraitIndividual& PaperRockScissorsWithTraitIndividual::operator=(
  const Individual& rhs
)
{
  const_cast<Prs&>(this->m_prs) = rhs.m_prs;
  const_cast<double&>(this->m_trait) = rhs.m_trait;
  return *this;
}

#ifndef NDEBUG
void PaperRockScissorsWithTraitIndividual::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const Individual a(Prs::paper,1.2);
    const Individual b(Prs::paper,1.2);
    assert(a == b);
  }
  {
    const Individual a(Prs::paper,1.2);
    const Individual b(Prs::rock,1.2);
    assert(a != b);
  }
  {
    const Individual a(Prs::paper,1.2);
    const Individual b(Prs::paper,2.3);
    assert(a != b);
  }
  {
    const Individual a(Prs::paper,1.2);
    Individual b(Prs::paper,2.3);
    assert(a != b);
    b = a;
    assert(a == b);
  }
  {
    const Individual a(Prs::paper,1.2);
    const Individual b(a);
    assert(a == b);
  }
}
#endif

bool DoesBeat(
  const PaperRockScissorsWithTraitIndividual& lhs,
  const PaperRockScissorsWithTraitIndividual& rhs
)
{
  return DoesBeat(lhs.GetPrs(),rhs.GetPrs());
}

bool operator==(
  const PaperRockScissorsWithTraitIndividual& lhs,
  const PaperRockScissorsWithTraitIndividual& rhs
)
{
  return
       lhs.GetPrs() == rhs.GetPrs()
    && lhs.GetTrait() == rhs.GetTrait()
  ;
}

bool operator!=(
  const PaperRockScissorsWithTraitIndividual& lhs,
  const PaperRockScissorsWithTraitIndividual& rhs
)
{
  return !(lhs == rhs);
}
