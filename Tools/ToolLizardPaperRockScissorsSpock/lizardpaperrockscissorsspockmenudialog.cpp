#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "lizardpaperrockscissorsspockmenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

#include "lizardpaperrockscissorsspocksimulation.h"
#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::lprss::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::lprss::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc > 0) //Always
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  return 0;
}

ribi::About ribi::lprss::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "LizardPaperRockScissorsSpock",
    "lizard-paper-rock-scissors-spock simulation",
    "the 11th of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolLizardPaperRockScissorsSpock.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

boost::shared_ptr<const ribi::Program> ribi::lprss::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramLizardPaperRockScissorsSpock);
  assert(p);
  return p;
}

std::string ribi::lprss::MenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::lprss::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-10: Version 0.1: initial standalone version",
    "2015-05-11: Version 1.0: conformized version",
    "2015-05-24: Version 1.1: added to ProjectRichelBilderbeek, moved to namespace ribi::lprss"
  };
}

ribi::Help ribi::lprss::MenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "PaperRockScissorsLizardSpock",
    "lizard-paper-rock-scissors-spock simulation",
    {
      //No additional options
    },
    {
    }
  );
}

#ifndef NDEBUG
void ribi::lprss::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    TestLizardPaperRockScissorsSpock();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
