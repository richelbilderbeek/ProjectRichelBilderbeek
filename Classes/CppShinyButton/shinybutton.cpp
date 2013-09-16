//---------------------------------------------------------------------------
/*
ShinyButton, toggle button class
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
//From http://www.richelbilderbeek.nl/CppShinyButton.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "shinybutton.h"

#include <cassert>
#include <cmath>

#include "trace.h"

#pragma GCC diagnostic pop

ribi::ShinyButton::ShinyButton(
  const double color,
  const double gradient,
  const std::string& text) noexcept
  : m_signal_color_changed{},
    m_signal_text_changed{},
    m_color(color),
    m_gradient(gradient),
    m_text(text)
{

}

const std::string ribi::ShinyButton::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::ShinyButton::GetVersionHistory() noexcept
{
  return {
    "2011-09-21: Version 1.0: initial version"
  };
}

void ribi::ShinyButton::SetColor(
  const double color,
  const double gradient) noexcept
{
  if (color != m_color || gradient != m_gradient)
  {
    m_color = color;
    m_gradient = gradient;
    m_signal_color_changed();
  }
}

void ribi::ShinyButton::SetText(
  const std::string& text) noexcept
{
  if (text != m_text)
  {
    m_text = text;
    m_signal_text_changed();
  }
}

std::ostream& ribi::operator<<(std::ostream& os, const ShinyButton& button) noexcept
{
  os
    << "<ShinyButton>"
    << "<color>"
      << button.m_color
    << "</color>"
    << "<gradient>"
      << button.m_gradient
    << "</gradient>"
    << "<text>"
      << button.m_text
    << "</text>"
    << "</ShinyButton>";
  return os;

}

