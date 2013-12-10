#include "pokevolleymenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "trace.h"

int ribi::PokeVolleyMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::PokeVolleyMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PokeVolley",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GamePokeVolley.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::PokeVolleyMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::PokeVolleyMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPokeVolley
  };
  assert(p);
  return p;
}

const std::string ribi::PokeVolleyMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::PokeVolleyMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}
