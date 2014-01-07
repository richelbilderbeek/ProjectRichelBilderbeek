//---------------------------------------------------------------------------
/*
AsciiArter, class to convert greyscale to ASCII art
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
//From http://www.richelbilderbeek.nl/CppAsciiArter.htm
//---------------------------------------------------------------------------
#ifndef ASCIIARTER_H
#define ASCIIARTER_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/tuple/tuple.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///AsciiArter converts a matrix of grey tints
///to ASCII art
struct AsciiArter
{
  typedef std::vector<int> Pixel;
  static const std::vector<std::string> ImageToAscii(
    const std::vector<std::vector<double> >& image,
    const int width);

  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;

  private:
  //static const std::vector<char> m_gradient;
  //static const std::vector<char> GetAsciiArtGradient();

  //Get a pixel's greyness
  static double GetGreyness(
    const std::vector<std::vector<double> >& image,
    const int x,
    const int y);

  //Get a line of pixels' average greyness
  static double GetGreyness(
    const std::vector<std::vector<double> >& image,
    const int x1,
    const int x2,
    const int y);

  //Get a square of pixels' average greyness
  static double GetGreyness(
    const std::vector<std::vector<double> >& image,
    const int x1,
    const int y1,
    const int x2,
    const int y2);

  static double GetFractionGrey(
    const std::vector<std::vector<double> >& image,
    const int x1,
    const int y1,
    const int x2,
    const int y2);
};

} //~namespace ribi

#endif // ASCIIARTER_H
