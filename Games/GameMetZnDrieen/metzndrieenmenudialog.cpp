#include "metzndrieenmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

int ribi::MetZnDrieenMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::MetZnDrieenMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Met z'n Drieen",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GameMetZnDrieen.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::MetZnDrieenMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::MetZnDrieenMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramMetZnDrieen
  };
  assert(p);
  return p;
}

const std::string ribi::MetZnDrieenMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::MetZnDrieenMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::X::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::X::Test");
  TRACE("Finished ribi::X::Test successfully");
}
#endif
