#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "speciesoftheringsmenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::SpeciesOfTheRingsMenuDialog::SpeciesOfTheRingsMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::SpeciesOfTheRingsMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::SpeciesOfTheRingsMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SpeciesOfTheRings",
    "simulation ring species",
    "the 27th of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolSpeciesOfTheRings.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::SpeciesOfTheRingsMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::SpeciesOfTheRingsMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    //new ribi::ProgramSpeciesOfTheRings
  };
  assert(p);
  return p;
}


std::string ribi::SpeciesOfTheRingsMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::SpeciesOfTheRingsMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-06-16: version 1.0: start of versioning",
  };
}

#ifndef NDEBUG
void ribi::SpeciesOfTheRingsMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
