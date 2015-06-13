#include "dna_r.h"

#include <cassert>
#include <chrono>

#include "RInside.h"

#include "dnasequence.h"
#include "fileio.h"
#include "testtimer.h"
#include "ribi_rinside.h"
#include "trace.h"

#ifndef NDEBUG
void ribi::DnaR::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
    auto& r = ribi::Rinside().Get();
    r.parseEval("library(ape)");
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  ribi::fileio::FileIo f;
  DnaR d;
  using ribi::DnaSequence;
  const bool verbose{false};

  if (verbose) { TRACE("PlotSequences"); }
  {
    std::vector<DnaSequence> v;
    v.push_back(DnaSequence("1","ACGTA"));
    v.push_back(DnaSequence("2","ACGTC"));
    v.push_back(DnaSequence("3","ACGTG"));
    v.push_back(DnaSequence("4","ACGTT"));

    const std::string filename{f.GetTempFileName(".png")};
    d.PlotSequences(v,filename);
    assert(f.IsRegularFile(filename));
  }
  if (!"Speed comparison PlotSequences")
  {
    std::vector<DnaSequence> v;
    v.push_back(DnaSequence("1","ACGTA"));
    v.push_back(DnaSequence("2","ACGTC"));
    v.push_back(DnaSequence("3","ACGTG"));
    v.push_back(DnaSequence("4","ACGTT"));
    const std::string filename{f.GetTempFileName(".png")};
    const auto t2 = std::chrono::system_clock::now();
    d.PlotSequencesRinside(v,filename);
    const auto d2 = std::chrono::system_clock::now() - t2;
    const auto t1 = std::chrono::system_clock::now();
    d.PlotSequencesRscript(v,filename);
    const auto d1 = std::chrono::system_clock::now() - t1;
    assert(d2 < d1 / 10);
  }
}
#endif

