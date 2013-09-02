//---------------------------------------------------------------------------
/*
GaborFilterWidget, Widget for the GaborFilter class
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
//From http://www.richelbilderbeek.nl/CppGaborFilterWidget.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "gaborfilterwidget.h"

#include <iostream>

#include "gaborfilter.h"

#pragma GCC diagnostic pop

GaborFilterWidget::GaborFilterWidget(
  const int x,
  const int y,
  const int width,
  const int height,
  const double angle,
  const double frequency,
  const double sigma)
  : m_filter(new GaborFilter(angle,frequency,sigma))
{
  this->SetGeometry(Rect(x,y,width,height));
}

const std::string GaborFilterWidget::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> GaborFilterWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-07-09: version 1.0: initial version");
  return v;
}

std::ostream& operator<<(std::ostream& os, const GaborFilterWidget& widget)
{
  os
    << "<GaborFilterWidget>"
    << widget.GetGeometry()
    << *widget.m_filter
    << "</GaborFilterWidget>";
  return os;
}

