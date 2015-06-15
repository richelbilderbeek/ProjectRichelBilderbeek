//---------------------------------------------------------------------------
/*
StateObserver, tool to examine state observers
Copyright (C) 2013-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolStateObserver.htm
//---------------------------------------------------------------------------
#include "stateobservermenudialog.h"

#include <cassert>
#include <iostream>

#include "alphabetafilter.h"
#include "alphabetagammafilter.h"
#include "alphafilter.h"
#include "integeralphafilter.h"
#include "integerstateobserver.h"
#include "integersymmetricalphafilter.h"
#include "multialphafilter.h"
#include "multiintegerstateobserver.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::StateObserverMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::StateObserverMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "StateObserver",
    "tool to examine state observers",
    "the 12th of July 2013",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolStateObserver.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("AlphaFilter version: " + AlphaFilter::GetVersion());
  a.AddLibrary("AlphaBetaFilter version: " + AlphaBetaFilter::GetVersion());
  a.AddLibrary("AlphaBetaGammaFilter version: " + AlphaBetaGammaFilter::GetVersion());
  a.AddLibrary("IntegerAlphaFilter version: " + IntegerAlphaFilter::GetVersion());
  a.AddLibrary("IntegerStateObserver version: " + IntegerStateObserver::GetVersion());
  a.AddLibrary("IntegerSymmetricalAlphaFilter version: " + IntegerSymmetricalAlphaFilter::GetVersion());
  a.AddLibrary("MultiAlphaFilter version: " + MultiAlphaFilter::GetVersion());
  a.AddLibrary("MultiIntegerStateObserver version: " + MultiIntegerStateObserver::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::StateObserverMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::StateObserverMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramStateObserver
  };
  assert(p);
  return p;
}

std::string ribi::StateObserverMenuDialog::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::StateObserverMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-05-25: version 1.0: initial version",
    "2013-06-04: version 1.1: added more state observers, allow plotting of subset of state observers",
    "2013-06-17: version 1.1: improved menu screen",
    "2013-07-12: version 1.2: transitioned to Qt5 and Boost 1.54.0",
    "2013-11-05: version 1.3: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::StateObserverMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
