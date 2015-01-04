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
#include "imagerotatermaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include <boost/math/constants/constants.hpp>

#include "geometry.h"
#include "trace.h"
#pragma GCC diagnostic pop

QRgb ribi::ImageRotaterMainDialog::GetPixel(
  const QImage& image,
  const double x,
  const double y)
{
  const double xRemainder = x - static_cast<int>(x);
  const double yRemainder = y - static_cast<int>(y);
  const int x_tl = ( xRemainder > 0.5 ? x : x-1);
  const int y_tl = ( yRemainder > 0.5 ? y : y-1);
  const double left = ( xRemainder > 0.5 ? 1.5 - xRemainder : 0.5 -
  xRemainder);
  const double top  = ( yRemainder > 0.5 ? 1.5 - yRemainder : 0.5 -
  yRemainder);
  return GetPixel(image,x_tl,y_tl,left,top);
}

QRgb ribi::ImageRotaterMainDialog::GetPixel(
  const QImage& image,
  const int x_tl,
  const int y_tl,
  const double left,
  const double top)
{
  const double right = 1.0 - left;
  const double bottom = 1.0 - top;
  assert(left   >= 0.0 && left   <=1.0);
  assert(top    >= 0.0 && top    <=1.0);
  assert(right  >= 0.0 && right  <=1.0);
  assert(bottom >= 0.0 && bottom <=1.0);

  const QRgb tl { image.pixel(x_tl+0,y_tl+0) };
  const QRgb tr { image.pixel(x_tl+1,y_tl+0) };
  const QRgb bl { image.pixel(x_tl+0,y_tl+1) };
  const QRgb br { image.pixel(x_tl+1,y_tl+1) };

  const double rTotal
    = (top    * left  * static_cast<double>(qRed(tl)))
    + (top    * right * static_cast<double>(qRed(tr)))
    + (bottom * left  * static_cast<double>(qRed(bl)))
    + (bottom * right * static_cast<double>(qRed(br)));
  const double gTotal
    = (top    * left  * static_cast<double>(qGreen(tl)))
    + (top    * right * static_cast<double>(qGreen(tr)))
    + (bottom * left  * static_cast<double>(qGreen(bl)))
    + (bottom * right * static_cast<double>(qGreen(br)));
  const double bTotal
    = (top    * left  * static_cast<double>(qBlue(tl)))
    + (top    * right * static_cast<double>(qBlue(tr)))
    + (bottom * left  * static_cast<double>(qBlue(bl)))
    + (bottom * right * static_cast<double>(qBlue(br)));
  assert(rTotal >= 0.0 && rTotal < 256.0);
  assert(gTotal >= 0.0 && gTotal < 256.0);
  assert(bTotal >= 0.0 && bTotal < 256.0);
  return qRgb(
    static_cast<unsigned char>(rTotal),
    static_cast<unsigned char>(gTotal),
    static_cast<unsigned char>(bTotal)
  );
}

void ribi::ImageRotaterMainDialog::Rotate(
  const QImage& pixmapOriginal,
  QImage& pixmapResult,
  const double angle)
{
  QImage imageOriginal = pixmapOriginal; //pixmapOriginal.toImage();
  QImage imageResult = pixmapResult;     //pixmapResult.toImage();
  const int maxx = imageResult.width();
  const int maxy = imageResult.height();
  const double midx = static_cast<double>(maxx) / 2.0;
  const double midy = static_cast<double>(maxy) / 2.0;

  for (int y=0; y!=maxy; ++y)
  {
    for(int x=0; x!=maxx; ++x)
    {
      const double dx1 = static_cast<double>(x) - midx;
      const double dy1 = static_cast<double>(y) - midy;
      double dx2, dy2; //Coordinats in original
      Translate(dx1,dy1,angle,dx2,dy2);
      const double x2 =
      (static_cast<double>(imageOriginal.width() ) / 2.0) + dx2;
      const double y2 =
      (static_cast<double>(imageOriginal.height()) / 2.0) + dy2;
      if ( x2 < 1.0
        || y2 < 1.0
        || x2 >= imageOriginal.width() - 1.0
        || y2 >= imageOriginal.height() - 1.0
        )
      { //Out of range
        //SetPixel(imageResult,x,y,qRgb(0,0,0));
        imageResult.setPixel(x,y,qRgb(0,0,0));
        continue;
      }
      const QRgb rgb {
        GetPixel(imageOriginal,x2,y2)
      };
      imageResult.setPixel(x,y,rgb);
      //SetPixel(imageResult,x,y,rgb);
    }
  }
  pixmapResult = imageResult;
  //pixmapResult = QPixmap::fromImage(imageResult);
}



void ribi::ImageRotaterMainDialog::Translate(
  const double dx1,
  const double dy1,
  const double dAngle,
  double& dx2,
  double& dy2)
{
  const double oldAngle = Geometry().GetAngleClockScreen(dx1,dy1);
  const double newAngle = oldAngle - dAngle; //NEW: Must be a minus to rotate clockwise
  const double ray = std::sqrt((dx1 * dx1) + (dy1 * dy1)); //Pythagoras
  dx2 =  std::sin(newAngle) * ray;
  dy2 = -std::cos(newAngle) * ray;
}
