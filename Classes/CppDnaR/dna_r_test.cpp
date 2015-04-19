#include "dna_r.h"

#include <cassert>

#include "fileio.h"
#include "testtimer.h"
#include "trace.h"

#ifndef NDEBUG
void DnaR::Test() noexcept
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
  const bool test_throughly{true};
  if (!test_throughly)
  {
    TRACE("DnaR not thoroughly tested");
    return;
  }
  if (verbose) { TRACE("DnaR "); }
  {

  }
  assert(!"Done");
}
#endif

