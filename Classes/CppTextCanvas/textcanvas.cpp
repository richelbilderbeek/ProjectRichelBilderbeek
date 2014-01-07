//---------------------------------------------------------------------------
/*
Canvas, ASCII art painting surface class
Copyright (C) 2008-2014 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppCanvas.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "canvas.h"

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

ribi::Canvas::Canvas(
  const int width,
  const int height,
  const ColorSystem colorSystem,
  const CoordinatSystem coordinatSystem)
  : m_signal_changed{},
    mCanvas(std::vector<std::vector<double> >(height,std::vector<double>(width,0.0))),
    mColorSystem(colorSystem),
    mCoordinatSystem(coordinatSystem)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(width  > 0);
  assert(height > 0);
}

ribi::Canvas::Canvas(
  const std::vector<std::vector<double>>& canvas,
  const ColorSystem colorSystem,
  const CoordinatSystem coordinatSystem)
  : m_signal_changed{},
    mCanvas(canvas),
    mColorSystem(colorSystem),
    mCoordinatSystem(coordinatSystem)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(!canvas.empty());
  assert(!canvas[0].empty());
}
void ribi::Canvas::Clear() noexcept
{
  for (auto& row: mCanvas)
  {
    for (auto& cell:row)
    {
      cell = 0.0;
    }
  }

  #ifndef NDEBUG
  for (auto row: mCanvas)
  {
    assert(std::accumulate(row.begin(),row.end(),0.0) == 0.0);
  }
  #endif
  m_signal_changed(this);
}

void ribi::Canvas::DrawCircle(const double xMid, const double yMid, const double ray) noexcept
{
  const double pi = boost::math::constants::pi<double>();
  const double circumference = ray * pi * 2.0;
  const int nSteps = static_cast<int>(circumference + 0.5);
  const double dAngle = 2.0 * pi / static_cast<double>(nSteps);
  double angle = 0.0;
  for (int i=0; i!=nSteps; ++i)
  {
    double x = xMid + (std::sin(angle) * ray);
    double y = yMid - (std::cos(angle) * ray);
    DrawDot(x,y);
    angle += dAngle;
  }
  m_signal_changed(this);
}

void ribi::Canvas::DrawDot(const double x, const double y) noexcept
{
  //Assume a dot has dimensions 1.0 x 1.0
  //and x and y are exactly in the middle of this dot
  const double xBegin = x - 0.5;
  const double yBegin = y - 0.5;
  const double fracLeft = std::ceil(xBegin) - xBegin;
  const double fracTop  = std::ceil(yBegin) - yBegin;
  const int indexLeft = std::floor(xBegin);
  const int indexTop  = std::floor(yBegin);
  if (IsInRange(indexLeft  ,indexTop  ))
    mCanvas[indexTop  ][indexLeft  ] += (fracLeft * fracTop);
  if (IsInRange(indexLeft+1,indexTop  ))
    mCanvas[indexTop  ][indexLeft+1] += ((1.0-fracLeft) * fracTop);
  if (IsInRange(indexLeft  ,indexTop+1))
    mCanvas[indexTop+1][indexLeft  ] += (fracLeft * (1.0-fracTop));
  if (IsInRange(indexLeft+1,indexTop+1))
    mCanvas[indexTop+1][indexLeft+1] += ((1.0-fracLeft) * (1.0-fracTop));
  m_signal_changed(this);
}

void ribi::Canvas::DrawLine(const double x1, const double y1, const double x2, const double y2) noexcept
{

  const double dX = x2 - x1;
  const double dY = y2 - y1;
  const double dist = std::sqrt( (dX * dX) + (dY * dY) );
  const double stepX = dX / dist;
  const double stepY = dY / dist;
  const int nSteps = static_cast<int>(dist + 0.5);
  double x = x1;
  double y = y1;
  for (int i=0; i!=nSteps; ++i)
  {
    DrawDot(x,y);
    x+=stepX;
    y+=stepY;
  }
  m_signal_changed(this);
}

void ribi::Canvas::DrawText(const double top, const double left, const std::string& text) noexcept
{
  const int spacing = 2;
  const boost::shared_ptr<const ribi::DotMatrixString> m {
    new ribi::DotMatrixString(text,spacing)
  };
  const int width  = m->GetMatrixWidth();
  const int height = m->GetMatrixHeight();
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      if (m->GetMatrix(x,y))
      {
        DrawDot(
          left + static_cast<double>(x) + 0.5,
          top  + static_cast<double>(y) + 0.5
        );
      }
    }
  }
}

bool ribi::Canvas::IsInRange(const int x, const int y) const
{
  if (   x < 0
      || y < 0
      || y >= static_cast<int>(mCanvas.size())
      || x >= static_cast<int>(mCanvas[y].size())
     )
    return false;
  return true;
}

const std::string ribi::Canvas::GetVersion() noexcept
{
  return "2.2";
}

const std::vector<std::string> ribi::Canvas::GetVersionHistory() noexcept
{
  return {
    "2008-xx-xx: version 1.0: initial C++ Builder version",
    "2013-08-21: version 2.0: port to C++11 under Qt Creator",
    "2013-08-22: version 2.1: allow two color and coordinat systems"
    "2014-01-07: version 2.2: added the DrawText member function"
  };
}

//The 2D std::vector must be y-x-ordered
//From http://www.richelbilderbeek.nl/CppPlotSurface.htm
void ribi::Canvas::PlotSurface(
  std::ostream& os,
  const std::vector<std::vector<double> >& v,
  const bool use_normal_color_system,
  const bool as_screen_coordinat_system)
{
  assert(v.empty() == false && "Surface must have a size");
  assert(v[0].size() > 0 && "Surface must have a two-dimensional size");

  //Obtain the ASCII art gradient and its size
  static const std::vector<char> asciiArtGradient = GetAsciiArtGradient();
  static const int nAsciiArtGradientChars = asciiArtGradient.size();

  //Minimum and maximum are not given, so these need to be calculated
  const double minVal = MinElement(v);
  double maxVal = MaxElement(v);
  if (minVal == maxVal)
  {
    maxVal = minVal == 0.0 ? 1.0 : minVal * 2.0;
  }

  //Draw the pixels

  const auto row_function(
    [](const std::vector<double>& row,
      std::ostream& os,
      const double minVal,
      const double maxVal,
      const bool use_normal_color_system)
    {
      //Iterate through each row's columns
      const std::vector<double>::const_iterator colEnd = row.end();
      for (std::vector<double>::const_iterator col = row.begin();
        col != colEnd;
        ++col)
      {
        //Scale the found grey value to an ASCII art character
        assert(maxVal != minVal);
        assert(maxVal - minVal != 0.0);
        assert(maxVal > minVal);
        const double greyValueDouble = ( (*col) - minVal) / (maxVal - minVal);
        assert(greyValueDouble >= 0.0 && greyValueDouble <= 1.0);
        const int greyValueInt
          = (use_normal_color_system
          ? greyValueDouble
          : 1.0 - greyValueDouble
          ) * nAsciiArtGradientChars;
        const int greyValue
          = ( greyValueInt < 0
          ? 0 : (greyValueInt > nAsciiArtGradientChars - 1
            ? nAsciiArtGradientChars - 1: greyValueInt) );
        assert(greyValue >= 0 && greyValue < nAsciiArtGradientChars);
        os << asciiArtGradient[greyValue];
      }
      os << std::endl;

    }
  );

  //Iterator through all rows
  if (as_screen_coordinat_system)
  {
    for (const auto row: v)
    {
      row_function(row,os,minVal,maxVal,use_normal_color_system);
    }
  }
  else
  {
    const auto rowEnd = v.rend();
    for (auto row = v.rbegin(); row != rowEnd; ++row)
    {
      row_function(*row,os,minVal,maxVal,use_normal_color_system);
    }
  }
}

//From http://www.richelbilderbeek.nl/CppGetAsciiArtGradient.htm
const std::vector<char> ribi::Canvas::GetAsciiArtGradient() noexcept
{
  return { 'M','N','m','d','h','y','s','o','+','/',':','-','.','`',' ' };
}

//Obtains the minimum element of a 2D container
//From http://www.richelbilderbeek.nl/CppMinElement.htm
template <class Container>
const typename Container::value_type::value_type ribi::Canvas::MinElement(const Container& v)
{
  assert(v.empty() == false && "Container must have a size");
  //Obtain an initial lowest value
  typename Container::value_type::value_type minValue
    = *(std::min_element(v[0].begin(),v[0].end()));

  //Set the iterators
  const typename Container::const_iterator rowEnd = v.end();
  typename Container::const_iterator row = v.begin();
  ++row; //Move to the next position, as index 0 is already read from

  for ( ; row != rowEnd; ++row) //row is already initialized
  {
    const typename Container::value_type::value_type localMinVal
      = *(std::min_element(row->begin(),row->end()));
    if (localMinVal < minValue) minValue = localMinVal;
  }
  return minValue;
}

//Obtains the maximal element of a 2D container
//From http://www.richelbilderbeek.nl/CppMaxElement.htm
template <class Container>
const typename Container::value_type::value_type ribi::Canvas::MaxElement(const Container& v)
{
  assert(v.empty() == false && "Container must have a size");

  //Obtain an initial heighest value
  typename Container::value_type::value_type maxValue
    = *(std::max_element(v[0].begin(),v[0].end()));

  //Set the iterators
  const typename Container::const_iterator rowEnd = v.end();
  typename Container::const_iterator row = v.begin();
  ++row; //Move to the next position, as index 0 is already read from
  for ( ; row != rowEnd; ++row) //row is already initialized
  {
    const typename Container::value_type::value_type localMaxVal
      = *(std::max_element(row->begin(),row->end()));
    if (localMaxVal > maxValue) maxValue = localMaxVal;
  }
  return maxValue;
}

void ribi::Canvas::SetColorSystem(const ColorSystem colorSystem) noexcept
{
  if (this->mColorSystem != colorSystem)
  {
    this->mColorSystem = colorSystem;
    this->m_signal_changed(this);
  }
}

void ribi::Canvas::SetCoordinatSystem(const CoordinatSystem coordinatSystem) noexcept
{
  if (this->mCoordinatSystem != coordinatSystem)
  {
    this->mCoordinatSystem = coordinatSystem;
    this->m_signal_changed(this);
  }
}

#ifndef NDEBUG
void ribi::Canvas::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Canvas::Test");
  //Drawing text
  {
    const int maxx = 90;
    const int maxy = 18;
    const boost::shared_ptr<Canvas> canvas(new Canvas(maxx,maxy,ColorSystem::invert));
    std::stringstream s_before;
    s_before << (*canvas);
    const std::string str_before {s_before.str() };
    assert(static_cast<int>(str_before.size()) - maxy == maxx * maxy); //-maxy, as newlines are added
    assert(std::count(str_before.begin(),str_before.end(),' ') == maxx * maxy); //Only spaces

    canvas->DrawText(1,1,"Hello world");

    std::stringstream s_after;
    s_after << (*canvas);
    const std::string str_after {s_after.str() };
    assert(std::count(str_after.begin(),str_after.end(),' ') != maxx * maxy); //Line trly drawn
  }
  //Is a line that starts and ends beyond the canvas drawn?
  {
    const int maxx = 3;
    const int maxy = 4;
    const boost::shared_ptr<Canvas> canvas(new Canvas(maxx,maxy,ColorSystem::invert));
    std::stringstream s_before;
    s_before << (*canvas);
    const std::string str_before {s_before.str() };
    assert(static_cast<int>(str_before.size()) - maxy == maxx * maxy); //-maxy, as newlines are added
    assert(std::count(str_before.begin(),str_before.end(),' ') == maxx * maxy); //Only spaces

    canvas->DrawLine(-maxx,-maxy,maxx*2.0,maxy*2.0);

    std::stringstream s_after;
    s_after << (*canvas);
    const std::string str_after {s_after.str() };
    assert(std::count(str_after.begin(),str_after.end(),' ') != maxx * maxy); //Line trly drawn
  }
  //Draw a smiley is all coordinat- and colorsystem combinations
  for (int i=0; i!=4; ++i)
  {
    const int maxx = 79;
    const int maxy = 23;
    const boost::shared_ptr<Canvas> canvas(new Canvas(maxx,maxy));
    canvas->SetColorSystem(
      i % 2
      ? ColorSystem::normal
      : ColorSystem::invert);
    canvas->SetCoordinatSystem(
      i / 2
      ? CoordinatSystem::screen
      : CoordinatSystem::graph);

    //Determine and calculate dimensions and coordinats of smiley
    const double maxxD = static_cast<double>(maxx);
    const double maxyD = static_cast<double>(maxy);
    const double midX        = 0.50 * maxxD;
    const double midY        = 0.50 * maxyD;
    const double headRay     = 0.50 * maxyD;
    const double eyeLeftX    = 0.50 * maxxD - (0.35 * headRay) ;
    const double eyeLeftY    = 0.50 * maxyD - (0.25 * headRay) ;
    const double eyeRightX   = 0.50 * maxxD + (0.35 * headRay) ;
    const double eyeRightY   = 0.50 * maxyD - (0.25 * headRay) ;
    const double eyeRay      = 0.30 * headRay;
    const double mouthLeftX  = 0.50 * maxxD - (0.7 * headRay) ;
    const double mouthMidX   = 0.50 * maxxD;
    const double mouthRightX = 0.50 * maxxD + (0.7 * headRay) ;
    const double mouthLeftY  = 0.50 * maxyD + (0.2 * headRay) ;
    const double mouthMidY   = 0.50 * maxyD + (0.7 * headRay) ;
    const double mouthRightY = 0.50 * maxyD + (0.2 * headRay) ;
    //Draw the image on Canvas
    canvas->DrawCircle(midX, midY, headRay);
    canvas->DrawCircle(eyeLeftX, eyeLeftY, eyeRay);
    canvas->DrawDot(eyeLeftX, eyeLeftY);
    canvas->DrawCircle(eyeRightX, eyeRightY, eyeRay);
    canvas->DrawDot(eyeRightX, eyeRightY);
    canvas->DrawLine(mouthLeftX, mouthLeftY, mouthMidX, mouthMidY);
    canvas->DrawLine(mouthMidX, mouthMidY, mouthRightX, mouthRightY);
    canvas->DrawLine(mouthRightX, mouthRightY, mouthLeftX, mouthLeftY);
    {
      std::stringstream s;
      s << (*canvas);
      assert(!s.str().empty());
    }
    canvas->Clear();
    {
      std::stringstream s;
      s << (*canvas);
      assert(!s.str().empty());
    }
  }
  TRACE("Finished ribi::Canvas::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const Canvas& canvas)
{
  ribi::Canvas::PlotSurface(
    os,
    canvas.mCanvas,
    canvas.mColorSystem == ribi::Canvas::ColorSystem::normal,
    canvas.mCoordinatSystem == ribi::Canvas::CoordinatSystem::screen);
  return os;
}
