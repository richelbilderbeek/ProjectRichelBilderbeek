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
#include "fileio.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::ImageCanvas::ImageCanvas(
  const std::string& filename,
  const int n_cols,
  const ribi::CanvasColorSystem colorSystem,
  const ribi::CanvasCoordinatSystem coordinatSystem)
  : m_canvas{ConvertToGreyYx(filename)},
    m_color_system(colorSystem),
    m_coordinat_system(coordinatSystem),
    m_n_cols(n_cols)
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<std::string> ribi::ImageCanvas::ConvertGreynessesToAscii(
  const std::vector<std::vector<double> >& image,
  const int width //How many chars the ASCII image will be wide
) noexcept
{
  //If the number of chars is below 5,
  //the calculation would be more complicated due to a too trivial value of charWidth
  assert(width >= 5);

  std::vector<std::string> v;
  if (image.empty()) return v;

  assert(!image.empty());

  //Maxy is in proportion with the bitmap
  const int image_width  = image[0].size();
  const int image_height = image.size();

  const int maxy =
    (static_cast<double>(width)
    / static_cast<double>(image_width))
    * static_cast<double>(image_height);
  assert(maxy > 0);
  const double dX = static_cast<double>(image_width)
    / static_cast<double>(width);
  const double dY = static_cast<double>(image_height)
    / static_cast<double>(maxy);
  assert(dX > 0.0);
  assert(dY > 0.0);

  for (int y=0; y!=maxy; ++y)
  {
    std::string s;
    for (int x=0; x!=width; ++x)
    {
      const int x1 = std::min(
        static_cast<double>(x) * dX,
        image_width  - 1.0) + 0.5;
      const int y1 = std::min(
        static_cast<double>(y) * dY,
        image_height - 1.0) + 0.5;
      const int x2 = std::min(
        (static_cast<double>(x) * dX) + dX,
        image_width  - 1.0) + 0.5;
      const int y2 = std::min(
        (static_cast<double>(y) * dY) + dY,
        image_height - 1.0) + 0.5;
      assert(x1 >= 0);
      assert(x2 >= 0);
      assert(y1 >= 0);
      assert(y2 >= 0);
      assert(x1 < image_width);
      assert(x2 < image_width);
      assert(y1 < image_height);
      assert(y2 < image_height);

      const double f = GetFractionGrey(image,x1,y1,x2,y2);
      assert(f >= 0.0 && f <= 1.0);

      const std::vector<char> m_gradient {
        GetAsciiArtGradient()
      };
      const int i
        = boost::numeric_cast<int>(
          f * boost::numeric_cast<double>(m_gradient.size() - 1));
      assert(i >= 0);
      assert(i < boost::numeric_cast<int>(m_gradient.size()));
      const char c = m_gradient[i];
      s+=c;
    }
    v.push_back(s);
  }
  return v;
}

