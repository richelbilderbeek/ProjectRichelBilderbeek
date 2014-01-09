//---------------------------------------------------------------------------
/*
ImageCanvas, class to convert an image to ASCII art
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppImageCanvas.htm
//---------------------------------------------------------------------------
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
#include <sstream>
#include <boost/math/constants/constants.hpp>

#include <QFile>
#include <QImage>

#include "canvascolorsystems.h"
#include "canvascoordinatsystems.h"
#include "dotmatrixstring.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::ImageCanvas::ImageCanvas(
  const std::string& filename,
  const int n_cols,
  const ribi::CanvasColorSystem colorSystem,
  const ribi::CanvasCoordinatSystem coordinatSystem)
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
  return "3.0";
}

const std::vector<std::string> ribi::ImageCanvas::GetVersionHistory() noexcept
{
  return {
    "2011-03-23: Version 1.0: initial version, then called AsciiArter",
    "2014-01-07: Version 2.0: add conversion to Canvas"
    "2014-01-07: version 3.0: reworked interface, renamed to ImageCanvas"
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
  const std::string temp_filename { fileio::GetTempFileName() };
  {
    const std::string resource_filename { ":/CppImageCanvas/images/R.png" };
    QFile qfile(resource_filename.c_str());
    qfile.copy(temp_filename.c_str());
    if (!fileio::IsRegularFile(temp_filename))
    {
      TRACE("ERROR");
      TRACE(resource_filename);
      TRACE("Resource filename must exist");
    }
  }
  assert(fileio::IsRegularFile(temp_filename));
  const int n
    = static_cast<int>(CanvasColorSystems::GetAll().size())
    * static_cast<int>(CanvasCoordinatSystems::GetAll().size());
  for (int i=0; i!=n; ++i)
  {
    const int ncs = static_cast<int>(CanvasColorSystems::GetAll().size());
    const int a = i % ncs;
    const CanvasColorSystem color_system = CanvasColorSystems::GetAll()[a];
    const int b = i / ncs;
    const CanvasCoordinatSystem coordinat_system
      = CanvasCoordinatSystems::GetAll()[b];
    const ImageCanvas c(temp_filename,20,color_system,coordinat_system);
    std::stringstream s;
    s << c;
    assert(!s.str().empty());
    //TRACE(c);
  }
  fileio::DeleteFile(temp_filename);
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
