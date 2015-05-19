#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "paper_rock_scissors.h"

struct Individual
{
  Individual(
    const double trait,
    const PaperRockScissors type
  );
  double m_trait;
  PaperRockScissors m_type;
};

#endif // INDIVIDUAL_H
