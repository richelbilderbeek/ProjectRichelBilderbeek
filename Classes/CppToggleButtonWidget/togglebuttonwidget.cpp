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
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "togglebuttonwidget.h"

#include <cassert>
//#include <cmath>

#include <boost/math/constants/constants.hpp>

#include "drawcanvas.h"
#include "textcanvas.h"
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

std::string ribi::ToggleButtonWidget::GetVersion() noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::ToggleButtonWidget::GetVersionHistory() noexcept
{
  return {
    "2011-07-03: version 1.0: initial version",
    "2011-08-20: Version 1.1: added operator<<",
    "2011-08-31: Version 1.2: added setting the color of a ToggleButton",
    "2014-01-21: Version 1.3: added ToDrawCanvas",
    "2014-03-28: Version 1.4: replaced custom Rect class by Boost.Geometry"
  };
}

const boost::shared_ptr<ribi::DrawCanvas> ribi::ToggleButtonWidget::ToDrawCanvas(
  const int width_in, const int height_in) const noexcept
{
  boost::shared_ptr<DrawCanvas> canvas {
    new DrawCanvas(width_in,height_in,CanvasColorSystem::invert)
  };
  //Pressed
  //
  //
  //
  //
  //
  //
  //
  //         ```.  -.```
  // `.-:-:.`-``.  -.``-`.:-:-.`
  ///M:.                     .:M/
  //oM:.                     .:Mo <- y1 = y2 - 2.0
  //`---::---`.``. .``.`---::--:-
  //`h:.    ` ```. .``` `    .:d- <- y2 = 5/6
  //  .-:-:-`-``. . .``-`-:-:-.
  //       ` ```. . .``` `



  //Toggled:

  //         ```.  -.```
  // `.-:-:.`-``.  -.``-`.:-:-.`
  ///M:.                     .:M/  <- y1 = 1/6
  //oM:.                     .:Mo
  //.---::---`.``. .``.`---::---.
  //..      ` ```. .``` `      ..
  //..                         ..
  //..                         ..
  //..                         ..
  //..                         ..
  //`.                         --
  //`h:.                     .:d- <- y2 = 5/6
  //  .-:-:-`-``. . .``-`-:-:-.
  //       ` ```. . .``` `

  const double left = 1.0;
  const double top  = 1.0;
  const double right  = static_cast<double>(width_in ) - 2.0;
  const double bottom = static_cast<double>(height_in) - 2.0;
  const double height = bottom - top;
  const double height_1_6 = height / 6.0;
  const double y2 = top + (height * 5.0 / 6.0);
  const double y1 = GetToggleButton()->IsPressed() ? y2 - 2.0 : top + (height * 1.0 / 6.0);

  const double pi = boost::math::constants::pi<double>();
  //Below
  canvas->DrawArc(
    left,
    y2 - height_1_6,
    right,
    y2 + height_1_6,
    0.5 * pi * boost::units::si::radian,
    1.0 * pi * boost::units::si::radian
  );
  //Draw top
  canvas->DrawEllipse(
    left,
    y1 - height_1_6,
    right,
    y1 + height_1_6
  );
  canvas->DrawLine(
    left,
    y1,
    left,
    y2
  );
  canvas->DrawLine(
    right,
    y1,
    right,
    y2
  );
  return canvas;
}

const boost::shared_ptr<ribi::TextCanvas> ribi::ToggleButtonWidget::ToTextCanvas(
  const int width, const int height
) const noexcept
{
  const boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(width,height)
  };
  assert(width  == 6 && "For now");
  assert(height == 4 && "For now");


  if (GetToggleButton()->IsPressed())
  {
    canvas->PutText(0,0," ____ ");
    canvas->PutText(0,1,"|    |");
    canvas->PutText(0,2,"|____|");
  }
  else
  {
    canvas->PutText(0,0," ____ ");
    canvas->PutText(0,1,"|    |");
    canvas->PutText(0,2,"|____|");
    canvas->PutText(0,3,"|____|");
  }
  return canvas;
}


std::ostream& ribi::operator<<(std::ostream& os, const ToggleButtonWidget& button)
{
  os
    << "<ToggleButtonWidget>"
    << *button.m_button
    //<< button.GetGeometry()
    << "</ToggleButtonWidget>";
  return os;
}


