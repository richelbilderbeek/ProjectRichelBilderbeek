//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#ifndef PICTOCODEMAINDIALOG_H
#define PICTOCODEMAINDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include "about.h"
//---------------------------------------------------------------------------
///TicTacToeMenuDialog embodies the logic
///behind the TicTacToe menu
struct PicToCodeMainDialog
{
  struct Pixel
  {
    int r,g,b,a;
  };

  struct YxImage
  {
    std::vector<std::vector<Pixel> > m_v;
    int width() const { return m_v[0].size(); }
    int height() const { return m_v.size(); }
  };


  static const std::vector<std::string>
    PicToQtCode(const YxImage& image);
};
//---------------------------------------------------------------------------
#endif // PICTOCODEMAINDIALOG_H
