#include "filteroperationermaindialog.h"

#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>

#include "richelbilderbeekprogram.h"
#pragma GCC diagnostic pop

const QPixmap ribi::FilterOperationerMainDialog::DoFilterOperation(
  const QPixmap& source,
  const boost::numeric::ublas::matrix<double>& filter)
{
  const std::vector<std::vector<int> > v {
    PixmapToVector(source)
  };

  const std::vector<std::vector<double> > w {
    MatrixToVector(filter)
  };

  const std::vector<std::vector<int> > x {
    DoFilterOperation(
      v, //y-x-ordered
      w //y-x-ordered
    )
  };

  const QImage image {
    VectorToImage(x)
  };

  QPixmap result { QPixmap::fromImage(image) };
  return result;
}


//Return a y-x-ordered 2D std::vector with the intensitief of grey
//values from range [0,255] (0=black,255=white) after the filter operation
//From http://www.richelbilderbeek.nl/CppDoFilterOperation.htm
const std::vector<std::vector<int> > ribi::FilterOperationerMainDialog::DoFilterOperation(
  const std::vector<std::vector<int> >& source, //y-x-ordered
  const std::vector<std::vector<double> >& filter) //y-x-ordered
{
  assert(!source.empty());
  assert(!filter.empty());
  const int width = source[0].size();
  const int height = source.size();
  std::vector<std::vector<int> > v(height,std::vector<int>(width));
  const int maxx = source[0].size();
  const int maxy = source.size();
  const int midX = filter[0].size() / 2;
  const int midY = filter.size()    / 2;

  const std::pair<double,double> filterRange = GetFilterRange(filter);
  assert(filterRange.first < filterRange.second);

  for (int y=0; y!=maxy; ++y)
  {
    const int writeY = y;
    assert(writeY >= 0 && writeY < static_cast<int>(v.size()) );
    std::vector<int>& vLine = v[writeY];
    for (int x=0; x!=maxx; ++x)
    {
      //The x and y values are the topleft coordinate of where
      //  the filter will be applied to. This coordinat can be out of
      //  the range, but at least one pixel of where the filter will be
      //  applied to will be in range
      //The pixel value is normalized to the area the
      //  filter operation took place on
      //The outcome of the filter operation is written to
      //  (x + midX, y + midY), which HAS to be in range
      const double unscaledPixelValue = GetFilterOperationPixel(source,x-midX,y-midY,filter);
      //Scale the unscaledPixelValue.
      //The maximal value of unscaledPixelValue is the sum of all positive
      //values in the filter * 255.
      //The minimum value of unscaledPixelValue is the sum of all negative
      //values in the filter * 255.
      //The scaled pixel value must be obtained by transforming the unscaled
      //range [min,max] to [0,256>.
      const double relUnscaledRange
        = (unscaledPixelValue - filterRange.first)
        / (filterRange.second - filterRange.first);
      assert(relUnscaledRange >= 0.0 && relUnscaledRange <= 1.0);
      const double scaledRange = relUnscaledRange * 255;
      assert(scaledRange >= 0.0 && scaledRange < 256.0);
      const int pixel = scaledRange;
      const int writeX = x;
      assert(writeX >= 0 && writeX < width);
      vLine[writeX] = pixel;
    }
  }
  assert(source[0].size()==v[0].size());
  assert(source.size()==v.size());
  return v;
}

//The sourceX and sourceY values are the topleft coordinate of where
//  the filter will be applied to. This coordinat can be out of
//  the range, but at least one pixel of where the filter will be
//  applied to will be in range. If there are no pixels in range,
//  an assertion will fail.
//The pixel value is normalized to the area the
//  filter operation took place on. Therefore, this area must be non-zero
//The outcome of this filter operation will be written to
//  (x + midX, y + midY), which HAS to be in range
//From http://www.richelbilderbeek.nl/CppDoFilterOperation.htm
double ribi::FilterOperationerMainDialog::GetFilterOperationPixel(
  const std::vector<std::vector<int> >& source, //y-x-ordered
  const int sourceX,
  const int sourceY,
  const std::vector<std::vector<double> >& filter) //y-x-ordered
{
  assert(!source.empty());
  assert(!filter.empty());
  const int sourceMaxY = source.size();
  const int sourceMaxX = source[0].size();
  const int filterMaxY = filter.size();
  const int filterMaxX = filter[0].size();

  double result = 0.0;
  int nPixels = 0;
  for (int y=0; y!=filterMaxY; ++y)
  {
    const int readY = sourceY + y;
    if ( readY < 0 || readY >= sourceMaxY) continue;
    assert(y >= 0);
    assert(y < static_cast<int>(filter.size()));
    const std::vector<double>& lineFilter = filter[y];
    assert(readY >= 0);
    assert(readY < static_cast<int>(source.size()));
    const std::vector<int>& lineSource = source[readY];
    for (int x=0; x!=filterMaxX; ++x)
    {
      const int readX = sourceX + x;
      if ( readX < 0 || readX >= sourceMaxX) continue;
      assert(x >= 0);
      assert(x < filterMaxX);
      assert(readX >= 0);
      assert(readX < sourceMaxX);
      const double deltaResult = static_cast<double>(lineSource[readX]) * lineFilter[x];
      result += deltaResult;
      ++nPixels;
    }
  }
  assert(nPixels!=0);
  const double filteredValue = result / static_cast<double>(nPixels);
  return filteredValue;

}

