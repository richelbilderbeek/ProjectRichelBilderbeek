#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "textcanvas.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iterator>

#include <boost/math/constants/constants.hpp>

#include "dotmatrixstring.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TextCanvas::TextCanvas(
  const int width,
  const int height,
  const Canvas::CoordinatSystem coordinatSystem)
  : m_signal_changed{},
    mCanvas(std::vector<std::string>(height,std::string(width,' '))),
    mCoordinatSystem(coordinatSystem)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(width  > 0);
  assert(height > 0);
}

void ribi::TextCanvas::Clear() noexcept
{
  for (auto& row: mCanvas)
  {
    for (auto& cell:row)
    {
      cell = ' ';
    }
  }

  #ifndef NDEBUG
  for (auto row: mCanvas)
  {
    assert(std::count(row.begin(),row.end(),' ') == static_cast<int>(row.size()));
  }
  #endif
  m_signal_changed(this);
}

bool ribi::TextCanvas::IsInRange(const int x, const int y) const
{
  if (   x < 0
      || y < 0
      || y >= static_cast<int>(mCanvas.size())
      || x >= static_cast<int>(mCanvas[y].size())
     )
    return false;
  return true;
}

const std::string ribi::TextCanvas::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::TextCanvas::GetVersionHistory() noexcept
{
  return {
    "2014-01-09: version 1.0: initial version"
  };
}

void ribi::TextCanvas::PutChar(const int x, const int y, const char c) noexcept
{
  assert(IsInRange(x,y));
  mCanvas[y][x] = c;
}

void ribi::TextCanvas::PutText(const int x, const int y, const std::string& text) noexcept
{
  int i=0;
  for (const auto c: text)
  {
    const int x_here = x + i;
    const int y_here = y;
    if (IsInRange(x_here,y_here))
    {
      PutChar(x_here,y_here,c);
      m_signal_changed(this);
    }
    ++i;
  }
}

void ribi::TextCanvas::SetCoordinatSystem(const Canvas::CoordinatSystem coordinatSystem) noexcept
{
  if (this->mCoordinatSystem != coordinatSystem)
  {
    this->mCoordinatSystem = coordinatSystem;
    this->m_signal_changed(this);
  }
}

#ifndef NDEBUG
void ribi::TextCanvas::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TextCanvas::Test");
  //Drawing text
  {
    const int maxx = 90;
    const int maxy = 18;
    const boost::shared_ptr<TextCanvas> canvas(new TextCanvas(maxx,maxy));
    std::stringstream s_before;
    s_before << (*canvas);
    const std::string str_before {s_before.str() };
    assert(static_cast<int>(str_before.size()) - maxy == maxx * maxy); //-maxy, as newlines are added
    assert(std::count(str_before.begin(),str_before.end(),' ') == maxx * maxy); //Only spaces

    canvas->PutText(1,1,"Hello world");

    std::stringstream s_after;
    s_after << (*canvas);
    const std::string str_after {s_after.str() };
    assert(std::count(str_after.begin(),str_after.end(),' ') != maxx * maxy); //Line trly drawn
  }
  //Is a text that starts before the canvas partially accepted?
  {
    const int maxx = 3;
    const int maxy = 4;
    const boost::shared_ptr<TextCanvas> canvas(new TextCanvas(maxx,maxy));
    std::stringstream s_before;
    s_before << (*canvas);
    const std::string str_before {s_before.str() };
    assert(static_cast<int>(str_before.size()) - maxy == maxx * maxy); //-maxy, as newlines are added
    assert(std::count(str_before.begin(),str_before.end(),' ') == maxx * maxy); //Only spaces

    canvas->PutText(-5,1,"Hello world");

    std::stringstream s_after;
    s_after << (*canvas);
    const std::string str_after {s_after.str() };
    assert(std::count(str_after.begin(),str_after.end(),' ') != maxx * maxy); //Line trly drawn
  }
  TRACE("Finished ribi::TextCanvas::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const TextCanvas& canvas)
{
  std::copy(canvas.mCanvas.begin(),canvas.mCanvas.end(),
    std::ostream_iterator<std::string>(os,"\n")
  );
  return os;
}
