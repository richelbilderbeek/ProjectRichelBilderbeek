
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

//From http://www.richelbilderbeek.nl/CppShinyButton.htm

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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "shinybutton.h"

#include <cassert>
#include <cmath>

#include "trace.h"

#pragma GCC diagnostic pop

ShinyButton::ShinyButton(
  const double color,
  const double gradient,
  const std::string& text)
  : m_color(color),
    m_gradient(gradient),
    m_text(text)
{

}

const std::string ShinyButton::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ShinyButton::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-09-21: Version 1.0: initial version");
  return v;
}

void ShinyButton::SetColor(
  const double color,
  const double gradient)
{
  if (color != m_color || gradient != m_gradient)
  {
    m_color = color;
    m_gradient = gradient;
    m_signal_color_changed();
  }
}

void ShinyButton::SetText(
  const std::string& text)
{
  if (text != m_text)
  {
    m_text = text;
    m_signal_text_changed();
  }
}

std::ostream& operator<<(std::ostream& os, const ShinyButton& button)
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

