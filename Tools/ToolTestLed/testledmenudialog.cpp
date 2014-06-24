//---------------------------------------------------------------------------
/*
TestLed, tool to test the Led class
Copyright (C) 2011-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestLed.htm
//---------------------------------------------------------------------------
#include "testledmenudialog.h"

#include <cassert>
#include <iostream>

#include "led.h"
#include "ledwidget.h"
#include "richelbilderbeekprogram.h"
#include "textcanvas.h"
#include "trace.h"

int ribi::TestLedMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  const int x = 0;
  const int y = 0;
  const int w = 20;
  const int h = 20;
  const double intensity = 0.5;
  const boost::shared_ptr<LedWidget> widget(
    new LedWidget(x,y,w,h,intensity)
  );

  std::cout << (*widget->ToCanvas(10)) << std::endl;
  return 0;
}

ribi::About ribi::TestLedMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestLed",
    "tool to test the Led class",
    "the 5th of November 2013",
    "2011-2014",
    "http://www.richelbilderbeek.nl/ToolTestLed.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("Led version: " + Led::GetVersion());
  a.AddLibrary("LedWidget version: " + LedWidget::GetVersion());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  return a;
}

ribi::Help ribi::TestLedMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestLedMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestLed
  };
  assert(p);
  return p;
}

std::string ribi::TestLedMenuDialog::GetVersion() const noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::TestLedMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-04-10: Version 1.0: initial version, web version not yet working",
    "2011-04-11: Version 1.1: got web version to work, added more About info",
    "2011-07-02: Version 1.2: added menu",
    "2011-09-08: Version 1.3: added Welcome screen picture and increased testing in website version",
    "2013-11-05: version 1.4: conformized for ProjectRichelBilderbeekConsole",
    "2014-06-05: version 1.4: conformized for ProjectRichelBilderbeekConsole"
  };
}


#ifndef NDEBUG
void ribi::TestLedMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestLedMenuDialog::Test");
  TRACE("Finished ribi::TestLedMenuDialog::Test successfully");
}
#endif
