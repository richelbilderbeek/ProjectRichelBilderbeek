//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2015 Richel Bilderbeek

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

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "about.h"
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct ImageCanvas;
struct AsciiArter;

///AsciiArterMainDialog converts a graphics file to ASCII art
struct AsciiArterMainDialog
{
  ///Will throw an exception if
  ///- the file does not exists
  ///- the number of columns is less than five
  AsciiArterMainDialog(
    const std::string& filename,
    const int n_cols
  );

  std::vector<std::string> GetAsciiArt() const noexcept; // { return CreateAsciiArt(m_filename,m_n_cols); }
  const boost::shared_ptr<ImageCanvas> GetImageCanvas() const noexcept;

  private:


  ///Will throw an exception if
  ///- file does not exist
  ///- n_cols < 5
  //static const std::vector<std::string> CreateAsciiArt(
  //  const std::string& filename, const int n_cols);

  //const std::vector<std::string> m_asciiart;
  const std::string m_filename;
  const int m_n_cols;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const AsciiArterMainDialog& d);

} //~namespace ribi

#endif // ASCIIARTERMAINDIALOG_H
