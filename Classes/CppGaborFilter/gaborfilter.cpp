//---------------------------------------------------------------------------
/*
GaborFilter, Gabor filter class
Copyright (C) 2011-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "gaborfilter.h"

#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>

#pragma GCC diagnostic pop

ribi::GaborFilter::GaborFilter(
  const double angle,
  const double frequency,
  const double sigma)
  : m_signal_changed{},
    m_angle(angle),
    m_frequency(frequency),
    m_sigma(sigma)
{
  if (sigma == 0.0)
  {
    throw std::logic_error("Cannot set GaborFilter::sigma to zero");
  }
  assert(m_sigma != 0.0);
}

double ribi::GaborFilter::GaborFunction(const double x, const double y,
  const double angle, const double frequency, const double sigma)
{
  assert(sigma != 0.0);
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

double ribi::GaborFilter::GaborFunction(const double x, const double y) const
{
  return GaborFunction(x,y,m_angle,m_frequency,m_sigma);
}

std::string ribi::GaborFilter::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::GaborFilter::GetVersionHistory() noexcept
{
  return {
    "2012-07-08: version 1.0: initial version"
  };
}

void ribi::GaborFilter::SetAngle(const double angle) noexcept
{
  if (angle != m_angle)
  {
    m_angle = angle;
    m_signal_changed();
  }
}

void ribi::GaborFilter::SetFrequency(const double frequency)
{
  if (frequency != m_frequency)
  {
    m_frequency = frequency;
    m_signal_changed();
  }
}

void ribi::GaborFilter::SetSigma(const double sigma)
{
  if (sigma == 0.0)
  {
    throw std::logic_error("Cannot set GaborFilter::sigma to zero");
  }
  if (sigma != m_sigma)
  {
    m_sigma = sigma;
    m_signal_changed();
  }
  assert(m_sigma != 0.0);
}

double ribi::GaborFilter::SuggestSigma(const double width, const double height) const
{
  const double s = std::sqrt( ((width*0.5)*(width*0.5)) + ((height*0.5)*(height*0.5)));
  return std::sqrt(-(s * s) / (2.0*std::log(1.0/510.0)));
}

std::ostream& ribi::operator<<(std::ostream& os, const GaborFilter& g) noexcept
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

