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
#ifndef TESTTEXTPOSITIONWIDGETMENUDIALOG_H
#define TESTTEXTPOSITIONWIDGETMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

///GUI independent TestTextPositionWidget menu dialog
struct TestTextPositionWidgetMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // TESTTEXTPOSITIONWIDGETMENUDIALOG_H
