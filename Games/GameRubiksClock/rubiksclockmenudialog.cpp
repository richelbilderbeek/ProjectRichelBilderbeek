//---------------------------------------------------------------------------
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameRubiksClock.htm
//---------------------------------------------------------------------------
#include "rubiksclockmenudialog.h"

#include <cassert>
#include <iostream>

#include "about.h"
#include "dial.h"
#include "dialwidget.h"
#include "drawcanvas.h"
#include "rectangle.h"
#include "rubiksclock.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "rubiksclockwidget.h"
#include "textcanvas.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"

int ribi::RubiksClockMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

  const boost::shared_ptr<RubiksClockWidget> widget(
    new RubiksClockWidget
  );
  std::cout << (*widget->ToDrawCanvas(20)) << std::endl;
  std::cout << (*widget->ToTextCanvas(20)) << std::endl;
  return 0;
}

const ribi::About ribi::RubiksClockMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "RubiksClock",
    "simulates a Rubik's Clock",
    "the 23rd of December 2012",
    "2007-2014",
    "http://www.richelbilderbeek.nl/GameRubiksClock.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Dial version: " + Dial::GetVersion());
  a.AddLibrary("DialWidget version: " + DialWidget::GetVersion());
  a.AddLibrary("Rectangle version: " + Rect::GetVersion());
  a.AddLibrary("RubiksClock version: " + RubiksClock::GetVersion());
  a.AddLibrary("RubiksClockDial version: " + RubiksClockDial::GetVersion());
  a.AddLibrary("RubiksClockDialWidget version: " + RubiksClockDialWidget::GetVersion());
  a.AddLibrary("RubiksClockWidget version: " + RubiksClockWidget::GetVersion());
  a.AddLibrary("ToggleButton version: " + ToggleButton::GetVersion());
  a.AddLibrary("ToggleButtonWidget version: " + ToggleButtonWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}

const ribi::Help ribi::RubiksClockMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::RubiksClockMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramRubiksClock
  };
  assert(p);
  return p;
}

const std::string ribi::RubiksClockMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

const std::vector<std::string> ribi::RubiksClockMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-12-19: Version 1.0: initial Windows-only version using C++ Builder",
    "2011-09-08: Version 2.0: initial port to Qt using Qt Creator, but not complete yet",
    "2011-09-15: Version 2.1: created web application version, RubiksClock has all functionality",
    "2012-12-23: Version 2.2: created desktop version"
  };
}

#ifndef NDEBUG
void ribi::RubiksClockMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::RubiksClockMenuDialog::Test");
  {
    const boost::shared_ptr<Dial> p(
      new Dial
    );
    assert(p);
  }
  {
    const boost::shared_ptr<DialWidget> p(
      new DialWidget
    );
    assert(p);
  }
  Rect();
  RubiksClock();
  {
    const boost::shared_ptr<RubiksClockDial> p(
      new RubiksClockDial(0,0,0,1,1,0,0,0)
    );
    assert(p);
  }
  {
    const boost::shared_ptr<RubiksClockDialWidget> p(
      new RubiksClockDialWidget(0.0,0,0,1,1,0,0,0)
    );
    assert(p);
  }
  {
    const boost::shared_ptr<RubiksClockWidget> p(
      new RubiksClockWidget
    );
    assert(p);
  }
  {
    const boost::shared_ptr<ToggleButton> p(
      new ToggleButton
    );
    assert(p);
  }
  ToggleButtonWidget();
  {
    const boost::shared_ptr<Widget> p(
      new Widget
    );
    assert(p);
  }

  TRACE("Finished ribi::RubiksClockMenuDialog::Test successfully");
}
#endif
