//---------------------------------------------------------------------------
/*
Rainbow, class for a rainbow color gradient
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
//From http://www.richelbilderbeek.nl/CppRainbow.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "rainbow.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>
#pragma GCC diagnostic pop

void ribi::Rainbow::GetRgb(
  const double x,
  double& r,
  double& g,
  double& b) noexcept
{
  const double pi = boost::math::constants::pi<double>();

  if (x <= 0.0 || x >= 1.0) { r = g = b = 0.0; return; }

  const double f_r = std::max(0.0,
    (x < 0.5
    ? std::cos(x * 1.5 * pi)
    : -std::sin(x * 1.5 * pi)
    ) );
  const double f_g = std::max(0.0,  std::sin( x * 1.5 * pi ));
  const double f_b = std::max(0.0, -std::cos( x * 1.5 * pi ));
  const double max = std::max(f_r,  std::max(f_g,f_b       ));
  assert(max!=0.0);

  r = f_r / max;
  g = f_g / max;
  b = f_b / max;
}

std::string ribi::Rainbow::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Rainbow::GetVersionHistory() noexcept
{
  return {
    "2011-08-31: Version 1.0: initial version",
    "2011-09-22: Version 1.1: added infrared and ultraviolet"
  };
}

