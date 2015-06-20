#include "histogram_r.h"

#include <cassert>
#include <chrono>

#include "fileio.h"
#include "testtimer.h"
#include "trace.h"
#include "ribi_rinside.h"
#include "RInside.h"

#ifndef NDEBUG
void ribi::HistogramR::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
    ribi::Rinside().Get();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  ribi::fileio::FileIo f;

  HistogramR h;

  if (verbose) { TRACE("ToHistogram"); }
  {
    const std::string filename{f.GetTempFileName(".png")};
    const std::vector<double> v = { 1.0,2.0,2.0,3.0,3.0,3.0};
    assert(!f.IsRegularFile(filename));
    h.ToHistogram(v,filename,HistogramR::GraphicsFormat::png);
    assert(f.IsRegularFile(filename));
    f.DeleteFile(filename);
  }
}
#endif

