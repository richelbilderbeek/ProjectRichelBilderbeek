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
#ifndef RAINBOW_H
#define RAINBOW_H

#include <string>
#include <vector>

namespace ribi {

struct Rainbow
{
  ///Obtain the RGB values from a relative position
  static void GetRgb(
    const double x,
    double& r,
    double& g,
    double& b) noexcept;

  ///Obtain this class its version
  static const std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace ribi

#endif // RAINBOW_H
