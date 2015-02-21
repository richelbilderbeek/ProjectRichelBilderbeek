//---------------------------------------------------------------------------
/*
RubiksClockDialWidget, class for displaying a RubiksClockDial
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
//From http://www.richelbilderbeek.nl/CppRubiksClockDialWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "rubiksclockdialwidget.h"

#include <cassert>
#include <cmath>

#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include "dial.h"
#include "rubiksclockdial.h"

//#include "trace.h"

#pragma GCC diagnostic pop

ribi::ruco::ClockDialWidget::ClockDialWidget(
  const double position,
  const int x,
  const int y,
  const int width,
  const int height,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_dial(new ClockDial(position,x,y,width,height,red,green,blue))
{
  SetGeometry(x,y,width,height);
}

double ribi::ruco::ClockDialWidget::GetDistance(const double dX, const double dY)
{
  return std::sqrt( (dX * dX) + (dY * dY) );
}

std::string ribi::ruco::ClockDialWidget::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::ruco::ClockDialWidget::GetVersionHistory() noexcept
{
  return {
    "2011-09-08: Version 1.0: initial version, called 'RubiksClockDialWidget'",
    "2014-01-23: Version 1.1: renamed to 'ClockDialWidget'",
    "2014-03-28: version 1.2: replaced Rect by Boost.Geometry its box class"
  };
}

bool ribi::ruco::ClockDialWidget::IsClicked(const int x, const int y) const
{
  const double widget_midx
    = boost::numeric_cast<double>(GetLeft())
    + (boost::numeric_cast<double>(GetWidth()) / 2.0);
  const double widget_midy
    = boost::numeric_cast<double>(GetTop())
    + (boost::numeric_cast<double>(GetHeight()) / 2.0);
  const double x_d = boost::numeric_cast<double>(x);
  const double y_d = boost::numeric_cast<double>(y);
  return GetDistance(x_d - widget_midx, y_d - widget_midy)
    < (boost::numeric_cast<double>(GetWidth()) / 2.0);
}

std::ostream& ribi::ruco::operator<<(std::ostream& os, const ribi::ruco::ClockDialWidget& widget)
{
  os
    << "<RubiksClockDialWidget>"
    << *widget.m_dial
    //<< widget.GetGeometry()
    << "</RubiksClockDialWidget>";
  return os;
}
