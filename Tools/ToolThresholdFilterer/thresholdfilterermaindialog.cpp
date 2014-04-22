#include "thresholdfilterermaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include <QImage>
#include "trace.h"
#pragma GCC diagnostic pop

QPixmap ribi::ThresholdFiltererMainDialog::DoThresholdFiltering(
  const QPixmap& source,
  const int threshold) noexcept
{
  assert(!source.isNull());
  QImage image { source.toImage() };

  assert(source.width() == image.width());
  assert(source.height() == image.height());

  const int width  = source.width();
  const int height = source.height();

  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      const QRgb p {
        image.pixel(x,y)
      };
      const int grey {
        (qRed(p) + qGreen(p) + qBlue(p)) / 3
      };
      const QRgb q = grey < threshold ? qRgb(0,0,0) : p;
      image.setPixel(x,y,q);
    }
  }
  QPixmap result { QPixmap::fromImage(image) };
  return result;
}
