//---------------------------------------------------------------------------
/*
  DotMatrix, tool to demonstrate dot-matrix text drawing
  Copyright (C) 2009  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitDotMatrixH
#define UnitDotMatrixH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <boost/array.hpp>
namespace Extctrls { class TImage; }
//---------------------------------------------------------------------------
//Dot-matrix characters are
//size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
//size 6 (width) x 8 (height) pixels, including empty spacer pixels
void DotMatrix(
  Extctrls::TImage * const image,
  const int x_co,
  const int y_co,
  const char c);
//---------------------------------------------------------------------------
//Dot-matrix characters are
//size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
//size 6 (width) x 8 (height) pixels, including empty spacer pixels
void DotMatrix(
  Extctrls::TImage * const image,
  const int x_co,
  const int y_co,
  const std::string& s);
//---------------------------------------------------------------------------
//Dot-matrix characters are
//size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
//size 6 (width) x 8 (height) pixels, including empty spacer pixels
void DotMatrix(
  Extctrls::TImage * const image,
  const int x_co,
  const int y_co,
  const std::vector<std::string>& v);
//---------------------------------------------------------------------------
//Dot-matrix characters are
//size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
//size 6 (width) x 8 (height) pixels, including empty spacer pixels
const boost::array<boost::array<int,5> ,7> GetMatrix(const char c);
//---------------------------------------------------------------------------
//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  Extctrls::TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
//Set a line of pixels' RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  Extctrls::TImage * const image,
  const int x1,
  const int x2,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
//Set a square of pixels' RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  Extctrls::TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------

#endif
