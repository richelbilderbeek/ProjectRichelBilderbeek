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
#ifndef ASCIIARTERMAINDIALOG_H
#define ASCIIARTERMAINDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>

#include "about.h"
#pragma GCC diagnostic pop

namespace ribi {

struct AsciiArter;

struct AsciiArterMainDialog
{
  AsciiArterMainDialog();
  const std::vector<std::string>& GetAsciiArt() const { return m_asciiart; }
  bool CanConvert() const;
  void Convert();

  int GetWidth() const { return m_width; }

  void SetImage(const std::vector<std::vector<double> >& image);
  void SetWidth(const int width);

  private:
  std::vector<std::string> m_asciiart;
  std::vector<std::vector<double> > m_image;
  int m_width;

  const boost::scoped_ptr<AsciiArter> m_asciiarter;
};

} //~namespace ribi

#endif // ASCIIARTERMAINDIALOG_H
