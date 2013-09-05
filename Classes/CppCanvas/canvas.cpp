//---------------------------------------------------------------------------
/*
Canvas, ASCII art painting surface class
Copyright (C) 2008-2013  Richel Bilderbeek

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
#include "canvas.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iterator>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>
#pragma GCC diagnostic pop

ribi::Canvas::Canvas(
  const int width,
  const int height,
  const ColorSystem colorSystem,
  const CoordinatSystem coordinatSystem)
  : mCanvas(std::vector<std::vector<double> >(height,std::vector<double>(width,0.0))),
    mColorSystem(colorSystem),
    mCoordinatSystem(coordinatSystem)
{
  assert(width  > 0);
  assert(height > 0);
}

void ribi::Canvas::DrawDot(const double x, const double y)
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
}

void ribi::Canvas::DrawLine(const double x1, const double y1, const double x2, const double y2)
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
}

void ribi::Canvas::DrawCircle(const double xMid, const double yMid, const double ray)
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

std::ostream& ribi::operator<<(std::ostream& os, const Canvas& canvas)
{
  ribi::Canvas::PlotSurface(
    os,
    canvas.mCanvas,
    canvas.mColorSystem == ribi::Canvas::ColorSystem::normal,
    canvas.mCoordinatSystem == ribi::Canvas::CoordinatSystem::screen);
  return os;
}

const std::string ribi::Canvas::GetVersion()
{
  return "2.1";
}

const std::vector<std::string> ribi::Canvas::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2008-xx-xx: version 1.0: initial C++ Builder version");
  v.push_back("2013-08-21: version 2.0: port to C++11 under Qt Creator");
  v.push_back("2013-08-22: version 2.1: allow two color and coordinat systems");
  return v;
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
  const double maxVal = MaxElement(v);
  assert(minVal != maxVal);

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
const std::vector<char> ribi::Canvas::GetAsciiArtGradient()
{
  std::vector<char> chars;
  chars.push_back('M');
  chars.push_back('N');
  chars.push_back('m');
  chars.push_back('d');
  chars.push_back('h');
  chars.push_back('y');
  chars.push_back('s');
  chars.push_back('o');
  chars.push_back('+');
  chars.push_back('/');
  chars.push_back(':');
  chars.push_back('-');
  chars.push_back('.');
  chars.push_back('`');
  chars.push_back(' ');
  return chars;
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
