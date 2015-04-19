#include "dna_r.h"

#include <cassert>

#include "dnasequence.h"
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
  using ribi::DnaSequence;
  {
    ribi::fileio::FileIo();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  ribi::fileio::FileIo fileio;
  const bool verbose{false};
  const bool test_throughly{true};
  if (!test_throughly)
  {
    TRACE("DnaR not thoroughly tested");
    return;
  }
  if (verbose) { TRACE("PlotSequences"); }
  {
    std::vector<DnaSequence> v;
    v.push_back(DnaSequence("1","ACGTA"));
    v.push_back(DnaSequence("2","ACGTC"));
    v.push_back(DnaSequence("3","ACGTG"));
    v.push_back(DnaSequence("4","ACGTT"));

    const std::string filename{fileio.GetTempFileName(".png")};
    DnaR().PlotSequences(v,filename);
    assert(fileio.IsRegularFile(filename));
  }
}
#endif

