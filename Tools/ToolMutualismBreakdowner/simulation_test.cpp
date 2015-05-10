#ifndef NDEBUG
#include "simulation.h"

#include <cassert>
#include "testtimer.h"

void Simulation::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);

  // "0.1 0.1 0.005 10 m^-2 0.5 InvertedExponentialConsumption 0.05 0.1 0.5 0.01 m^-2 0.5 0.1 1 0.01 10"

}

#endif
