
/*
Rainbow, class for a rainbow color gradient
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

//From http://www.richelbilderbeek.nl/CppRainbow.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "rainbow.h"

#include <cassert>
#include <cmath>

//Terrible #define, but my crosscompiler cannot find the definition of M_PI in cmath.h :-(
#ifndef M_PI
# define M_PI		3.14159265358979323846	/* pi */
#endif

void Rainbow::GetRgb(
  const double x,
  double& r,
  double& g,
  double& b)
{
  if (x <= 0.0 || x >= 1.0) { r = g = b = 0.0; return; }

  const double f_r = std::max(0.0,
    (x < 0.5
    ? std::cos(x * 1.5 * M_PI)
    : -std::sin(x * 1.5 * M_PI)
    ) );
  const double f_g = std::max(0.0, std::sin( x * 1.5 * M_PI ) );
  const double f_b = std::max(0.0, -std::cos( x * 1.5 * M_PI ) );
  const double max = std::max(f_r, std::max(f_g,f_b));
  assert(max!=0.0);

  r = f_r / max;
  g = f_g / max;
  b = f_b / max;
}

const std::string Rainbow::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> Rainbow::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-08-31: Version 1.0: initial version");
  v.push_back("2011-09-22: Version 1.1: added infrared and ultraviolet");
  return v;
}

