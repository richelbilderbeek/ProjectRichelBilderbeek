#include "simpredatormenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

int ribi::SimPredatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::SimPredatorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SimPredator",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GameSimPredator.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::SimPredatorMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::SimPredatorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramSimPredator
  };
  assert(p);
  return p;
}

const std::string ribi::SimPredatorMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::SimPredatorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-07-13: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}
