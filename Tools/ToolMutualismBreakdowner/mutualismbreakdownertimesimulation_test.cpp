#ifndef NDEBUG
#include "mutualismbreakdownertimesimulation.h"

#include <cassert>
#include "testtimer.h"
#include "mutualismbreakdownerseagrassgrowthfunction.h"

void ribi::mb::TimeSimulation::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    SeagrassStressedLogisticGrowth();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
}

#endif
