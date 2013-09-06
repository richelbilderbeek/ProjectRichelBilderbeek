//---------------------------------------------------------------------------
/*
DialWidget, class for displaying a Dial
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
//From http://www.richelbilderbeek.nl/CppDialWidget.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "dialwidget.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include "dial.h"
#include "rectangle.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::DialWidget::DialWidget(
  const double position,
  const int x,
  const int y,
  const int width,
  const int height,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_dial(new Dial(position,red,green,blue))
{
  #ifndef NDEBUG
  Test();
  #endif
  this->SetGeometry(Rect(x,y,width,height));
}

void ribi::DialWidget::Click(const int x,const int y)
{
  if (!IsClicked(x,y)) return;
  const int midx = GetGeometry().GetX() + (GetGeometry().GetWidth()  / 2);
  const int midy = GetGeometry().GetY() + (GetGeometry().GetHeight() / 2);
  const double dx = boost::numeric_cast<double>(x - midx);
  const double dy = boost::numeric_cast<double>(y - midy);
  const double angle = Dial::GetAngle(dx,dy);
  const double pi = boost::math::constants::pi<double>();
  const double position = angle / (2.0 * pi);
  assert(position >= 0.0);
  assert(position <= 1.0);
  m_dial->SetPosition(position);
}

const std::string ribi::DialWidget::GetVersion()
{
  return "2.4";
}

const std::vector<std::string> ribi::DialWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-07-03: Version 1.0: initial version");
  v.push_back("2011-08-07: Version 2.0: conformized architure for MysteryMachine");
  v.push_back("2011-08-20: Version 2.1: added operator<<");
  v.push_back("2011-08-31: Version 2.2: allow changing the dial its color");
  v.push_back("2011-09-08: Version 2.3: check for clicking on the dial, instead of its rectangle");
  v.push_back("2013-04-30: Version 2.4: added testing, fixed bug in GetAngle");
  return v;
}

double ribi::DialWidget::GetAngle(const double dx, const double dy)
{
  return Dial::GetAngle(dx,dy);
}

double ribi::DialWidget::GetDistance(const double dx, const double dy)
{
  return Dial::GetDistance(dx,dy);
}

bool ribi::DialWidget::IsClicked(const int x, const int y) const
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

void ribi::DialWidget::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    boost::shared_ptr<Dial> dial(new Dial);
  }
}

std::ostream& ribi::operator<<(std::ostream& os, const DialWidget& widget)
{
  os
    << "<DialWidget>"
    << *widget.m_dial
    << widget.GetGeometry()
    << "</DialWidget>";
  return os;
}


