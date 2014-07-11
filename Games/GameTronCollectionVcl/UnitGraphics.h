//---------------------------------------------------------------------------
/*
  The Tron Collection, three simple tron games
  Copyright (C) 2008  Richel Bilderbeek

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
#ifndef UnitGraphicsH
#define UnitGraphicsH
//---------------------------------------------------------------------------
namespace Extctrls { class TImage; }
#include <Graphics.hpp>
//---------------------------------------------------------------------------


void DrawGlobePlus(Extctrls::TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
void DrawGlobeMinus(Extctrls::TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
void DrawGlobe(
  Extctrls::TImage * const image,
  const unsigned char rMax,
  const unsigned char gMax,
  const unsigned char bMax);
void Rainbow(
  const double x,
  unsigned char& r,
  unsigned char& g,
  unsigned char& b);
const TColor RgbToColor(
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );

const unsigned char GetRed(const double x);
const unsigned char GetGreen(const double x);
const unsigned char GetBlue(const double x);


void GetPixel(
  const Extctrls::TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
const TColor GetPixelVcl(
  const Extctrls::TImage * const image,
  const int x,
  const int y);
void SetPixel(
  Extctrls::TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
void SetPixel(
  Extctrls::TImage * const image,
  const int x,
  const int y,
  const TColor color);
void PaintVcl(Extctrls::TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );
void PaintVcl(Extctrls::TImage * const image, const TColor color);
void RemoveColor(Extctrls::TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );
void RemoveColor(Extctrls::TImage * const image, const TColor color);
const TColor RgbToColor(
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );



#endif
