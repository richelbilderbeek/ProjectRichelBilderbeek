//---------------------------------------------------------------------------
/*
GaborFilterWidget, Widget for the GaborFilter class
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
//From http://www.richelbilderbeek.nl/CppGaborFilterWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "gaborfilterwidget.h"

#include <iostream>

#include "gaborfilter.h"

#pragma GCC diagnostic pop

ribi::GaborFilterWidget::GaborFilterWidget(
  const int x,
  const int y,
  const int width,
  const int height,
  const double angle,
  const double frequency,
  const double sigma)
  : m_filter(new GaborFilter(angle,frequency,sigma))
{
  this->SetGeometry(x,y,width,height);
}

std::string ribi::GaborFilterWidget::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::GaborFilterWidget::GetVersionHistory() noexcept
{
  return {
    "2012-07-09: version 1.0: initial version"
  };
}

std::ostream& ribi::operator<<(std::ostream& os, const GaborFilterWidget& widget) noexcept
{
  os
    << "<GaborFilterWidget>"
    //<< widget.GetGeometry()
    << *widget.m_filter
    << "</GaborFilterWidget>";
  return os;
}

