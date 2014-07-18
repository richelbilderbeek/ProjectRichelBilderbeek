#include "aafmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "aaffighter.h"
#include "aaffighterfactory.h"
#include "richelbilderbeekprogram.h"
#include "textcanvas.h"
#include "trace.h"

int ribi::aaf::MenuDialog::ExecuteSpecific(const std::vector<std::string>& /*argv*/) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  /*
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  std::cout
    << this->GetAbout().GetFileTitle() << " cannot be run in console mode\n"
    << std::endl;
  */
  const boost::shared_ptr<Fighter> fighter {
    aaf::FighterFactory().Create(AminoAcid::glycine)
  };
  std::cout << (*fighter->ToTextCanvas()) << std::endl;
  return 0;
}

ribi::About ribi::aaf::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "AminoAcidFighter",
    "4 player SpaceWar clone with amino acids",
    "today",
    "200x-201x",
    "http://www.richelbilderbeek.nl/GameAminoAcidFighter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

ribi::Help ribi::aaf::MenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::aaf::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramAminoAcidFighter
  };
  assert(p);
  return p;
}

std::string ribi::aaf::MenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::aaf::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: Initial Qt version"
  };
}

#ifndef NDEBUG
void ribi::aaf::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::aaf::AminoAcidFighterMenuDialog::Test()");
  MenuDialog d;
  assert(d.Execute( { "AminoAcidFigher", "-a" } ) == 0);
  assert(d.Execute( { "AminoAcidFigher", "--about" } ) == 0);
  assert(d.Execute( { "AminoAcidFigher", "-h" } ) == 0);
  assert(d.Execute( { "AminoAcidFigher", "--help" } ) == 0);
  assert(d.Execute( { "AminoAcidFigher", "-l" } ) == 0);
  assert(d.Execute( { "AminoAcidFigher", "--licence" } ) == 0);
  assert(d.Execute( { "AminoAcidFigher", "-v" } ) == 0);
  assert(d.Execute( { "AminoAcidFigher", "--version" } ) == 0);
  TRACE("Finished ribi::aaf::AminoAcidFighterMenuDialog::Test()");
}
#endif
