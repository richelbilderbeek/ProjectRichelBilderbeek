#include "testqtroundedrectitemmenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"

int ribi::TestQtRoundedRectItemMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestQtRoundedRectItemMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestQtRoundedRectItem",
    "tests QtRoundedRectItemt",
    "the 10th of June 2014",
    "2012-2014",
    "http://www.richelbilderbeek.nl/ToolTestQtRoundedRectItem.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestQtRoundedRectItemMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestQtRoundedRectItemMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQtRoundedRectItem
  };
  assert(p);
  return p;
}

std::string ribi::TestQtRoundedRectItemMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::TestQtRoundedRectItemMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-12-21: version 1.0: initial version",
    "2012-05-20: version 1.1: added menu",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole",
    "2014-06-10: version 1.3: use QtKeyboardFriendlyGraphicView in desktop version"
  };
}

#ifndef NDEBUG
void ribi::TestQtRoundedRectItemMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestQtRoundedRectItemMenuDialog::Test");
  TRACE("Finished ribi::TestQtRoundedRectItemMenuDialog::Test successfully");
}
#endif
