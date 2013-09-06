//---------------------------------------------------------------------------
/*
Widget, GUI independent widget class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWidget.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "widget.h"
#pragma GCC diagnostic pop

const std::string ribi::Widget::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::Widget::GetVersionHistory()
{
  return {
    "2011-07-03: version 1.0: initial version",
    "2011-08-07: version 1.1: added signal that is emitted when geometry changes"
  };
}

void ribi::Widget::SetGeometry(const Rect& geometry)
{
  if (geometry != m_geometry)
  {
    m_geometry = geometry;
    m_signal_geometry_changed();
  }
}

