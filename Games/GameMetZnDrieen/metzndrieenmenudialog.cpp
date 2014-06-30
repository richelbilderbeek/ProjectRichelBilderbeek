/*

#include "metzndrieenmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "richelbilderbeekprogram.h"
#include "trace.h"

int ribi::MetZnDrieenMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::MetZnDrieenMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Met z'n Drieen",
    "Billy-themed connect-three game",
    "today",
    "200x-2014",
    "http://www.richelbilderbeek.nl/GameMetZnDrieen.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

ribi::Help ribi::MetZnDrieenMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::MetZnDrieenMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramMetZnDrieen
  };
  assert(p);
  return p;
}

std::string ribi::MetZnDrieenMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::MetZnDrieenMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::MetZnDrieenMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::MetZnDrieenMenuDialog::Test");
  TRACE("Finished ribi::MetZnDrieenMenuDialog::Test successfully");
}
#endif

*/
