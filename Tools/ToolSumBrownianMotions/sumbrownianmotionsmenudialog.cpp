#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "sumbrownianmotionsmenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

//#include "asciiarter.h"
#include "sumbrownianmotionsmenudialog.h"
#include "fileio.h"
//#include "imagecanvas.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::SumBrownianMotionsMenuDialog::SumBrownianMotionsMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::SumBrownianMotionsMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1 || argc > 4)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::SumBrownianMotionsMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SumBrownianMotions",
    "simulation",
    "the 3rd of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolSumBrownianMotions.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

boost::shared_ptr<const ribi::Program> ribi::SumBrownianMotionsMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p; //(new ProgramSumBrownianMotions);
  assert(p);
  return p;
}

std::string ribi::SumBrownianMotionsMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::SumBrownianMotionsMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-08: Version 1.0: initial version",
  };
}

ribi::Help ribi::SumBrownianMotionsMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "SumBrownianMotions",
    "Tool to create ASCII art images from images",
    {
      //No additional options
    },
    {
      "SumBrownianMotions [option]\n",
      "SumBrownianMotions --about",
      "",
      "SumBrownianMotions [picture input filename] [text output filename] [columns = 78]\n",
      "SumBrownianMotions source.png target.txt",
      "SumBrownianMotions source.png target.txt 254"
    }
  );
}

#ifndef NDEBUG
void ribi::SumBrownianMotionsMenuDialog::Test() noexcept
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
