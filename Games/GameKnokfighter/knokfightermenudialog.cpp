#include "knokfightermenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "trace.h"

int ribi::KnokfighterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::KnokfighterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Knokfighter",
    "Double Dragon clone",
    "today",
    "200x-201x",
    "http://www.richelbilderbeek.nl/GameKnokfighter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

ribi::Help ribi::KnokfighterMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::KnokfighterMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramKnokfighter
  };
  assert(p);
  return p;
}

std::string ribi::KnokfighterMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::KnokfighterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::KnokfighterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::KnokfighterMenuDialog::Test");
  TRACE("Finished ribi::KnokfighterMenuDialog::Test successfully");
}
#endif
