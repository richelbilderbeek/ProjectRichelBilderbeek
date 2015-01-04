//---------------------------------------------------------------------------
/*
DialWidget, class for displaying a Dial
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
//From http://www.richelbilderbeek.nl/CppDialWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "dialwidget.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include "dial.h"
#include "drawcanvas.h"
#include "geometry.h"
#include "testtimer.h"
#include "trace.h"
#include "textcanvas.h"

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
  this->SetGeometry(Geometry().CreateRect(x,y,width,height));
}

void ribi::DialWidget::Click(const int x,const int y) noexcept
{
  if (!IsClicked(x,y)) return;
  const Geometry h; //Helper
  const auto g(GetGeometry());
  const int midx = h.GetLeft(g) + (h.GetWidth( g) / 2);
  const int midy = h.GetTop( g) + (h.GetHeight(g) / 2);
  const double dx = boost::numeric_cast<double>(x - midx);
  const double dy = boost::numeric_cast<double>(y - midy);
  const double angle = Geometry().GetAngleClockScreen(dx,dy);
  const double pi = boost::math::constants::pi<double>();
  const double position = angle / (2.0 * pi);
  assert(position >= 0.0);
  assert(position <= 1.0);
  m_dial->SetPosition(position);
}

std::string ribi::DialWidget::GetVersion() noexcept
{
  return "2.5";
}

std::vector<std::string> ribi::DialWidget::GetVersionHistory() noexcept
{
  return {
    "2011-07-03: Version 1.0: initial version",
    "2011-08-07: Version 2.0: conformized architure for MysteryMachine",
    "2011-08-20: Version 2.1: added operator<<",
    "2011-08-31: Version 2.2: allow changing the dial its color",
    "2011-09-08: Version 2.3: check for clicking on the dial, instead of its rectangle",
    "2013-04-30: Version 2.4: added testing, fixed bug in GetAngle",
    "2014-03-28: Version 2.5: replaced custom Rect class by Boost.Geometry",
  };
}

bool ribi::DialWidget::IsClicked(const int x, const int y) const noexcept
{
  const Geometry h; //Helper
  const auto g(GetGeometry());
  const double widget_midx
    = boost::numeric_cast<double>(GetLeft())
    + (boost::numeric_cast<double>(h.GetWidth(g)) / 2.0);
  const double widget_midy
    = boost::numeric_cast<double>(h.GetTop(g))
    + (boost::numeric_cast<double>(h.GetHeight(g)) / 2.0);
  const double x_d = boost::numeric_cast<double>(x);
  const double y_d = boost::numeric_cast<double>(y);
  return Geometry().GetDistance(x_d - widget_midx, y_d - widget_midy)
    < (boost::numeric_cast<double>(h.GetWidth(g)) / 2.0);
}

void ribi::DialWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    DrawCanvas();
    TextCanvas();
    Geometry();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const boost::shared_ptr<DialWidget> w(new DialWidget);
    assert(w->GetDial());
    for (double position = 0.0; position < 1.0; position += 0.0625)
    {
      w->GetDial()->SetPosition(position);
      std::stringstream s;
      s << '\n' << (*w->ToTextCanvas(4));
      assert(!s.str().empty());

      s << '\n' << (*w->ToDrawCanvas(4));
      assert(!s.str().empty());
      //TRACE(s.str());
    }
  }
}

const boost::shared_ptr<ribi::DrawCanvas> ribi::DialWidget::ToDrawCanvas(const int radius) const noexcept
{
  assert(radius > 1);
  boost::shared_ptr<ribi::DrawCanvas> canvas(
    new DrawCanvas(1+(radius*2),1+(radius*2))
  );
  const double pi = boost::math::constants::pi<double>();

  //Circle
  {
    const double midx = static_cast<double>(radius);
    const double midy = static_cast<double>(radius);
    const double ray = static_cast<double>(radius);
    canvas->DrawCircle(midx,midy,ray);
  }
  //Pointer
  {
    const double midx = static_cast<double>(radius);
    const double midy = static_cast<double>(radius);
    const double angle = GetDial()->GetPosition() * 2.0 * pi;
    const double ray = static_cast<double>(radius);
    const double x = midx + (std::sin(angle) * ray);
    const double y = midy - (std::cos(angle) * ray);
    canvas->DrawLine(midx,midy,x,y);
  }
  return canvas;
}

const boost::shared_ptr<ribi::TextCanvas> ribi::DialWidget::ToTextCanvas(const int radius) const noexcept
{
  assert(radius > 1);
  boost::shared_ptr<ribi::TextCanvas> canvas(
    new TextCanvas(1+(radius*2),1+(radius*2))
  );
  const double pi = boost::math::constants::pi<double>();

  //Circle
  {
    const int n_steps = std::ceil(2.0 * pi * static_cast<double>(radius));
    for (int i=0; i!=n_steps; ++i)
    {
      const double f = static_cast<double>(i) / static_cast<double>(n_steps);
      const double angle = f * 2.0 * pi;
      const double midx = static_cast<double>(radius);
      const double midy = static_cast<double>(radius);
      const double ray = static_cast<double>(radius);
      const int x = static_cast<int>(std::round(midx + (std::sin(angle) * ray)));
      const int y = static_cast<int>(std::round(midy - (std::cos(angle) * ray)));
      canvas->PutChar(x,y,'*');
    }
  }
  //Pointer
  {
    char c = ' ';
    // modulo 8 as module 16 would result in a switch statement with case 0+x == case 8+x
    const int quadrant = (static_cast<int>(GetDial()->GetPosition() * 16.0) % 16) % 8;

    switch (quadrant)
    {
      case  0: c = '|'; break;
      case  1: c = '/'; break;
      case  2: c = '/'; break;
      case  3: c = '-'; break;
      case  4: c = '-'; break;
      case  5: c = '\\'; break;
      case  6: c = '\\'; break;
      case  7: c = '|'; break;
      default: assert(!"Should not get here");
    }

    const int n_steps = radius;
    for (int i=0; i!=n_steps; ++i)
    {
      const double angle = GetDial()->GetPosition() * 2.0 * pi;
      assert(angle >= 0.0 * pi);
      assert(angle <= 2.0 * pi);
      const double midx = static_cast<double>(radius);
      const double midy = static_cast<double>(radius);
      const double ray = static_cast<double>(i);
      const int x = static_cast<int>(std::round(midx + (std::sin(angle) * ray)));
      const int y = static_cast<int>(std::round(midy - (std::cos(angle) * ray)));
      canvas->PutChar(x,y,c);
    }

  }
  return canvas;
}

std::ostream& ribi::operator<<(std::ostream& os, const DialWidget& widget) noexcept
{
  os
    << "<DialWidget>"
    << *widget.m_dial
    //<< widget.GetGeometry()
    << "</DialWidget>"
  ;
  return os;
}


