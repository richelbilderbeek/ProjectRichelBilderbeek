#include "reversimenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

int ribi::ReversiMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::ReversiMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Reversi",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GameReversi.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::ReversiMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::ReversiMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramReversi
  };
  assert(p);
  return p;
}

const std::string ribi::ReversiMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::ReversiMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07-13: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}
