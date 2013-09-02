//---------------------------------------------------------------------------
/*
LedWidget, Widget for the Led class
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
//From http://www.richelbilderbeek.nl/CppLedWidget.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "ledwidget.h"
#pragma GCC diagnostic pop

#include <iostream>

#include "led.h"

LedWidget::LedWidget(
  const int x,
  const int y,
  const int width,
  const int height,
  const double intensity,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_led(new Led(intensity,red,green,blue))
{
  this->SetGeometry(Rect(x,y,width,height));
}

const std::string LedWidget::GetVersion()
{
  return "1.3";
}

const std::vector<std::string> LedWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-07-03: version 1.0: initial version");
  v.push_back("2011-08-17: Version 1.1: emit a signal when the color is changed");
  v.push_back("2011-08-20: Version 1.2: added operator<<");
  v.push_back("2011-09-08: Version 1.3: removed redundant signals");
  return v;
}

std::ostream& operator<<(std::ostream& os, const LedWidget& widget)
{
  os
    << "<LedWidget>"
    << widget.GetGeometry()
    << *widget.m_led
    << "</LedWidget>";
  return os;
}

