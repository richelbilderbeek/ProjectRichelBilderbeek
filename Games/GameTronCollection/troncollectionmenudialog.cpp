#include "troncollectionmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

int ribi::TronCollectionMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::TronCollectionMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TronCollection",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GameTronCollection.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::TronCollectionMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::TronCollectionMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramTronCollection
  };
  assert(p);
  return p;
}

const std::string ribi::TronCollectionMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::TronCollectionMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}
