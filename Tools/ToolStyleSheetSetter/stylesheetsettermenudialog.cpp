#include "stylesheetsettermenudialog.h"

#include <cassert>
#include <iostream>

int ribi::StyleSheetSetterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::StyleSheetSetterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "StyleSheetSetter",
    "",
    "the 29th of November 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolStyleSheetSetter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

const ribi::Help ribi::StyleSheetSetterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::StyleSheetSetterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramGaborFilter
  };
  assert(p);
  return p;
}

const std::string ribi::StyleSheetSetterMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::StyleSheetSetterMenuDialog::GetVersionHistory() const noexcept
{
  return {
   "2013-01-09: version 0.1: initial version with a main dialog only",
   "2013-11-29: version 1.0: conformized to ProjectRichelBilderbeek"
  };
}
