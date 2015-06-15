#include "primeexpertmenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

int ribi::PrimeExpertMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << this->GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::PrimeExpertMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PrimeExpert",
    "prime look-up table",
    "the 11th of Oktober 2013",
    "2008-2015",
    "http://www.richelbilderbeek.nl/ToolPrimeExpert.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::PrimeExpertMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    }
    ,
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::PrimeExpertMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPrimeExpert
  };
  assert(p);
  return p;
}

std::string ribi::PrimeExpertMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::PrimeExpertMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2008-07-12: Version 1.0: initial version in C++ Builder",
    "2011-02-26: Version 2.0: port to Qt Creator",
    "2013-10-11: Version 2.1: conformized for ProjectRichelBilderbeek",
    "2013-11-04: Version 2.2: conformized for ProjectRichelBilderbeekConsole",
  };
}

#ifndef NDEBUG
void ribi::PrimeExpertMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
