//---------------------------------------------------------------------------
/*
SimMysteryMachine, simulator of my mystery machine
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
//From http://www.richelbilderbeek.nl/ToolSimMysteryMachine.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "simmysterymachinemenudialog.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "dial.h"
#include "dialwidget.h"
#include "led.h"
#include "ledwidget.h"
#include "testtimer.h"
#include "mysterymachine.h"
#include "mysterymachinewidget.h"
#include "richelbilderbeekprogram.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"
#include "widget.h"
#pragma GCC diagnostic pop

int ribi::SimMysteryMachineMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::SimMysteryMachineMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SimMysteryMachine",
    "simulator of my mystery machine",
    "the 26th of August 2012",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolSimMysteryMachine.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Dial version: " + Dial::GetVersion());
  a.AddLibrary("DialWidget version: " + DialWidget::GetVersion());
  a.AddLibrary("Led version: " + Led::GetVersion());
  a.AddLibrary("LedWidget version: " + LedWidget::GetVersion());
  a.AddLibrary("ToggleButton version: " + ToggleButton::GetVersion());
  a.AddLibrary("ToggleButtonWidget version: " + ToggleButtonWidget::GetVersion());
  a.AddLibrary("MysteryMachine version: " + MysteryMachine::GetVersion());
  a.AddLibrary("MysteryMachineWidget version: " + MysteryMachineWidget::GetVersion());
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}

ribi::Help ribi::SimMysteryMachineMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::SimMysteryMachineMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramSimMysteryMachine
  };
  assert(p);
  return p;
}

std::string ribi::SimMysteryMachineMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::SimMysteryMachineMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-04-10: Version 1.0: initial version (web application version not working yet)",
    "2011-09-15: Version 1.1: working web application, added picture of a physical prototype of a MysteryMachine",
    "2012-08-26: Version 1.2: added picture of a physical MysteryMachine, improved aesthetics"
  };
}

#ifndef NDEBUG
void ribi::SimMysteryMachineMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
