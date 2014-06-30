/*
#include "spaceharrymenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "richelbilderbeekprogram.h"

int ribi::SpaceHarryMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::SpaceHarryMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SpaceHarry",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GameSpaceHarry.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

ribi::Help ribi::SpaceHarryMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::SpaceHarryMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramSpaceHarry
  };
  assert(p);
  return p;
}

std::string ribi::SpaceHarryMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::SpaceHarryMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}
*/
