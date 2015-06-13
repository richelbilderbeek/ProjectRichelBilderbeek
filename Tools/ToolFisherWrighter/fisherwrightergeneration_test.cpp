#include "fisherwrightergeneration.h"

#include <cassert>
#include <fstream>

#ifndef NDEBUG
void ribi::fw::Generation::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  //operator== on empty vector
  {
    std::vector<Individual> v;
    std::vector<Individual> w;
    Generation a(v);
    Generation b(w);
    assert(a == b);
  }
}
#endif


