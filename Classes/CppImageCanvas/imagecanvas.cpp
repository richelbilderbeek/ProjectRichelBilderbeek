#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "imagecanvas.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iterator>

#include <boost/math/constants/constants.hpp>

#include <QImage>

#include "dotmatrixstring.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::ImageCanvas::ImageCanvas(
  const std::string& filename,
  const int n_cols,
  const ribi::Canvas::ColorSystem colorSystem,
  const ribi::Canvas::CoordinatSystem coordinatSystem)
  : mColorSystem(colorSystem),
    mCoordinatSystem(coordinatSystem),
    m_filename(filename),
    m_n_cols(n_cols)
{
  #ifndef NDEBUG
  Test();
  #endif
}

const std::vector<std::vector<double> >
  ribi::ImageCanvas::ConvertToGreyYx(const QImage * const i)
{
  const int maxy = i->height();
  const int maxx = i->width();
  const int n_bytes = i->bytesPerLine() / maxx;

  std::vector<std::vector<double> > v;
  for (int y=0; y!=maxy; ++y)
  {
    v.push_back(std::vector<double>());
    const unsigned char * const line = i->scanLine(y);
    for (int x=0; x!=maxx; ++x)
    {
      int sum = 0;
      for (int byte=0; byte!=n_bytes; ++byte)
      {
        sum += line[(x * n_bytes) + byte];
      }
      const double greyness
        = (boost::numeric_cast<double>(sum)
        / boost::numeric_cast<double>(n_bytes))
        / 256.0;
      assert(greyness >= 0.0);
      assert(greyness <= 1.0);
      v.back().push_back(greyness);
    }
  }
  return v;
}

const std::string ribi::ImageCanvas::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::ImageCanvas::GetVersionHistory() noexcept
{
  return {
    "2014-01-07: version 1.0: initial version, split of from AsciiArterMainDialog"
  };
}

#ifndef NDEBUG
void ribi::ImageCanvas::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ImageCanvas::Test");
  TRACE("Finished ribi::ImageCanvas::Test successfully");
}
#endif

const boost::shared_ptr<ribi::Canvas> ribi::ImageCanvas::ToCanvas() const noexcept
{
  const boost::scoped_ptr<QImage> qimage{
    new QImage(m_filename.c_str())
  };
  const std::vector<std::vector<double> > image { ConvertToGreyYx(qimage.get()) };

  const boost::shared_ptr<ribi::Canvas> canvas {
    new Canvas(image,mColorSystem,mCoordinatSystem)
  };
  assert(canvas);
  return canvas;
}

std::ostream& ribi::operator<<(std::ostream& os, const ImageCanvas& canvas)
{
  os << (*canvas.ToCanvas());
  return os;
}
