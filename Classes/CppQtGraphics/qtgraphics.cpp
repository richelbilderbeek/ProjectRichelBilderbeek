//---------------------------------------------------------------------------
/*
QtGraphics, Qt graphics code snippets
Copyright (C) 2015-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtArrowItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtgraphics.h"

#include <cassert>

#include "stopwatch.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::QtGraphics::QtGraphics()
{
  #ifndef NDEBUG
  Test();
  #endif
}

QImage ribi::QtGraphics::CreateImage(const int width, const int height, const int z) const noexcept
{
  QImage image(width,height,QImage::Format_ARGB32);
  for (int y=0;y!=height;++y)
  {
    for (int x=0;x!=width;++x)
    {
      image.setPixel(
        x,y,
        qRgb((x+z+0)%256,(y+z+0)%256,(x+y+z)%256) //Color
      );
    }
  }
  return image;
}

void ribi::QtGraphics::DrawImage(
  QImage& target, const QImage& source,
  const int left, const int top
) const noexcept
{
  const auto n_channels = source.pixelFormat().channelCount();
  const int width = source.width();
  const int height = source.height();
  for (int y=0; y!=height; ++y)
  {
    const auto line_to = target.scanLine(y + top);
    const auto line_from = source.constScanLine(y);
    std::copy(
      &line_from[0],
      &line_from[width * n_channels],
      &line_to[left * n_channels]
    );
  }
}



void ribi::QtGraphics::DrawImageSlow(
  QImage& target, const QImage& source,
  const int left, const int top
) const noexcept
{
  const auto n_channels = source.pixelFormat().channelCount();
  const int width = source.width();
  const int height = source.height();
  for (int y=0; y!=height; ++y)
  {
    const auto line_to = target.scanLine(y + top);
    const auto line_from = source.constScanLine(y);
    for (int x=0; x!=width; ++x)
    {
      for (int c=0; c!=n_channels; ++c)
      {
        line_to[ ((left + x) * n_channels) + c]
          = line_from[ (x * n_channels) + c]
        ;
      }
      //target.setPixel(left+x,top+y,source.pixel(x,y));
    }
  }
}


void ribi::QtGraphics::DrawImageSlowest(
  QImage& target, const QImage& source,
  const int left, const int top
) const noexcept
{
  const int width = source.width();
  const int height = source.height();
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      target.setPixel(left+x,top+y,source.pixel(x,y));
    }
  }
}

std::string ribi::QtGraphics::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::QtGraphics::GetVersionHistory() const noexcept
{
  return {
    "2015-02-22: version 1.0: initial version",
    "2015-08-28: version 1.1: added CreateImage and DrawImage"
  };
}

#ifndef NDEBUG
void ribi::QtGraphics::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Stopwatch();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Default-construction of QtGraphics"); }
  {
    const QtGraphics q;
  }
  //CreateImage
  {
    const QImage a = QtGraphics().CreateImage(256,256,64);
    assert(!a.isNull());
  }
  {
    QImage target = QtGraphics().CreateImage(256,256,64);
    assert(!target.isNull());
    const QImage source = QtGraphics().CreateImage(196,156,196);
    assert(!source.isNull());
    QtGraphics().DrawImage(target,source,32,64);
  }
  {
    QImage target_slow = QtGraphics().CreateImage(256,256,64);
    QImage target_fast = QtGraphics().CreateImage(256,256,64);
    const QImage source = QtGraphics().CreateImage(196,156,196);
    QtGraphics().DrawImage(    target_fast,source,     32,64);
    QtGraphics().DrawImageSlowest(target_slow,source,32,64);
    assert(target_fast == target_slow);
  }
  const bool do_timing{true};
  if (do_timing)
  {
    QImage target_slow = QtGraphics().CreateImage(2560,2560);
    QImage target_fast = QtGraphics().CreateImage(2560,2560);
    const QImage source = QtGraphics().CreateImage(1960,1560);
    Stopwatch s_fast;
    QtGraphics().DrawImage(target_fast,source,32,64);
    const double t_fast{s_fast.GetElapsedSecs()};
    Stopwatch s_slow;
    QtGraphics().DrawImageSlow(target_slow,source,32,64);
    const double t_slow{s_slow.GetElapsedSecs()};
    TRACE(t_fast);
    TRACE(t_slow);
    TRACE(t_fast / t_slow);
    TRACE((t_fast - t_slow) / t_slow);
    assert(t_fast * 10.0 < t_slow);
  }
}
#endif
