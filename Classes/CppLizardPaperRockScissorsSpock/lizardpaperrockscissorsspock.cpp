#include "lizardpaperrockscissorsspock.h"

#include <cassert>

bool ribi::DoesBeat(
  const LizardPaperRockScissorsSpock lhs,
  const LizardPaperRockScissorsSpock rhs
)
{
  using Lprss = LizardPaperRockScissorsSpock;
  switch (lhs)
  {
    case Lprss::lizard: return rhs == Lprss::paper || rhs == Lprss::spock;
    case Lprss::paper: return rhs == Lprss::spock || rhs == Lprss::rock;
    case Lprss::rock: return rhs == Lprss::scissors || rhs == Lprss::lizard;
    case Lprss::scissors: return rhs == Lprss::paper || rhs == Lprss::lizard;
    case Lprss::spock: return rhs == Lprss::rock || rhs == Lprss::scissors;
  }
  /*
  const int a{static_cast<int>(lhs)};
  const int b{static_cast<int>(rhs)};
  return (a + 4) % 5 == b
    || (a + 2) % 5 == b;
  */
  assert(!"Should not get here");
  return false;
}
