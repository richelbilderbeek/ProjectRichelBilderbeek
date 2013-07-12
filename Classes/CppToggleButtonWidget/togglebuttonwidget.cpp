
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

//From http://www.richelbilderbeek.nl/CppToggleButtonWidget.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "togglebuttonwidget.h"

#include <cassert>
#include <cmath>

//Terrible #define, but my crosscompiler cannot find the definition of M_PI in cmath.h :-(
#ifndef M_PI
# define M_PI		3.14159265358979323846	/* pi */
#endif

#include "togglebutton.h"
#include "trace.h"

#pragma GCC diagnostic pop

ToggleButtonWidget::ToggleButtonWidget(
  const bool pressed,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_button(new ToggleButton(pressed,red,green,blue))
{

}

void ToggleButtonWidget::Click(const int, const int)
{
  m_button->Toggle();
}

const std::string ToggleButtonWidget::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> ToggleButtonWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-07-03: version 1.0: initial version");
  v.push_back("2011-08-20: Version 1.1: added operator<<");
  v.push_back("2011-08-31: Version 1.2: added setting the color of a ToggleButton");
  return v;
}

std::ostream& operator<<(std::ostream& os, const ToggleButtonWidget& button)
{
  os
    << "<ToggleButtonWidget>"
    << *button.m_button
    << button.GetGeometry()
    << "</ToggleButtonWidget>";
  return os;
}


