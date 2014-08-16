#include "xenonzeromenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "richelbilderbeekprogram.h"

int ribi::XeNonZeroMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::XeNonZeroMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "XeNonZero",
    "a simple game",
    "the 13th of July 2013",
    "2005-2014",
    "http://www.richelbilderbeek.nl/GameXeNonZero.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

ribi::Help ribi::XeNonZeroMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::XeNonZeroMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramXeNonZero
  };
  assert(p);
  return p;
}

std::string ribi::XeNonZeroMenuDialog::GetVersion() const noexcept
{
  return "0.1";
}

std::vector<std::string> ribi::XeNonZeroMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 0.1: conformized to ProjectRichelBilderbeekConsole"
  };
}
