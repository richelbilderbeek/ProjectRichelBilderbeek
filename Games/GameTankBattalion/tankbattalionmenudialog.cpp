#include "tankbattalionmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>


#include "richelbilderbeekprogram.h"
#include "trace.h"

ribi::taba::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::taba::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::taba::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TankBattalion",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GameTankBattalion.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

ribi::Help ribi::taba::MenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::taba::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramTankBattalion
  };
  assert(p);
  return p;
}

std::string ribi::taba::MenuDialog::GetVersion() const noexcept
{
  return "0.1";
}

std::vector<std::string> ribi::taba::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 0.1: conformized to ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::taba::MenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TankBattalionMenuDialog::Test");
  TRACE("Finished ribi::TankBattalionMenuDialog::Test successfully");
}
#endif
