//---------------------------------------------------------------------------
/*
TestTextPositionWidget, solver of quadratic equations
Copyright (C) 2008-2014 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolTestTextPositionWidget.htm
//---------------------------------------------------------------------------
#include "testtextpositionwidgetmenudialog.h"

#include "trace.h"

const ribi::About ribi::TestTextPositionWidgetMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestTextPositionWidget",
    "tool to test the TicTacToe class",
    "the 15th of Oktober 2013",
    "2011-2013",
    "http://www.richelbilderbeek.nl/ToolTestTextPositionWidget.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::TestTextPositionWidgetMenuDialog::GetVersion()
{
  return "1.4";
}

const std::vector<std::string> ribi::TestTextPositionWidgetMenuDialog::GetVersionHistory()
{
  return {
    "2010-09-17: version 1.0: initial version, use of QTable as board",
    "2010-09-22: version 1.1: use of TicTacToeWidget",
    "2011-01-06: version 1.2: merge with Wt application",
    "2011-01-06: version 1.3: moved TicTacToe and QtTicTacToeWidget to different folders",
    "2013-10-14: version 1.4: conformized to ProjectRichelBilderbeek"
  };
}
