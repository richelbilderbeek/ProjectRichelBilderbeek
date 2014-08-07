#include "stylesheetsettermenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::StyleSheetSetterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::StyleSheetSetterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "StyleSheetSetter",
    "",
    "the 29th of November 2013",
    "2013-2014",
    "http://www.richelbilderbeek.nl/ToolStyleSheetSetter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

ribi::Help ribi::StyleSheetSetterMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::StyleSheetSetterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramStyleSheetSetter
  };
  assert(p);
  return p;
}

std::string ribi::StyleSheetSetterMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::StyleSheetSetterMenuDialog::GetVersionHistory() const noexcept
{
  return {
   "2013-01-09: version 0.1: initial version with a main dialog only",
   "2013-11-29: version 1.0: conformized to ProjectRichelBilderbeek"
  };
}

#ifndef NDEBUG
void ribi::StyleSheetSetterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
