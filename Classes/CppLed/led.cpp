//---------------------------------------------------------------------------
/*
Led, LED class
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
//From http://www.richelbilderbeek.nl/CppLed.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "led.h"

#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "trace.h"

#pragma GCC diagnostic pop

ribi::Led::Led(
  const double intensity,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_signal_color_changed{},
    m_signal_intensity_changed{},
    m_intensity(intensity),
    m_red(red),
    m_green(green),
    m_blue(blue)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(intensity >= 0.0
    && "An LED intensity must be a positive value");
  assert(intensity <= 1.0
    && "An LED intensity must be equal or lower than 1.0 (that is, 100%)");
}

std::string ribi::Led::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::Led::GetVersionHistory() noexcept
{
  return {
    "2011-04-10: Version 1.0: initial version",
    "2011-08-17: Version 1.1: emit a signal when the color is changed",
    "2011-08-20: Version 1.2: added operator<<"
  };
}

void ribi::Led::SetColor(
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  SetRed(red);
  SetGreen(green);
  SetBlue(blue);
}

void ribi::Led::SetBlue(const unsigned char blue)
{
  if (m_blue != blue)
  {
    m_blue = blue;
    m_signal_color_changed();
  }
}

void ribi::Led::SetGreen(const unsigned char green)
{
  if (m_green != green)
  {
    m_green = green;
    m_signal_color_changed();
  }
}

void ribi::Led::SetIntensity(const double intensity)
{
  assert(intensity >= 0.0
    && "An LED intensity must be a positive value");
  assert(intensity <= 1.0
    && "An LED intensity must be equal or lower than 1.0 (that is, 100%)");
  if (intensity != m_intensity)
  {
    m_intensity = intensity;
    //Emit signal
    m_signal_intensity_changed();
  }
}

void ribi::Led::SetRed(const unsigned char red)
{
  if (m_red != red)
  {
    m_red = red;
    m_signal_color_changed();
  }
}

#ifndef NDEBUG
void ribi::Led::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Led::Test");
  TRACE("Finished ribi::Led::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const Led& led)
{
  os
    << "<Led>"
    << "<blue>"
      << static_cast<int>(led.m_blue)
    << "</blue>"
    << "<green>"
      << static_cast<int>(led.m_green)
    << "</green>"
    << "<intensity>"
      << led.m_intensity
    << "</intensity>"
    << "<red>"
      << static_cast<int>(led.m_red)
    << "</red>"
    << "</Led>";
  return os;
}

