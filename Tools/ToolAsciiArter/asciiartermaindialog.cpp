//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "asciiartermaindialog.h"

#include "asciiarter.h"
#pragma GCC diagnostic pop

ribi::AsciiArterMainDialog::AsciiArterMainDialog()
  : m_width(0),
    m_asciiarter(new AsciiArter)
{

}

bool ribi::AsciiArterMainDialog::CanConvert() const
{
  return !m_image.empty() && m_width > 5;
}

void ribi::AsciiArterMainDialog::Convert()
{
  m_asciiart = m_asciiarter->ImageToAscii(m_image,m_width);
}

void ribi::AsciiArterMainDialog::SetImage(const std::vector<std::vector<double> >& image)
{
  m_image = image;
}

void ribi::AsciiArterMainDialog::SetWidth(const int width)
{
  assert(width > 5);
  m_width = width;
}
