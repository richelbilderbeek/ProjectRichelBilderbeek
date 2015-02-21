//---------------------------------------------------------------------------
/*
Led, LED class
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
//From http://www.richelbilderbeek.nl/CppLed.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "led.h"

#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "testtimer.h"
#include "trace.h"
#include "testtimer.h"

#pragma GCC diagnostic pop

ribi::Led::Led(
  const double intensity,
  const int red,
  const int green,
  const int blue)
  : m_signal_color_changed{},
    m_signal_intensity_changed{},
    m_blue(blue),
    m_green(green),
    m_intensity(intensity),
    m_red(red)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(red >= 0);
  assert(red < 256);
  assert(green >= 0);
  assert(green < 256);
  assert(blue >= 0);
  assert(blue < 256);

  assert(intensity >= 0.0
    && "An LED intensity must be a positive value");
  assert(intensity <= 1.0
    && "An LED intensity must be equal or lower than 1.0 (that is, 100%)");
}

std::string ribi::Led::GetVersion() noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::Led::GetVersionHistory() noexcept
{
  return {
    "2011-04-10: Version 1.0: initial version",
    "2011-08-17: Version 1.1: emit a signal when the color is changed",
    "2011-08-20: Version 1.2: added operator<<",
    "2014-06-20: Version 1.3: changed color data types from unsigned char to int"
  };
}

void ribi::Led::SetColor(
  const int red,
  const int green,
  const int blue
) noexcept
{
  SetRed(red);
  SetGreen(green);
  SetBlue(blue);
}

void ribi::Led::SetBlue(const int blue) noexcept
{
  assert(blue >= 0);
  assert(blue < 256);
  if (m_blue != blue)
  {
    m_blue = blue;
    m_signal_color_changed(this);
  }
}

void ribi::Led::SetGreen(const int green) noexcept
{
  assert(green >= 0);
  assert(green < 256);
  if (m_green != green)
  {
    m_green = green;
    m_signal_color_changed(this);
  }
}

void ribi::Led::SetIntensity(const double intensity) noexcept
{
  assert(intensity >= 0.0
    && "An LED intensity must be a positive value");
  assert(intensity <= 1.0
    && "An LED intensity must be equal or lower than 1.0 (that is, 100%)");
  if (intensity != m_intensity)
  {
    m_intensity = intensity;
    //Emit signal
    m_signal_intensity_changed(this);
  }
}

void ribi::Led::SetRed(const int red) noexcept
{
  assert(red >= 0);
  assert(red < 256);
  if (m_red != red)
  {
    m_red = red;
    m_signal_color_changed(this);
  }
}

#ifndef NDEBUG
void ribi::Led::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

std::string ribi::Led::ToStr() const noexcept
{
  std::stringstream s;
  s << (*this);
  return s.str();
}

std::string ribi::Led::ToXml() const noexcept
{
  std::stringstream s;
  s
    << "<Led>"
    << "<blue>"
      << m_blue
    << "</blue>"
    << "<green>"
      << m_green
    << "</green>"
    << "<intensity>"
      << m_intensity
    << "</intensity>"
    << "<red>"
      << m_red
    << "</red>"
    << "</Led>";
  return s.str();

}

std::ostream& ribi::operator<<(std::ostream& os, const Led& led) noexcept
{
  os
    << led.m_intensity << " ("
    << led.m_red << ", "
    << led.m_green << ", "
    << led.m_blue << ")"
  ;
  return os;
}

bool ribi::operator==(const Led& lhs, const Led& rhs) noexcept
{
  return
       lhs.GetBlue()      == rhs.GetBlue()
    && lhs.GetGreen()     == rhs.GetGreen()
    && lhs.GetIntensity() == rhs.GetIntensity()
    && lhs.GetRed()       == rhs.GetRed()
  ;
}


