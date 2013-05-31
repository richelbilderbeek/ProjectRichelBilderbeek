//---------------------------------------------------------------------------
/*
GaborFilter, LED class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppGaborFilter.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "gaborfilter.h"

#include "exercise.h"
#include <cassert>
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
GaborFilter::GaborFilter(
  const double angle,
  const double frequency,
  const double sigma)
  : m_angle(angle),
    m_frequency(frequency),
    m_sigma(sigma)
{

}
//---------------------------------------------------------------------------
double GaborFilter::GaborFunction(const double x, const double y,
  const double angle, const double frequency, const double sigma)
{
  const double dx = x;
  const double dy = y;
  const double distance = std::sqrt((dx * dx) + (dy * dy));
  const double fx = std::cos(angle) * frequency;
  const double fy = std::sin(angle) * frequency;
  const double cosine = std::cos((dx * fx) + (dy * fy));
  const double gauss = std::exp( -(distance * distance) / (2.0 * sigma * sigma));
  const double z = cosine * gauss;
  return z;
}
//---------------------------------------------------------------------------
double GaborFilter::GaborFunction(const double x, const double y) const
{
  return GaborFunction(x,y,m_angle,m_frequency,m_sigma);
}
//---------------------------------------------------------------------------
const std::string GaborFilter::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> GaborFilter::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-07-08: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void GaborFilter::SetAngle(const double angle)
{
  if (angle != m_angle)
  {
    m_angle = angle;
    m_signal_changed();
  }
}
//---------------------------------------------------------------------------
void GaborFilter::SetFrequency(const double frequency)
{
  if (frequency != m_frequency)
  {
    m_frequency = frequency;
    m_signal_changed();
  }
}
//---------------------------------------------------------------------------
void GaborFilter::SetSigma(const double sigma)
{
  if (sigma != m_sigma)
  {
    m_sigma = sigma;
    m_signal_changed();
  }
}
//---------------------------------------------------------------------------
double GaborFilter::SuggestSigma(const double width, const double height) const
{
  const double s = std::sqrt( ((width*0.5)*(width*0.5)) + ((height*0.5)*(height*0.5)));
  return std::sqrt(-(s * s) / (2.0*std::log(1.0/510.0)));
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const GaborFilter& g)
{
  os
    << "<GaborFilter>"
    << "<angle>"
      << g.GetAngle()
    << "</angle>"
    << "<frequency>"
      << g.GetFrequency()
    << "</frequency>"
    << "<sigma>"
      << g.GetSigma()
    << "</sigma>"
    << "</GaborFilter>";
  return os;
}
//---------------------------------------------------------------------------
