//---------------------------------------------------------------------------
/*
ToggleButton, toggle button class
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
//From http://www.richelbilderbeek.nl/CppToggleButton.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "togglebutton.h"

#include <cassert>
//#include <cmath>

//#include <boost/math/constants/constants.hpp>

#include "trace.h"

#pragma GCC diagnostic pop

ribi::ToggleButton::ToggleButton(
  const bool pressed,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue) noexcept
  : m_signal_color_changed{},
    m_signal_toggled{},
    m_pressed(pressed),
    m_red(red),
    m_green(green),
    m_blue(blue)
{

}

const std::string ribi::ToggleButton::GetVersion() noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::ToggleButton::GetVersionHistory() noexcept
{
  return {
    "2011-04-11: Version 1.0: initial version",
    "2011-08-20: Version 1.1: added operator<<",
    "2011-08-31: Version 1.2: added setting the color of a ToggleButton"
  };
}

void ribi::ToggleButton::Press() noexcept
{
  if (!m_pressed) { Toggle(); }
}

void ribi::ToggleButton::Release() noexcept
{
  if (m_pressed) { Toggle(); }
}

void ribi::ToggleButton::SetColor(
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue) noexcept
{
  if (red != m_red || green != m_green || blue != m_blue)
  {
    m_red = red;
    m_green = green;
    m_blue = blue;
    m_signal_color_changed();
  }
}

void ribi::ToggleButton::Toggle() noexcept
{
  m_pressed = !m_pressed;
  m_signal_toggled();
}

std::ostream& ribi::operator<<(std::ostream& os, const ToggleButton& button) noexcept
{
  os
    << "<ToggleButton>"
    << "<blue>"
      << static_cast<int>(button.m_blue)
    << "</blue>"
    << "<green>"
      << static_cast<int>(button.m_green)
    << "</green>"
    << "<pressed>"
      << button.m_pressed
    << "</pressed>"
    << "<red>"
      << static_cast<int>(button.m_red)
    << "</red>"
    << "</ToggleButton>";
  return os;
}