//Obtains the range a filter can have
//Assumes the every element has a maximum value of 255
//From http://www.richelbilderbeek.nl/CppDoFilterOperation.htm
const std::pair<double,double> ribi::FilterOperationerMainDialog::GetFilterRange(const std::vector<std::vector<double> >& filter)
{
  assert(!filter.empty());
  const int maxx = filter[0].size();
  const int maxy = filter.size();
  assert(maxx + maxy > 2 && "Filter size must be bigger then 1x1");
  double min = 0.0;
  double max = 0.0;
  for(int y=0; y!=maxy; ++y)
  {
    assert(y >= 0);
    assert(y  < static_cast<int>(filter.size()) );

    const std::vector<double>& lineFilter = filter[y];
    for(int x=0; x!=maxx; ++x)
    {
      assert(x >= 0);
      assert(x  < static_cast<int>(lineFilter.size()) );

      const double value = lineFilter[x];
      if (value < 0.0) min +=value;
      else if (value > 0.0) max +=value;
    }
  }
  const std::pair<double,double> range
  = std::make_pair(min * 255.0, max * 255.0);
  return range;
}

const std::vector<std::vector<int> > ribi::FilterOperationerMainDialog::ImageToVector(const QImage& image)
{
  const int height = image.height();
  const int width = image.width();
  std::vector<std::vector<int> > v(height,std::vector<int>(width));

  for (int y=0; y!=height; ++y)
  {
    assert(y < static_cast<int>(v.size()));
    for (int x=0; x!=width; ++x)
    {
      const QRgb rgb {
        image.pixel(x,y)
      };
      const int g { (qRed(rgb) + qBlue(rgb) + qGreen(rgb)) / 3 };
      assert(g >= 0);
      assert(g < 256);
      assert(x < static_cast<int>(v[y].size()));
      v[y][x] = g;
    }
  }
  return v;
}

const std::vector<std::vector<double> >
  ribi::FilterOperationerMainDialog::MatrixToVector(
  const boost::numeric::ublas::matrix<double>& m)
{
  const int height = m.size1();
  const int width = m.size2();
  std::vector<std::vector<double> > v(height,std::vector<double>(width));
  for (int y=0; y!=height; ++y)
  {
    assert(y < static_cast<int>(v.size()));
    for (int x=0; x!=width; ++x)
    {
      assert(x < static_cast<int>(v[y].size()));
      v[y][x] = m(y,x);
    }
  }
  return v;
}

const std::vector<std::vector<int> > ribi::FilterOperationerMainDialog::PixmapToVector(const QPixmap& pixmap)
{
  return ImageToVector(pixmap.toImage());
}

const QImage ribi::FilterOperationerMainDialog::VectorToImage(
  const std::vector<std::vector<int> >& v)
{
  assert(!v.empty());
  assert(!v[0].empty());
  const int height = static_cast<int>(v.size());
  const int width  = static_cast<int>(v[0].size());

  QImage image(width,height,QImage::Format_RGB32);

  for (int y=0; y!=height; ++y)
  {
    assert(y < static_cast<int>(v.size()));
    assert(v[y].size() == v[0].size()
      && "must be a rectangular 2D vector");
    for (int x=0; x!=width; ++x)
    {
      assert(x < static_cast<int>(v[y].size()));
      const int grey { v[y][x] };
      QRgb rgb{ qRgb(grey,grey,grey) };
      image.setPixel(x,y,rgb);
    }
  }
  return image;
}
