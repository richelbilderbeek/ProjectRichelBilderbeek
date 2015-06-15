#include "predickadvocatormenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"


int ribi::PreDickAdvocaTorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::PreDickAdvocaTorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PreDickAdvocaTor",
    "tool to correctly predict WC scores", //if the lucky number is correct and the truth becomes reality
    "the 3rd of December 2013",
    "20010-2015",
    "http://www.richelbilderbeek.nl/ToolPreDickAdvocaTor.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::PreDickAdvocaTorMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::PreDickAdvocaTorMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramPreDickAdvocaTor
  };
  assert(p);
  return p;
}

std::string ribi::PreDickAdvocaTorMenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::PreDickAdvocaTorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-xx-xx: version 1.0: initial version",
    "2013-12-03: version 2.0: improved user experience, prepare for next WC"
    "2013-12-27: version 2.1: put 2014 WC teams in"
  };
}

#ifndef NDEBUG
void ribi::PreDickAdvocaTorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
