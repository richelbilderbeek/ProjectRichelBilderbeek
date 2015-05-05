#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "mutualismbreakdownermenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

//#include "asciiarter.h"
#include "mutualismbreakdownermenudialog.h"
#include "fileio.h"
//#include "imagecanvas.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::MutualismBreakdownerMenuDialog::MutualismBreakdownerMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::MutualismBreakdownerMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1 || argc > 4)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::MutualismBreakdownerMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "MutualismBreakdowner",
    "simulation",
    "the 3rd of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolMutualismBreakdowner.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

boost::shared_ptr<const ribi::Program> ribi::MutualismBreakdownerMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramMutualismBreakdowner);
  assert(p);
  return p;
}

std::string ribi::MutualismBreakdownerMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::MutualismBreakdownerMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-03: Version 0.1: initial version",
    "2015-05-05: Version 1.0: added menu screens",
  };
}

ribi::Help ribi::MutualismBreakdownerMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "MutualismBreakdowner",
    "Tool to create ASCII art images from images",
    {
      //No additional options
    },
    {
      "MutualismBreakdowner [option]\n",
      "MutualismBreakdowner --about",
      "",
      "MutualismBreakdowner [picture input filename] [text output filename] [columns = 78]\n",
      "MutualismBreakdowner source.png target.txt",
      "MutualismBreakdowner source.png target.txt 254"
    }
  );
}

#ifndef NDEBUG
void ribi::MutualismBreakdownerMenuDialog::Test() noexcept
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
