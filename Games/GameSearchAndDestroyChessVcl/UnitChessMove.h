//---------------------------------------------------------------------------
/*
  SearchAndDestroyChess 2, Kriegspiel/Dark Chess game
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
#ifndef UnitChessMoveH
#define UnitChessMoveH
//---------------------------------------------------------------------------
#include "UnitEnumChessPieceType.h"
//---------------------------------------------------------------------------
struct ChessMove
{
  ChessMove(
    const EnumChessPieceType anyType = king,
    const int anyX1 = 0,
    const int anyY1 = 0,
    const bool anyCapture = true,
    const int anyX2 = 0,
    const int anyY2 = 0)
    : type(anyType),
      x1(anyX1),
      y1(anyY1),
      capture(anyCapture),
      x2(anyX2),
      y2(anyY2)
  {

  }
  EnumChessPieceType type;
  int x1;
  int y1;
  bool capture;
  int x2;
  int y2;
};
//---------------------------------------------------------------------------
const bool operator==(const ChessMove& lhs, const ChessMove& rhs);
#endif
