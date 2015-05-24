#include "paperrockscissors.h"

bool ribi::DoesBeat(const PaperRockScissors lhs, const PaperRockScissors rhs)
{
  const int a{static_cast<int>(lhs)};
  const int b{static_cast<int>(rhs)};
  return (a + 1) % 3 == b;
}
