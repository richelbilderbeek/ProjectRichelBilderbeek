#ifndef NDEBUG
#include "lizardpaperrockscissorsspock.h"

#include <cassert>

void ribi::TestLizardPaperRockScissorsSpock() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using Lprss = LizardPaperRockScissorsSpock;
  const Lprss paper{Lprss::paper};
  const Lprss rock{Lprss::rock};
  const Lprss scissors{Lprss::scissors};
  const Lprss lizard{Lprss::lizard};
  const Lprss spock{Lprss::spock};

  // Rock crushes Scissors or crushes Lizard
  assert(DoesBeat(rock,scissors));
  assert(DoesBeat(rock,lizard));

  assert(!DoesBeat(rock,paper));
  assert(!DoesBeat(rock,rock));
  assert(!DoesBeat(rock,spock));

  //Scissors cuts Paper or decapitates Lizard
  assert(DoesBeat(scissors,paper));
  assert(DoesBeat(scissors,lizard));
  assert(!DoesBeat(scissors,scissors));
  assert(!DoesBeat(scissors,rock));
  assert(!DoesBeat(scissors,spock));

  // Paper covers Rock or disproves Spock
  assert(DoesBeat(paper,rock));
  assert(DoesBeat(paper,spock));
  assert(!DoesBeat(paper,paper));
  assert(!DoesBeat(paper,lizard));
  assert(!DoesBeat(paper,scissors));

  // Lizard eats Paper or poisons Spock
  assert(DoesBeat(lizard,paper));
  assert(DoesBeat(lizard,spock));
  assert(!DoesBeat(lizard,rock));
  assert(!DoesBeat(lizard,lizard));
  assert(!DoesBeat(lizard,scissors));

  // Spock vaporizes Rock or smashes Scissors
  assert(DoesBeat(spock,rock));
  assert(DoesBeat(spock,scissors));
  assert(!DoesBeat(spock,paper));
  assert(!DoesBeat(spock,lizard));
  assert(!DoesBeat(spock,spock));

}
#endif

