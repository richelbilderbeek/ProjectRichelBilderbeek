#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "simtoppredatorpreymenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::SimTopPredatorPreyMenuDialog::SimTopPredatorPreyMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::SimTopPredatorPreyMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  std::cout << GetHelp() << '\n';
  return 1;
}

ribi::About ribi::SimTopPredatorPreyMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SimTopPredatorPrey",
    "simulation of toppredator-predator-prey",
    "the 27th of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolSimTopPredatorPrey.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::SimTopPredatorPreyMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      //Help::Option('b',"bin","decimal number to be converted to/from Gray code"),
      //Help::Option('d',"dec","decimal number to be converted to/from Gray code")
    },
    {
      //"GrayCoder -d 123456",
      //"GrayCoder -b 010101"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::SimTopPredatorPreyMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramSimTopPredatorPrey
  };
  assert(p);
  return p;
}


std::string ribi::SimTopPredatorPreyMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::SimTopPredatorPreyMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-27: version 1.0: start of versioning",
  };
}

#ifndef NDEBUG
void ribi::SimTopPredatorPreyMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
