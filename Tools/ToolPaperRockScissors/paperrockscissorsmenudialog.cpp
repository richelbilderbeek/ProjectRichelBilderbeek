#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "paperrockscissorsmenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

//#include "paperrockscissors.h"
#include "simulation.h"
#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::PaperRockScissorsMenuDialog::PaperRockScissorsMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::PaperRockScissorsMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc > 0) //Always
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  return 0;
}

ribi::About ribi::PaperRockScissorsMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PaperRockScissors",
    "paper-rock-scissors simulation",
    "the 11th of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolPaperRockScissors.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

boost::shared_ptr<const ribi::Program> ribi::PaperRockScissorsMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p; //(new ProgramPaperRockScissors);
  assert(p);
  return p;
}

std::string ribi::PaperRockScissorsMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::PaperRockScissorsMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-03: Version 0.1: initial standalone version",
    "2015-05-11: Version 1.0: conformized version"
  };
}

ribi::Help ribi::PaperRockScissorsMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "PaperRockScissors",
    "paper-rock-scissors simulation",
    {
      //No additional options
    },
    {
    }
  );
}

#ifndef NDEBUG
void ribi::PaperRockScissorsMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    TestPaperRockScissors();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
