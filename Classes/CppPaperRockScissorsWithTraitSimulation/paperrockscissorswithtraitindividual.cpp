#include "paperrockscissorswithtraitindividual.h"

#include <cassert>

ribi::prswt::Individual::Individual(
    const PaperRockScissors prs,
    const double trait
  )
  : m_prs(prs), m_trait(trait)
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::prswt::Individual::Individual(
  const Individual& other)
  : m_prs(other.m_prs),
    m_trait(other.m_trait)
{

}

ribi::prswt::Individual&
  ribi::prswt::Individual::operator=(
  const Individual& rhs
)
{
  using Prs = PaperRockScissors;

  const_cast<Prs&>(this->m_prs) = rhs.m_prs;
  const_cast<double&>(this->m_trait) = rhs.m_trait;
  return *this;
}

#ifndef NDEBUG
void ribi::prswt::Individual::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using Prs = PaperRockScissors;
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

bool ribi::prswt::DoesBeat(
  const Individual& lhs,
  const Individual& rhs
)
{
  return DoesBeat(lhs.GetPrs(),rhs.GetPrs());
}

bool ribi::prswt::operator==(
  const Individual& lhs,
  const Individual& rhs
)
{
  return
       lhs.GetPrs() == rhs.GetPrs()
    && lhs.GetTrait() == rhs.GetTrait()
  ;
}

bool ribi::prswt::operator!=(
  const Individual& lhs,
  const Individual& rhs
)
{
  return !(lhs == rhs);
}
