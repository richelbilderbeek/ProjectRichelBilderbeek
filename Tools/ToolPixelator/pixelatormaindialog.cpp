#include "pixelatormaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include <QImage>
#include "trace.h"
#pragma GCC diagnostic pop

QPixmap ribi::PixelatorMainDialog::DoPixelate(const QPixmap& source, const int pixel_size) noexcept
{
  assert(!source.isNull());
  const QImage imageOriginal { source.toImage() };
  QImage imageResult { source.toImage() };

  assert(source.width() == imageResult.width());
  assert(source.height() == imageResult.height());

  const int width  = source.width();
  const int height = source.height();
  const int maxx = 1 + (width  / pixel_size);
  const int maxy = 1 + (height / pixel_size);

  for (int y=0; y!=maxy; ++y)
  {
    const int y1 = (y * pixel_size);
    if (y1 >= height) continue;
    const int y2 = std::min( y1 + pixel_size, height);
    assert(y1 <= height);
    assert(y2 <= height);
    assert(y1!=y2);

    for (int x=0; x!=maxx; ++x)
    {
      const int x1 = (x * pixel_size);
      if (x1 >= width) continue;
      const int x2 = std::min( x1 + pixel_size, width);
      assert(x1 <= width);
      assert(x2 <= width);
      assert(x1!=x2);
      const QRgb p {
        GetPixel(imageOriginal,x1,y1,x2,y2)
      };
      SetPixel(imageResult,x1,y1,x2,y2,p);
    }
  }
  QPixmap result { QPixmap::fromImage(imageResult) };
  return result;
}

QRgb ribi::PixelatorMainDialog::GetPixel(
  const QImage& image,
  const int x,
  const int y) noexcept
{
  assert(!image.isNull());
  assert(x >= 0);
  assert(x < image.width());
  assert(y >= 0);
  assert(y < image.height());
  return image.pixel(x,y);
}

QRgb ribi::PixelatorMainDialog::GetPixel(
  const QImage& image,
  const int x1,
  const int x2,
  const int y) noexcept
{
  assert(!image.isNull());
  assert(x1 >= 0);
  assert(x1 < image.width());
  assert(x2 >= 0);
  assert(x2 <= image.width());
  assert(y >= 0);
  assert(y < image.height());
  assert(x1 < x2);

  const int nPixels = x2 - x1;
  int sumRed   = 0;
  int sumGreen = 0;
  int sumBlue  = 0;

  for (int x=x1; x!=x2; ++x)
  {
    const QRgb p { image.pixel(x,y) };
    sumRed   += qRed(p);
    sumGreen += qGreen(p);
    sumBlue  += qBlue(p);
  }
  const int averageRed   = sumRed   / nPixels;
  const int averageGreen = sumGreen / nPixels;
  const int averageBlue  = sumBlue  / nPixels;
  assert(averageRed   >= 0 && averageRed   < 256);
  assert(averageGreen >= 0 && averageGreen < 256);
  assert(averageBlue  >= 0 && averageBlue  < 256);
  QRgb rgb { qRgb(averageRed,averageGreen,averageBlue) };
  return rgb;
}

QRgb ribi::PixelatorMainDialog::GetPixel(
  const QImage& image,
  const int x1,
  const int y1,
  const int x2,
  const int y2) noexcept
{
  assert(!image.isNull());
  assert(x1 >= 0);
  assert(x1 < image.width());
  assert(x2 >= 0);
  assert(x2 <= image.width());
  assert(y1 >= 0);
  assert(y1 < image.height());
  assert(y2 >= 0);
  assert(y2 <= image.height());
  assert(x1 < x2 );
  assert(y1 < y2 );

  const int nPixelsVertical = y2 - y1;
  int sumRed   = 0;
  int sumGreen = 0;
  int sumBlue  = 0;

  for (int y=y1; y!=y2; ++y)
  {
    const QRgb p { GetPixel(image,x1,x2,y) };
    sumRed   += qRed(p);
    sumGreen += qGreen(p);
    sumBlue  += qBlue(p);
  }
  const int averageRed   = sumRed   / nPixelsVertical;
  const int averageGreen = sumGreen / nPixelsVertical;
  const int averageBlue  = sumBlue  / nPixelsVertical;
  assert(averageRed   >= 0 && averageRed   < 256);
  assert(averageGreen >= 0 && averageGreen < 256);
  assert(averageBlue  >= 0 && averageBlue  < 256);
  QRgb rgb { qRgb(averageRed,averageGreen,averageBlue) };
  return rgb;
}

void ribi::PixelatorMainDialog::SetPixel(
  QImage& image,
  const int x,
  const int y,
  const QRgb color) noexcept
{
  assert(!image.isNull());
  assert(x >= 0);
  assert(x < image.width());
  assert(y >= 0);
  assert(y < image.height());

  image.setPixel(x,y,color);
}

void ribi::PixelatorMainDialog::SetPixel(
  QImage& image,
  const int x1,
  const int x2,
  const int y,
  const QRgb color) noexcept
{
  assert(!image.isNull());
  assert(x1 >= 0);
  assert(x1 < image.width());
  assert(x2 >= 0);
  assert(x2 <= image.width());
  assert(y >= 0);
  assert(y < image.height());
  assert(x1 < x2 );

  for (int x=x1; x!=x2; ++x)
  {
    SetPixel(image,x,y,color);
  }
}

void ribi::PixelatorMainDialog::SetPixel(
  QImage& image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  const QRgb color) noexcept
{
  assert(!image.isNull());
  assert(x1 >= 0);
  assert(x1 < image.width());
  assert(x2 >= 0);
  assert(x2 <= image.width());
  assert(y1 >= 0);
  assert(y1 < image.height());
  assert(y2 >= 0);
  assert(y2 <= image.height());
  assert(x1 < x2 );
  assert(y1 < y2 );
  for (int y=y1; y!=y2; ++y)
  {
    SetPixel(image,x1,x2,y,color);
  }
}
