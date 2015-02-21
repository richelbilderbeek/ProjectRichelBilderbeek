#include "tankbattalionspritetypes.h"

#include "testtimer.h"
#include "trace.h"

ribi::taba::SpriteTypes::SpriteTypes()
{
  #ifndef NDEBUG
  Test();
  #endif // NDEBUG
}

#ifndef NDEBUG
void ribi::taba::SpriteTypes::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
