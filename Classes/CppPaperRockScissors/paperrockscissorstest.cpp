#ifndef NDEBUG
#include "paperrockscissors.h"

#include <cassert>

void TestPaperRockScissors() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const PaperRockScissors paper{PaperRockScissors::paper};
  const PaperRockScissors rock{PaperRockScissors::rock};
  const PaperRockScissors scissors{PaperRockScissors::scissors};
  assert(DoesBeat(paper,rock));
  assert(DoesBeat(rock,scissors));
  assert(DoesBeat(scissors,paper));

  assert(!DoesBeat(rock,paper));
  assert(!DoesBeat(scissors,rock));
  assert(!DoesBeat(paper,scissors));

  assert(!DoesBeat(paper,paper));
  assert(!DoesBeat(rock,rock));
  assert(!DoesBeat(scissors,scissors));
}
#endif

