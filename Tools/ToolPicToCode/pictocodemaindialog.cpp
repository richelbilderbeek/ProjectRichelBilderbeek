//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "pictocodemaindialog.h"

#include <boost/lexical_cast.hpp>

#include "pictocodemenudialog.h"
#pragma GCC diagnostic pop

const std::vector<std::string>
  ribi::PicToCodeMainDialog::PicToQtCode(
    const YxImage& image)
{
  const int width  = image.width();
  const int height = image.height();

  std::vector<std::string> v;
  //Function declaration
  v.push_back("//Code generated by PicToCode version " + PicToCodeMenuDialog().GetVersion());
  v.push_back("//From http://www.richelbilderbeek.nl/ToolPicToCode.htm");
  v.push_back("QPixmap Draw()");
  v.push_back("{");
  v.push_back("  const int width  = "
    + boost::lexical_cast<std::string>(width) + ";");
  v.push_back("  const int height = "
    + boost::lexical_cast<std::string>(height) + ";");
  v.push_back("  QPixmap pixmap(width,height);");
  v.push_back("  QImage image = pixmap.toImage();");
  for (int y=0; y!=height; ++y)
  {

    v.push_back("  {");
    v.push_back("    unsigned char * const line");
    v.push_back("      = static_cast<unsigned char *>(image.scanLine("
      + boost::lexical_cast<std::string>(y)
      + "));");
    for (int x=0; x!=width; ++x)
    {
      v.push_back("    line["
        + boost::lexical_cast<std::string>((x*4)+0)
        + "] = "
        + boost::lexical_cast<std::string>(image.m_v[y][x].b)
        + "; line["
        + boost::lexical_cast<std::string>((x*4)+1)
        + "] = "
        + boost::lexical_cast<std::string>(image.m_v[y][x].g)
        +"; line["
        + boost::lexical_cast<std::string>((x*4)+2)
        + "] = "
        + boost::lexical_cast<std::string>(image.m_v[y][x].r)
        +"; line["
        + boost::lexical_cast<std::string>((x*4)+3)
        + "] = "
        + boost::lexical_cast<std::string>(image.m_v[y][x].a)
        +";");
    }
    v.push_back("  }");
  }
  v.push_back("  pixmap = pixmap.fromImage(image);");
  v.push_back("  //Add transparency");
  v.push_back("  const QBitmap mask = pixmap.createMaskFromColor(QColor(0,0,0,0).rgb());");
  v.push_back("  pixmap.setMask(mask);");
  v.push_back("  return pixmap;");
  v.push_back("}");
  return v;
}
