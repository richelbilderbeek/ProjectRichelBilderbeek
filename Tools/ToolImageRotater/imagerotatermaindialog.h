//---------------------------------------------------------------------------
/*
ImageRotater, tool to perform a histogram equalization
Copyright (C) 2008-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolImageRotater.htm
//---------------------------------------------------------------------------
#ifndef IMAGEROTATERMAINDIALOG_H
#define IMAGEROTATERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <vector>
#include <QImage>
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct ImageRotaterMainDialog
{
  ///Draw an image to another image under a certain angle (in radians)
  ///adding black where there is nothing to draw
  //From http://www.richelbilderbeek.nl/CppRotate.htm
  static void Rotate(
    const QImage& imageOriginal,
    QImage& imageResult,
    const double angle);

  private:
  //Special are the double x and y
  static QRgb GetPixel(
    const QImage& image,
    const double x,
    const double y);

  //Special aer the four pixels
  static QRgb GetPixel(
    const QImage& image,
    const int x_tl,
    const int y_tl,
    const double left,
    const double top);

  static void Translate(
    const double dx1,
    const double dy1,
    const double dAngle,
    double& dx2,
    double& dy2);
};

} //~namespace ribi


#endif
