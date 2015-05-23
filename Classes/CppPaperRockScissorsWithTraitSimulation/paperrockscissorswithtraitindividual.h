#ifndef PAPERROCKSCISSORSWITHTRAITINDIVIDUAL_H
#define PAPERROCKSCISSORSWITHTRAITINDIVIDUAL_H

#include "paperrockscissors.h"

struct PaperRockScissorsWithTraitIndividual
{
  using Prs = PaperRockScissors;  using Individual = PaperRockScissorsWithTraitIndividual;


  PaperRockScissorsWithTraitIndividual(
    const Prs prs,
    const double trait
  );
  PaperRockScissorsWithTraitIndividual(const Individual&);
  PaperRockScissorsWithTraitIndividual& operator=(const Individual&);

  Prs GetPrs() const noexcept { return m_prs; }
  double GetTrait() const noexcept { return m_trait; }

  private:
  const Prs m_prs;
  const double m_trait;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool DoesBeat(
  const PaperRockScissorsWithTraitIndividual& lhs,
  const PaperRockScissorsWithTraitIndividual& rhs
);

bool operator==(
  const PaperRockScissorsWithTraitIndividual& lhs,
  const PaperRockScissorsWithTraitIndividual& rhs
);

bool operator!=(
  const PaperRockScissorsWithTraitIndividual& lhs,
  const PaperRockScissorsWithTraitIndividual& rhs
);

#endif // PAPERROCKSCISSORSWITHTRAITINDIVIDUAL_H
