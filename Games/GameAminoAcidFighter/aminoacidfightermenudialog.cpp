#include "aminoacidfightermenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "trace.h"

int ribi::AminoAcidFighterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::AminoAcidFighterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "AminoAcidFighter",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GameAminoAcidFighter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::AminoAcidFighterMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::AminoAcidFighterMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramAminoAcidFighter
  };
  assert(p);
  return p;
}

const std::string ribi::AminoAcidFighterMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::AminoAcidFighterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: Initial Qt version"
  };
}

#ifndef NDEBUG
void ribi::AminoAcidFighterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::AminoAcidFighterMenuDialog::Test()");
  TRACE("Finished ribi::AminoAcidFighterMenuDialog::Test()");
}
#endif
