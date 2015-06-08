#include "testqtroundededitrectitemmenudialog.h"

#include <cassert>
#include <iostream>

#include "container.h"
#include "fileio.h"
#include "plane.h"
#include "testtimer.h"
#include "ribi_regex.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"

int ribi::TestQtRoundedEditRectItemMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestQtRoundedEditRectItemMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestQtRoundedEditRectItemWidget",
    "tests QtRoundedEditRectItemWidget",
    "the 9th of August 2014",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ToolTestQtRoundedEditRectItemWidget.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
  a.AddLibrary("ribi::Regex version: " + Regex::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestQtRoundedEditRectItemMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestQtRoundedEditRectItemMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQtRoundedEditRectItem
  };
  assert(p);
  return p;
}

std::string ribi::TestQtRoundedEditRectItemMenuDialog::GetVersion() const noexcept
{
  return "1.6";
}

std::vector<std::string> ribi::TestQtRoundedEditRectItemMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-12-21: version 1.0: initial version",
    "2012-12-31: version 1.1: added menu",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole",
    "2014-06-15: version 1.3: added Modify dialog in desktop version",
    "2014-06-23: version 1.4: use of QtRoundedEditRectItemDialog",
    "2014-08-07: version 1.5: increased use of TDD",
    "2014-08-09: version 1.6: some bugfixes in the classes used"

  };
}

#ifndef NDEBUG
void ribi::TestQtRoundedEditRectItemMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Container();
    fileio::FileIo();
    const boost::shared_ptr<Plane> p{
      new Plane(
        Plane::Coordinat3D(1.0,0.0,0.0),
        Plane::Coordinat3D(0.0,1.0,0.0),
        Plane::Coordinat3D(0.0,0.0,1.0)
      )
    };
    ::ribi::Regex();
  }

  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
