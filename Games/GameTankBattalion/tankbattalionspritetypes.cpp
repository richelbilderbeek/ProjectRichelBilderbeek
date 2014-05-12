#include "tankbattalionspritetypes.h"

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
  TRACE("Starting ribi::fileio::FileIo::Test");
  TRACE("Finished ribi::fileio::FileIo::Test successfully");
}
#endif
