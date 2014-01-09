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
#include <boost/algorithm/string/split.hpp>

#include <QString>
#include <QRegExp>

#include "canvascolorsystems.h"
#include "canvascoordinatsystems.h"
#include "dotmatrixstring.h"
#include "fileio.h"
#include "trace.h"
#include "xml.h"

#pragma GCC diagnostic pop

ribi::Canvas::Canvas(
  const int width,
  const int height,
  const CanvasColorSystem color_system,
  const CanvasCoordinatSystem coordinat_system)
  : m_signal_changed{},
    m_canvas(std::vector<std::vector<double> >(height,std::vector<double>(width,0.0))),
    m_color_system(color_system),
    m_coordinat_system(coordinat_system)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(width  > 0);
  assert(height > 0);
}

ribi::Canvas::Canvas(
  const std::vector<std::vector<double>>& canvas,
  const CanvasColorSystem color_system,
  const CanvasCoordinatSystem coordinat_system)
  : m_signal_changed{},
    m_canvas(canvas),
    m_color_system(color_system),
    m_coordinat_system(coordinat_system)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(!canvas.empty());
  assert(!canvas[0].empty());
}

ribi::Canvas::Canvas(const std::string& filename)
  : m_signal_changed{},
    m_canvas{},
    m_color_system{},
    m_coordinat_system{}
{
  assert(fileio::IsRegularFile(filename));
  std::string s;
  {
    std::ifstream f(filename.c_str());
    f >> s;
  }
  assert(s.size() >= 17);
  assert(s.substr(0,8) == std::string("<canvas>"));
  assert(s.substr(s.size() - 9,9) == std::string("</canvas>"));
  TRACE(s);
  {
    const std::vector<std::string> v { GetRegexMatches(s,QRegExp("(<color_system>.*</color_system>)")) };
    #ifndef NDEBUG
    if (v.size() != 1)
    {
      TRACE("ERROR");
      TRACE(v.size());
      TRACE(s);
    }
    #endif
    assert(v.size() == 1);
    m_color_system = CanvasColorSystems::ToType(ribi::xml::StripXmlTag(v[0]));
  }

  {
    const std::vector<std::string> v { GetRegexMatches(s,QRegExp("(<coordinat_system>.*</coordinat_system>)")) };
    assert(v.size() == 1);
    m_coordinat_system = CanvasCoordinatSystems::ToType(ribi::xml::StripXmlTag(v[0]));
  }

  {
    const std::vector<std::string> v { GetRegexMatches(s,QRegExp("(<rows>.*</rows>)")) };
    TRACE(v.size());
    assert(v.size() == 1 && "(<rows>.*</rows>) must be present exactly once");
    int i=0;
    for (std::string line: v)
    {
      TRACE(line);
      //const std::pair<std::string,std::vector<std::string>> w { xml::XmlToVector(boost::lexical_cast<std::string>(i)) };
      const std::pair<std::string,std::vector<std::string>> w { xml::XmlToVector(line) };
      //const std::string t { ribi::xml::StripXmlTag(line) };
      //const std::vector<std::string> w { SeperateString(t,' ') };
      TRACE(w.first);
      std::vector<double> x;
      std::transform(
        w.second.begin(),
        w.second.end(),
        std::back_inserter(x),
        [](const std::string u)
        {
          TRACE(u);
          return boost::lexical_cast<double>(u);
        }
      );
      TRACE(x.size());
      m_canvas.push_back(x);
      ++i;
      TRACE(i);
    }
  }
}

