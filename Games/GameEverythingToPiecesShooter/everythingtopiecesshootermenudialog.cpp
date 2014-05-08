#include "everythingtopiecesshootermenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"

int ribi::Boenken::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::Boenken::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Boenken",
    "a multiplayer soccer/billiards game",
    "the 17th of November 2012",
    "2007-2014",
    "http://www.richelbilderbeek.nl/GameBoenken.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}

ribi::Help ribi::Boenken::MenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::Boenken::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramBoenken
  };
  assert(p);
  return p;
}

std::string ribi::Boenken::MenuDialog::GetVersion() const noexcept
{
  return "4.1";
}

std::vector<std::string> ribi::Boenken::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2000-xx-xx: version 0.0: wrote QBASIC version of Boenken",
    "2007-10-18: version 1.0: port from QBASIC to C++ Builder",
    "2007-12-30: version 2.0: added old-school-graphics mode, two-button control and option to set the friction of the players",
    "2010-08-14: version 3.0: initial port to cross-platform, using Qt Creator. Added doxygen support",
    "2010-08-15: version 3.1: created basic menu functionality, improved doxygen documentation,  improved code (seperated GUI from game rules, all sprites can be deleted by boost::checked_delete only)",
    "2012-03-07: version 4.0: conformized naming and architecture for ProjectRichelBilderbeek"
    "2012-11-17: version 4.1: added a fancy color gradient to the main menu"
  };
}

#ifndef NDEBUG
void ribi::Boenken::MenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Boenken::MenuDialog::Test");
  TRACE("Finished ribi::Boenken::MenuDialog::Test successfully");
}
#endif
