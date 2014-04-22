#include "connectthreemove.h"

#include <cassert>

#include "trace.h"

#ifndef NDEBUG
void ribi::con3::Move::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::con3::Move::Test");
  TRACE("Finished ribi::con3::Move::Test successfully");
}
#endif
