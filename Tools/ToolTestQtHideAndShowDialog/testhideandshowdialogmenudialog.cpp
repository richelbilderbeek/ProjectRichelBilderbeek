#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testhideandshowdialogmenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "fileio.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestHideAndShowDialogMenuDialog::TestHideAndShowDialogMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestHideAndShowDialogMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::TestHideAndShowDialogMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestHideAndShowDialog",
    "tests the TestHideAndShowDialog class",
    "the 30th of June 2014",
    "2014",
    "http://www.richelbilderbeek.nl/ToolTestHideAndShowDialog.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  return a;
}

ribi::Help ribi::TestHideAndShowDialogMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestHideAndShowDialogMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestQtHideAndShowDialog
  };
  assert(p);
  return p;
}

std::string ribi::TestHideAndShowDialogMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::TestHideAndShowDialogMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-xx-xx: version 1.0: initial version",
    "2014-05-09: version 1.1: started versioning"
    "2014-06-30: version 1.2: fixed desktop version"
  };
}

#ifndef NDEBUG
void ribi::TestHideAndShowDialogMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
