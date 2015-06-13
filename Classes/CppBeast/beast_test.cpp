#include "beast.h"

#include <cassert>
#include <chrono>

#include <QFile>

#include "RInside.h"

#include "fileio.h"
#include "testtimer.h"
#include "ribi_rinside.h"
#include "trace.h"

#ifndef NDEBUG
void ribi::Beast::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
    ribi::Rinside();
    auto& r = ribi::Rinside().Get();
    r.parseEval("library(ape)");
    r.parseEval("library(geiger)");
    r.parseEval("library(phangorn)");
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Constructor"); }
  {
    Beast();
  }
  Beast b;
  ribi::fileio::FileIo f;

  const std::string log_file_bd{"CppBeastLogFileBirthDeath.log"};
  const std::string log_file_coa{"CppBeastLogFileCoalescent.log"};
  const std::vector<std::string> resource_filenames
    =
    {
      log_file_bd, log_file_coa
    };
  //Create resources
  for (const auto& s: resource_filenames)
  {
    if (!f.IsRegularFile(s))
    {
      QFile((std::string(":/CppBeast/") + s).c_str()).copy(s.c_str());
    }
    assert(f.IsRegularFile(s));
  }

  if (!"Speed comparison AnalyzeBirthDeath")
  {
    const std::string png_filename{f.GetTempFileName(".png")};

    const auto t2 = std::chrono::system_clock::now();
    b.AnalyzeBirthDeathRinside(
      log_file_bd,
      png_filename
    );
    const auto d2 = std::chrono::system_clock::now() - t2;

    const auto t1 = std::chrono::system_clock::now();
    b.AnalyzeBirthDeathRscript(
      log_file_bd,
      png_filename
    );

    const auto d1 = std::chrono::system_clock::now() - t1;
    assert(d2 < d1 / 10);
  }

  if (!"Speed comparison AnalyzeCoalescent")
  {
    const std::string png_filename1{f.GetTempFileName(".png")};
    const std::string png_filename2{f.GetTempFileName(".png")};

    const auto t2 = std::chrono::system_clock::now();
    b.AnalyzeCoalescentRinside(
      log_file_coa,
      png_filename1,
      png_filename2
    );
    const auto d2 = std::chrono::system_clock::now() - t2;

    const auto t1 = std::chrono::system_clock::now();
    b.AnalyzeCoalescentRscript(
      log_file_coa,
      png_filename1,
      png_filename2
    );

    const auto d1 = std::chrono::system_clock::now() - t1;
    assert(d2 < d1 / 10);
  }

  //Cleanup resources
  for (const auto& s: resource_filenames)
  {
    assert(f.IsRegularFile(s));
    f.DeleteFile(s);
    assert(!f.IsRegularFile(s));
  }
}
#endif

