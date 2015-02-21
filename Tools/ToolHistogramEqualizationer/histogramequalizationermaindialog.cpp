//---------------------------------------------------------------------------
/*
HistogramEqualizationer, tool to perform a histogram equalization
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
//From http://www.richelbilderbeek.nl/ToolHistogramEqualizationer.htm
//---------------------------------------------------------------------------
#include "histogramequalizationermaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <vector>
#include <boost/scoped_ptr.hpp>

#include "trace.h"
#pragma GCC diagnostic pop

QImage ribi::HistogramEqualizationerMainDialog::DoHistogramEqualization(const QImage& source) noexcept
{
  QImage image(source);
  const int width  = image.width();
  const int height = image.height();


  const int surface = width * height;
  const int nGreyValues = 256; //There are 256 different pixel intensities
  const std::vector<int> histogram = GetImageHistogram(image);
  assert(nGreyValues==static_cast<int>(histogram.size()));
  const std::vector<int> cumulativeHistogram = GetCumulativeHistogram(histogram);
  assert(nGreyValues==static_cast<int>(cumulativeHistogram.size()));

  //Works, but anybody knows how to use std::for_each or std::transform for this?
  std::vector<int> rescaledHistogram(nGreyValues,0);
  for (int i=0; i!=nGreyValues; ++i)
  {
    //'surface + 1' to prevent that rescaledGreyValue == 256
    const int rescaledGreyValue
      = static_cast<int>(
          static_cast<double>(nGreyValues)
        * static_cast<double>(cumulativeHistogram[i])
        / static_cast<double>(surface + 1) );
    assert(rescaledGreyValue >= 0);
    assert(rescaledGreyValue < 256);
    rescaledHistogram[i] = rescaledGreyValue;
  }

  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const QRgb rgb { image.pixel(x,y) };
      const int grey {
        ( qRed(rgb) + qGreen(rgb) + qBlue(rgb) ) / 3
      };
      assert(grey >=   0);
      assert(grey  < 256);
      const int greyNew = rescaledHistogram[grey];
      assert(greyNew >= 0);
      assert(greyNew  < 256);
      image.setPixel(x,y,qRgb(greyNew,greyNew,greyNew));
    }
  }


  return image;
}

//From http://www.richelbilderbeek.nl/CppConvertToGrey.htm
/*
void ConvertToGrey(const TImage * const source, TImage * const target)
{
  assert(source!=0 && "Source image is NULL");
  assert(target!=0 && "Target image is NULL");
  assert(source->Picture->Bitmap!=0 && "Source bitmap is NULL");
  assert(target->Picture->Bitmap!=0 && "Target bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Source bitmap must be 24 bit");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Target bitmap must be 24 bit");
  //Get the width and height from the source
  const int width  = source->Picture->Bitmap->Width;
  const int height = source->Picture->Bitmap->Height;
  //Set the target's width and height
  target->Picture->Bitmap->Width  = width;
  target->Picture->Bitmap->Height = height;

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * lineSource
      = static_cast<const unsigned char *>(
        source->Picture->Bitmap->ScanLine[y]);
    unsigned char * lineTarget
      = static_cast<unsigned char *>(
        target->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const int grey
        = (lineSource[x*3+0] + lineSource[x*3+1] + lineSource[x*3+2]) / 3;
      assert(grey >= 0 && grey < 256);

      lineTarget[x*3+0]=grey; //Blue
      lineTarget[x*3+1]=grey; //Green
      lineTarget[x*3+2]=grey; //Red
    }
  }
}
*/

const std::vector<int> ribi::HistogramEqualizationerMainDialog::GetImageHistogram(const QImage& image) noexcept
{
  assert(!image.isNull() && "Image must not be null");
  //Get the width and height from the source
  const int width  = image.width();
  const int height = image.height();

  std::vector<int> histogram(256,0); //There are 256 different color values

  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const QRgb rgb {
        image.pixel(x,y)
      };
      const int grey {
        (
          qRed(rgb)
        + qGreen(rgb)
        + qBlue(rgb)
        )
        / 3
      };
      assert(grey >= 0 && grey < 256);
      ++histogram[grey];
    }
  }
  return histogram;
}

