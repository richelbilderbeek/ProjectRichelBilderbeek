#include "testaboutmenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::TestAboutMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  return 0;
}

ribi::About ribi::TestAboutMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestAbout",
    "test the About classes",
    "the 12th of July 2013",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ToolTestAbout.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

ribi::Help ribi::TestAboutMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestAboutMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestAbout
  };
  assert(p);
  return p;
}

std::string ribi::TestAboutMenuDialog::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::TestAboutMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-01-25: Version 1.0: initial version in Qt4 and C++98",
    "2013-07-12: Version 1.1: transitioned to Qt5 and C++11"
    "2013-09-05: version 1.2: transition to namespace ribi"
    "2013-11-28: version 1.3: conformized to ProjectRichelBilderbeek"
  };
}

#ifndef NDEBUG
void ribi::TestAboutMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
