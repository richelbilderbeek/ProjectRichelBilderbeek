//---------------------------------------------------------------------------
/*
TestToggleButton, tool to test the ToggleButton class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestToggleButton.htm
//---------------------------------------------------------------------------
#include "testtogglebuttonmenudialog.h"

#include <cassert>
#include <iostream>

#include "drawcanvas.h"
#include "richelbilderbeekprogram.h"
#include "textcanvas.h"
#include "togglebutton.h"
#include "testtimer.h"
#include "togglebuttonwidget.h"
#include "trace.h"

int ribi::TestToggleButtonMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

  const boost::shared_ptr<ToggleButtonWidget> widget(
    new ToggleButtonWidget
  );

  widget->GetToggleButton()->Press();

  std::cout
    << "Pressed\n"
    << '\n'
    << (*widget->ToDrawCanvas(30,15)) << std::endl;

  widget->GetToggleButton()->Toggle();

  std::cout
    << '\n'
    << "Toggled:\n"
    << '\n'
    << (*widget->ToDrawCanvas(30,15)) << std::endl;
  return 0;
}


ribi::About ribi::TestToggleButtonMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestToggleButton",
    "tool to test the ToggleButton class",
    "the 21st of January 2014",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestToggleButton.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("DrawCanvas version: " + DrawCanvas::GetVersion());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  a.AddLibrary("ToggleButton version: " + ToggleButton::GetVersion());
  a.AddLibrary("ToggleButtonWidget version: " + ToggleButtonWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}

ribi::Help ribi::TestToggleButtonMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestToggleButtonMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestToggleButton
  };
  assert(p);
  return p;
}

std::string ribi::TestToggleButtonMenuDialog::GetVersion() const noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::TestToggleButtonMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-06-16: Version 1.0: initial version, desktop version not yet working",
    "2011-06-31: Version 1.1: added more tests and an image to the Welcome screen in website version",
    "2012-06-21: Version 1.2: added desktop version",
    "2013-11-05: version 1.3: conformized for ProjectRichelBilderbeekConsole",
    "2014-01-21: version 1.4: added displaying a toggle button as text"
  };
}

#ifndef NDEBUG
void ribi::TestToggleButtonMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
