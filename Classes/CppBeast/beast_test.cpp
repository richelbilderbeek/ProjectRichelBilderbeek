#include "beast.h"

#include <cassert>

#include "fileio.h"
#include "testtimer.h"
#include "trace.h"

#ifndef NDEBUG
void Beast::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Constructor"); }
  {
    Beast();
  }
}
#endif

