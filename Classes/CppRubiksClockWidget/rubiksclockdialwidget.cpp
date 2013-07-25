
/*
RubiksClockDialWidget, class for displaying a RubiksClockDial
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

//From http://www.richelbilderbeek.nl/CppRubiksClockDialWidget.htm

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
#include "rubiksclockdialwidget.h"

#include <cassert>
#include <cmath>

#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include "dial.h"
#include "rubiksclockdial.h"
#include "rectangle.h"
//#include "trace.h"

#pragma GCC diagnostic pop

RubiksClockDialWidget::RubiksClockDialWidget(
  const double position,
  const int x,
  const int y,
  const int width,
  const int height,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_dial(new RubiksClockDial(position,x,y,width,height,red,green,blue))
{
  this->SetGeometry(Rect(x,y,width,height));
}

double RubiksClockDialWidget::GetDistance(const double dX, const double dY)
{
  return std::sqrt( (dX * dX) + (dY * dY) );
}

const std::string RubiksClockDialWidget::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> RubiksClockDialWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-09-08: Version 1.0: initial version");
  return v;
}

bool RubiksClockDialWidget::IsClicked(const int x, const int y) const
{
  const double widget_midx
    = boost::numeric_cast<double>(GetGeometry().GetX())
    + (boost::numeric_cast<double>(this->GetGeometry().GetWidth()) / 2.0);
  const double widget_midy
    = boost::numeric_cast<double>(GetGeometry().GetY())
    + (boost::numeric_cast<double>(this->GetGeometry().GetHeight()) / 2.0);
  const double x_d = boost::numeric_cast<double>(x);
  const double y_d = boost::numeric_cast<double>(y);
  return GetDistance(x_d - widget_midx, y_d - widget_midy)
    < (boost::numeric_cast<double>(this->GetGeometry().GetWidth()) / 2.0);
}

std::ostream& operator<<(std::ostream& os, const RubiksClockDialWidget& widget)
{
  os
    << "<RubiksClockDialWidget>"
    << *widget.m_dial
    << widget.GetGeometry()
    << "</RubiksClockDialWidget>";
  return os;
}


