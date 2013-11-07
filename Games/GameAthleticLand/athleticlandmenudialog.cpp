#include "athleticlandmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

int ribi::AthleticLandMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::AthleticLandMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "AthleticLand",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GameAthleticLand.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::AthleticLandMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::AthleticLandMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramAthleticLand
  };
  assert(p);
  return p;
}

const std::string ribi::AthleticLandMenuDialog::GetVersion() const noexcept
{
  return "0.1";
}

const std::vector<std::string> ribi::AthleticLandMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 0.1: conformized to ProjectRichelBilderbeekConsole"
  };
}