void ribi::Canvas::Clear() noexcept
{
  for (auto& row: m_canvas)
  {
    for (auto& cell:row)
    {
      cell = 0.0;
    }
  }

  #ifndef NDEBUG
  for (auto row: m_canvas)
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
    m_canvas[indexTop  ][indexLeft  ] += (fracLeft * fracTop);
  if (IsInRange(indexLeft+1,indexTop  ))
    m_canvas[indexTop  ][indexLeft+1] += ((1.0-fracLeft) * fracTop);
  if (IsInRange(indexLeft  ,indexTop+1))
    m_canvas[indexTop+1][indexLeft  ] += (fracLeft * (1.0-fracTop));
  if (IsInRange(indexLeft+1,indexTop+1))
    m_canvas[indexTop+1][indexLeft+1] += ((1.0-fracLeft) * (1.0-fracTop));
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

const std::vector<char> ribi::Canvas::GetAsciiArtGradient() noexcept
{
  return { 'M','N','m','d','h','y','s','o','+','/',':','-','.','`',' ' };
}

const std::vector<std::string> ribi::Canvas::GetRegexMatches(
  const std::string& s,
  const QRegExp& r_original)
{
  QRegExp r(r_original);
  r.setMinimal(true); //QRegExp must be non-greedy
  std::vector<std::string> v;
  int pos = 0;
  while ((pos = r.indexIn(s.c_str(), pos)) != -1)
  {
    const QString q = r.cap(1);
    if (q.isEmpty()) break;
    v.push_back(q.toStdString());
    pos += r.matchedLength();
  }

  return v;
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

bool ribi::Canvas::IsInRange(const int x, const int y) const
{
  if (   x < 0
      || y < 0
      || y >= static_cast<int>(m_canvas.size())
      || x >= static_cast<int>(m_canvas[y].size())
     )
    return false;
  return true;
}

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

void ribi::Canvas::Save(const std::string& filename) const noexcept
{
  std::stringstream s;
  {
    {
      std::stringstream t;
      int i=0;
      for (auto line: m_canvas)
      {
        t << xml::VectorToXml(std::string("y") + boost::lexical_cast<std::string>(i),line);
        ++i;
      }
      s << xml::ToXml("rows",t.str());
    }
    //color system
    s << xml::ToXml("color_system",CanvasColorSystems::ToStr(m_color_system));
    //coordinat system
    s << xml::ToXml("coordinat_system",CanvasCoordinatSystems::ToStr(m_coordinat_system));
  }
  {
    const std::string t = xml::ToXml("canvas",s.str());
    std::ofstream f(filename.c_str());
    f << t;
  }
  #ifndef NDEBUG
  {
    Canvas c(filename);
    assert(*this == c);
  }
  #endif
}

const std::vector<std::string> ribi::Canvas::SeperateString(
  const std::string& input,
  const char seperator) noexcept
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

void ribi::Canvas::SetColorSystem(const CanvasColorSystem colorSystem) noexcept
{
  if (this->m_color_system != colorSystem)
  {
    this->m_color_system = colorSystem;
    this->m_signal_changed(this);
  }
}

void ribi::Canvas::SetCoordinatSystem(const CanvasCoordinatSystem coordinatSystem) noexcept
{
  if (this->m_coordinat_system != coordinatSystem)
  {
    this->m_coordinat_system = coordinatSystem;
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
    const boost::shared_ptr<Canvas> canvas(new Canvas(maxx,maxy,CanvasColorSystem::invert));
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
    const boost::shared_ptr<Canvas> canvas(new Canvas(maxx,maxy,CanvasColorSystem::invert));
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
  //Draw a smiley is all coordinat- and colorsystem combinations, Clear
  for (int i=0; i!=4; ++i)
  {
    const int maxx = 79;
    const int maxy = 23;
    const boost::shared_ptr<Canvas> canvas(new Canvas(maxx,maxy));
    canvas->SetColorSystem(
      i % 2
      ? CanvasColorSystem::normal
      : CanvasColorSystem::invert);
    canvas->SetCoordinatSystem(
      i / 2
      ? CanvasCoordinatSystem::screen
      : CanvasCoordinatSystem::graph);

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
      canvas->SetColorSystem(CanvasColorSystem::invert); //Background = Black
      std::stringstream s;
      s << (*canvas);
      const std::string t { s.str() };
      TRACE(t);
      TRACE(std::count(t.begin(),t.end(),' '));
      TRACE(canvas->GetWidth());
      TRACE(canvas->GetHeight());

      assert(std::count(t.begin(),t.end(),' ') == canvas->GetWidth() * canvas->GetHeight());

    }
  }
  //Saving and loading
  {
    const int maxx = 5;
    const int maxy = 9;
    const boost::shared_ptr<Canvas> canvas(new Canvas(maxx,maxy,CanvasColorSystem::invert));
    canvas->DrawLine(-maxx,-maxy,maxx*2.0,maxy*2.0);

    const boost::shared_ptr<const Canvas> old_canvas {
      new Canvas(canvas->GetGreynesses(),canvas->GetColorSystem(),canvas->GetCoordinatSystem())
    };
    assert( old_canvas !=  canvas);
    assert(*old_canvas == *canvas);

    const std::string temp_filename { fileio::GetTempFileName() };
    canvas->Save(temp_filename);
    canvas->Clear();

    assert(*old_canvas != *canvas);

    const boost::shared_ptr<const Canvas> new_canvas {
      new Canvas(temp_filename)
    };

    assert(*old_canvas == *new_canvas);

  }
  TRACE("Finished ribi::Canvas::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const Canvas& canvas)
{
  ribi::Canvas::PlotSurface(
    os,
    canvas.m_canvas,
    canvas.m_color_system == ribi::CanvasColorSystem::normal,
    canvas.m_coordinat_system == ribi::CanvasCoordinatSystem::screen);
  return os;
}

bool ribi::operator==(const Canvas& lhs, const Canvas& rhs) noexcept
{
  return lhs.m_canvas == rhs.m_canvas
    && lhs.m_color_system == rhs.m_color_system
    && lhs.m_coordinat_system == rhs.m_coordinat_system;
}

bool ribi::operator!=(const Canvas& lhs, const Canvas& rhs) noexcept
{
  return !(lhs == rhs);
}
