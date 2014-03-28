#include "visualabcmenudialog.h"

#include <cassert>
#include <iostream>

#include "trace.h"

int ribi::VisualAbcMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::VisualAbcMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Visual ABC",
    "visual ABC editor",
    "the 5th of May 2011",
    "2011-2014",
    "http://www.richelbilderbeek.nl/ToolVisualAbc.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  //a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  return a;
}

ribi::Help ribi::VisualAbcMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::VisualAbcMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramVisualAbc
  };
  assert(p);
  return p;
}

std::string ribi::VisualAbcMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::VisualAbcMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-05-01: Version 1.0: initial version",
    "2011-05-01: Version 1.1: added button to save ABC text"
  };
}

#ifndef NDEBUG
void ribi::VisualAbcMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::VisualAbcMenuDialog::Test");
  TRACE("Finished ribi::VisualAbcMenuDialog::Test successfully");
}
#endif
