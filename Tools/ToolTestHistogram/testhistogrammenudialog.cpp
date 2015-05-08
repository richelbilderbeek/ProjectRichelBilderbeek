#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testhistogrammenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

#include "testhistogrammenudialog.h"
#include "fileio.h"

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestHistogramMenuDialog::TestHistogramMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestHistogramMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1 || argc > 4)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::TestHistogramMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestHistogram",
    "tests the Histogram class",
    "the 8th of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolTestHistogram.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

boost::shared_ptr<const ribi::Program> ribi::TestHistogramMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p; //(new ProgramTestHistogram);
  assert(p);
  return p;
}

std::string ribi::TestHistogramMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::TestHistogramMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-08: Version 1.0: initial version",
  };
}

ribi::Help ribi::TestHistogramMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "TestHistogram",
    "tests the Histogram class",
    {
      //No additional options
    },
    {
    }
  );
}

#ifndef NDEBUG
void ribi::TestHistogramMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
