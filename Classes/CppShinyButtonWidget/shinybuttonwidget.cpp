//---------------------------------------------------------------------------
/*
ShinyButtonWidget, widget for the ShinyButton class
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
//From http://www.richelbilderbeek.nl/CppShinyButtonWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "shinybuttonwidget.h"

#include <cassert>
#include <cmath>

#include "shinybutton.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::ShinyButtonWidget::ShinyButtonWidget(
  const double color,
  const double gradient,
  const std::string& text,
  const Rect rect)
  : m_signal_clicked{},
    m_button(new ShinyButton(color,gradient,text))
{
  this->SetGeometry(rect);
}

void ribi::ShinyButtonWidget::Click()
{
  m_signal_clicked(this);
}

const std::string ribi::ShinyButtonWidget::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::ShinyButtonWidget::GetVersionHistory()
{
  return {
    "2011-09-21: version 1.0: initial version",
    "2011-10-29: version 1.1: added Click method and m_signal_clicked"
  };
}

std::ostream& ribi::operator<<(std::ostream& os, const ShinyButtonWidget& button)
{
  os
    << "<ShinyButtonWidget>"
    << *button.m_button
    << button.GetGeometry()
    << "</ShinyButtonWidget>";
  return os;
}


