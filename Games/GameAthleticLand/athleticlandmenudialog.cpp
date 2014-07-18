#include "athleticlandmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "richelbilderbeekprogram.h"
#include "trace.h"

int ribi::AthleticLandMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  std::cout
    << this->GetAbout().GetFileTitle() << " cannot be run in console mode\n"
    << std::endl;
  return 0;
}

ribi::About ribi::AthleticLandMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "AthleticLand",
    "MSX game clone",
    "2013-11-07",
    "2013-xxxx",
    "http://www.richelbilderbeek.nl/GameAthleticLand.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

ribi::Help ribi::AthleticLandMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::AthleticLandMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramAthleticLand
  };
  assert(p);
  return p;
}

std::string ribi::AthleticLandMenuDialog::GetVersion() const noexcept
{
  return "0.1";
}

std::vector<std::string> ribi::AthleticLandMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 0.1: conformized to ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::AthleticLandMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::AthleticLandMenuDialog::Test");
  TRACE("Finished ribi::AthleticLandMenuDialog::Test successfully");
}
#endif
