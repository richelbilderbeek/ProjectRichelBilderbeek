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
#include "fileio.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::Canvas::Canvas()
  : m_signal_changed{}
{

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
  return "1.0";
}

const std::vector<std::string> ribi::Canvas::GetVersionHistory() noexcept
{
  return {
    "2014-01-10: version 1.0: initial version, split up from DrawCanvas"
  };
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
