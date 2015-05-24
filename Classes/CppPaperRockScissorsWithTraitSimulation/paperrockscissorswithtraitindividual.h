#ifndef PAPERROCKSCISSORSWITHTRAITINDIVIDUAL_H
#define PAPERROCKSCISSORSWITHTRAITINDIVIDUAL_H

#include "paperrockscissors.h"

namespace ribi {
namespace prswt { //Paper-Rock-Scissors-With-Trait

struct Individual
{
  Individual(
    const PaperRockScissors prs,
    const double trait
  );
  Individual(const Individual&);
  Individual& operator=(const Individual&);

  PaperRockScissors GetPrs() const noexcept { return m_prs; }
  double GetTrait() const noexcept { return m_trait; }

  private:
  const PaperRockScissors m_prs;
  const double m_trait;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool DoesBeat(
  const Individual& lhs,
  const Individual& rhs
);

bool operator==(
  const Individual& lhs,
  const Individual& rhs
);

bool operator!=(
  const Individual& lhs,
  const Individual& rhs
);

} //~namespace ribi
} //~namespace prswt { //Paper-Rock-Scissors-With-Trait

#endif // PAPERROCKSCISSORSWITHTRAITINDIVIDUAL_H
