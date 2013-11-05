#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tooltestapproximatormenudialog.h"

#include <cassert>
#include <iostream>

#include "approximator.h"
#include "trace.h"

#pragma GCC diagnostic pop

int ribi::ToolTestApproximatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::ToolTestApproximatorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolTestApproximator",
    "tests the Approximator class",
    "the 28th of August 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestApproximator.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Approximator version: " + Approximator<>::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const ribi::Help ribi::ToolTestApproximatorMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::ToolTestApproximatorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestApproximator
  };
  assert(p);
  return p;
}

const std::string ribi::ToolTestApproximatorMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::ToolTestApproximatorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-08-28: version 1.0: initial version",
    "2013-09-05: version 1.1: transition to namespace ribi",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole"
  };
}
