//---------------------------------------------------------------------------
/*
  Secret Message, tool to add secret messages to images
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
#ifndef UnitFunctionsH
#define UnitFunctionsH
//---------------------------------------------------------------------------
#include <ExtCtrls.hpp>
namespace Extctrls { struct TImage; }
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAddMessageRed.htm
void AddMessageRed(
  const Extctrls::TImage * const original,
  const Extctrls::TImage * const message,
  Extctrls::TImage * const result);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppExtractMessageRed.htm
void ExtractMessageRed(
  const Extctrls::TImage * const original,
  Extctrls::TImage * const result);
//---------------------------------------------------------------------------
//Get a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
void GetPixel(
  const Extctrls::TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
//---------------------------------------------------------------------------
//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppSetPixel.htm
void SetPixel(
  Extctrls::TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
const bool IsWhite(const Extctrls::TImage * const image, const int x, const int y);
//---------------------------------------------------------------------------
#endif
