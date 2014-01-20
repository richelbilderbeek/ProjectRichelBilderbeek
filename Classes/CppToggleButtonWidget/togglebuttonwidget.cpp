//---------------------------------------------------------------------------
/*
ToggleButtonWidget, widget for the ToggleButton class
Copyright (C) 2011-2014 Richel Bilderbeek

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

#include <boost/math/constants/constants.hpp>

#include "drawcanvas.h"
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

const std::string ribi::ToggleButtonWidget::GetVersion() noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::ToggleButtonWidget::GetVersionHistory() noexcept
{
  return {
    "2011-07-03: version 1.0: initial version",
    "2011-08-20: Version 1.1: added operator<<",
    "2011-08-31: Version 1.2: added setting the color of a ToggleButton"
  };
}

const boost::shared_ptr<ribi::DrawCanvas> ribi::ToggleButtonWidget::ToDrawCanvas(
  const int width, const int height) const noexcept
{
  boost::shared_ptr<DrawCanvas> canvas {
    new DrawCanvas(width,height,CanvasColorSystem::invert)
  };
  const int maxx = width  - 2;
  const int maxy = height - 2;
  const int left = 1;
  const int top  = 1;
  const double pi = boost::math::constants::pi<double>();
  //Below
  canvas->DrawArc(
    left + 0,
    top + (maxy * 1 / 3),
    maxx,
    maxy * 2 / 3,
     0.5 * pi * boost::units::si::radian,
    -1.0 * pi * boost::units::si::radian
  );
  //Draw top
  canvas->DrawEllipse(
    left + 0,
    top + (GetToggleButton()->IsPressed() ? (maxy * 1 / 3) - 2 : 0.0),
    maxx,
    maxy * 2 / 3
  );
  canvas->DrawLine(
    left,
    top + (GetToggleButton()->IsPressed() ? (maxy * 2 / 3) - 2 : (maxy * 1 / 3)),
    left,
    top + (maxy * 2 / 3)
  );
  canvas->DrawLine(
    left + maxx,
    top + (GetToggleButton()->IsPressed() ? (maxy * 2 / 3) - 2 : (maxy * 1 / 3)),
    left + maxx,
    top + (maxy * 2 / 3)
  );
  return canvas;
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


