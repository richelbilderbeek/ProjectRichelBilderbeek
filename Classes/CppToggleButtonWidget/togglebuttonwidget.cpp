//---------------------------------------------------------------------------
/*
ToggleButtonWidget, widget for the ToggleButton class
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
//From http://www.richelbilderbeek.nl/CppToggleButtonWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "togglebuttonwidget.h"

#include <cassert>
//#include <cmath>

//#include <boost/math/constants/constants.hpp>

#include "togglebutton.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::ToggleButtonWidget::ToggleButtonWidget(
  const bool pressed,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_button(new ToggleButton(pressed,red,green,blue))
{

}

void ribi::ToggleButtonWidget::Click(const int, const int)
{
  m_button->Toggle();
}

const std::string ribi::ToggleButtonWidget::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> ribi::ToggleButtonWidget::GetVersionHistory()
{
  return {
    "YYYY-MM-DD: version X.Y: [description]",
    "2011-07-03: version 1.0: initial version",
    "2011-08-20: Version 1.1: added operator<<",
    "2011-08-31: Version 1.2: added setting the color of a ToggleButton"
  };
}

std::ostream& ribi::operator<<(std::ostream& os, const ToggleButtonWidget& button)
{
  os
    << "<ToggleButtonWidget>"
    << *button.m_button
    << button.GetGeometry()
    << "</ToggleButtonWidget>";
  return os;
}