std::vector<std::vector<double>>
  ribi::ImageCanvas::ConvertToGreyYx(const QImage * const i) noexcept
{
  const int maxy = i->height();
  const int maxx = i->width();

  std::vector<std::vector<double> > v;

  if (maxx == 0) return v;
  assert(maxx > 0);
  const int n_bytes = i->bytesPerLine() / maxx;

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

std::vector<std::vector<double> >
  ribi::ImageCanvas::ConvertToGreyYx(const std::string& filename) noexcept
{
  const boost::scoped_ptr<QImage> qimage{
    new QImage(filename.c_str())
  };
  assert(qimage);
  return ConvertToGreyYx(qimage.get());
}

double ribi::ImageCanvas::GetFractionGrey(
  const std::vector<std::vector<double> >& image,
  const int x1,
  const int y1,
  const int x2,
  const int y2) noexcept
{
  assert(x1 <= x2);
  assert(y1 <= y2);
  if (x1 == x2 && y1 == y2) return GetGreyness(image,x1,y1);
  if (y1 == y2) return GetGreyness(image,x1,x2,y1);
  if (x1 == x2)
  {
    assert(y1 < y2);
    double sum = 0;
    for (int y=y1; y!=y2; ++y)
    {
      const double g = GetGreyness(image,x1,y);
      assert(g >= 0.0);
      assert(g <= 1.0);
      sum+=g;
    }
    const double average_greyness
      = sum / boost::numeric_cast<double>(y2-y1);
    assert(average_greyness >= 0.0);
    assert(average_greyness <= 1.0);
    return average_greyness;
  }
  return GetGreyness(image,x1,y1,x2,y2);
}

double ribi::ImageCanvas::GetGreyness(
  const std::vector<std::vector<double> >& image,
  const int x,
  const int y) noexcept
{
  assert(!image.empty()
    && "Image is NULL");
  assert(x >= 0
    && "x coordinat is below zero");
  assert(y >= 0
    && "y coordinat is below zero");
  assert(y < boost::numeric_cast<int>(image.size())
    && "y coordinat is beyond image height");
  assert(x < boost::numeric_cast<int>(image[y].size())
    && "x coordinat is beyond image width");
  const double greyness = image[y][x];
  assert(greyness >= 0.0);
  assert(greyness <= 1.0);
  return greyness;
}

double ribi::ImageCanvas::GetGreyness(
  const std::vector<std::vector<double> >& image,
  const int x1,
  const int x2,
  const int y) noexcept
{
  assert(!image.empty()
    && "Image is NULL");
  assert(x1 >= 0
    && "x1 coordinat is below zero");
  assert(x2 >= 0
    && "x2 coordinat is below zero");
  assert(y >= 0
    && "y coordinat is below zero");
  assert(y < boost::numeric_cast<int>(image.size())
    && "y coordinat is beyond image height");
  assert(x1 < x2
    && "X-coordinats must be different and ordered");
  assert(x1 < boost::numeric_cast<int>(image[y].size())
    && "x1 coordinat is beyond image width");
  assert(x2 < boost::numeric_cast<int>(image[y].size())
    && "x2 coordinat is beyond image width");
  assert(image[y].begin() + x2 != image[y].end()
    && "x2 coordinat iterator must not be beyond image width");
  const double average_greyness = std::accumulate(
    image[y].begin() + x1,
    image[y].begin() + x2,
    0.0) / boost::numeric_cast<double>(x2-x1);
  assert(average_greyness >= 0.0);
  assert(average_greyness <= 1.0);
  return average_greyness;
}

//Get a square of pixels' average greyness
double ribi::ImageCanvas::GetGreyness(
  const std::vector<std::vector<double> >& image,
  const int x1,
  const int y1,
  const int x2,
  const int y2) noexcept
{
  assert(y1 < y2
    && "Y-coordinats must be ordered");

  double sum = 0.0;

  for (int y=y1; y!=y2; ++y)
  {
    const double grey = GetGreyness(image,x1,x2,y);
    assert(grey >= 0 && grey < 1.0);
    sum+=grey;
  }
  const double average_greyness = sum
    / boost::numeric_cast<double>(y2 - y1);

  assert(average_greyness >=0.0 && average_greyness <= 1.0);
  return average_greyness;
}



int ribi::ImageCanvas::GetHeight() const noexcept
{
  return static_cast<int>(m_canvas.size());
}

std::string ribi::ImageCanvas::GetVersion() noexcept
{
  return "3.0";
}

std::vector<std::string> ribi::ImageCanvas::GetVersionHistory() noexcept
{
  return {
    "2011-03-23: Version 1.0: initial version, then called AsciiArter",
    "2014-01-07: Version 2.0: add conversion to Canvas"
    "2014-01-07: version 3.0: reworked interface, renamed to ImageCanvas"
  };
}

void ribi::ImageCanvas::SetColorSystem(const CanvasColorSystem colorSystem) noexcept
{
  if (this->m_color_system != colorSystem)
  {
    this->m_color_system = colorSystem;
    this->m_signal_changed(this);
  }
}

void ribi::ImageCanvas::SetCoordinatSystem(const CanvasCoordinatSystem coordinatSystem) noexcept
{
  if (this->m_coordinat_system != coordinatSystem)
  {
    this->m_coordinat_system = coordinatSystem;
    this->m_signal_changed(this);
  }
}

#ifndef NDEBUG
void ribi::ImageCanvas::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::string temp_filename { fileio::FileIo().GetTempFileName() };
  {
    const std::string resource_filename { ":/CppImageCanvas/images/R.png" };
    QFile qfile(resource_filename.c_str());
    qfile.copy(temp_filename.c_str());
    if (!fileio::FileIo().IsRegularFile(temp_filename))
    {
      TRACE("ERROR");
      TRACE(resource_filename);
      TRACE("Resource filename must exist");
    }
  }
  assert(fileio::FileIo().IsRegularFile(temp_filename));
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
  fileio::FileIo().DeleteFile(temp_filename);
}
#endif


std::vector<std::string> ribi::ImageCanvas::ToStrings() const noexcept
{
  std::vector<std::vector<double>> canvas { m_canvas };
  if (m_color_system == CanvasColorSystem::invert)
  {
    for (auto& line: canvas)
    {
      for (double& x: line)
      {
        x = 1.0 - x;
      }
    }
  }
  std::vector<std::string> text {
    ConvertGreynessesToAscii(canvas,m_n_cols)
  };
  if (m_coordinat_system == CanvasCoordinatSystem::graph)
  {
    std::reverse(text.begin(),text.end());
  }
  return text;
}

std::ostream& ribi::operator<<(std::ostream& os, const ImageCanvas& canvas) noexcept
{
  const auto v = canvas.ToStrings();
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));
  return os;
}
