#include "connectthreemove.h"

#include <cassert>

#include "testtimer.h"
#include "trace.h"

#ifndef NDEBUG
void ribi::con3::Move::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
