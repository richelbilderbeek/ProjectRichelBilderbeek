#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testmultiapproximatormenudialog.h"

#include <cassert>
#include <iostream>

#include "approximator.h"
#include "multiapproximator.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

#pragma GCC diagnostic pop

int ribi::ToolTestMultiApproximatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::ToolTestMultiApproximatorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolTestMultiApproximator",
    "tests the MultiApproximator class",
    "the 23rd of August 2013",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolTestMultiApproximator.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Approximator version: " + Approximator<>::GetVersion());
  a.AddLibrary("MultiApproximator version: " + MultiApproximator<>::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::ToolTestMultiApproximatorMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::ToolTestMultiApproximatorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestMultiApproximator
  };
  assert(p);
  return p;
}

std::string ribi::ToolTestMultiApproximatorMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::ToolTestMultiApproximatorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-08-23: version 1.0: initial version",
    "2013-08-23: version 1.1: display conversion from MultiApproximator to Approximator"
  };
}

#ifndef NDEBUG
void ribi::ToolTestMultiApproximatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
