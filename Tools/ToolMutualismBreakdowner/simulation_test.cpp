#ifndef NDEBUG
#include "simulation.h"

#include <cassert>

void Simulation::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
}

#endif
