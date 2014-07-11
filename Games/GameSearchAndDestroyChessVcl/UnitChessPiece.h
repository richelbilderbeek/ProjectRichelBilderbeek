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
#ifndef UnitChessPieceH
#define UnitChessPieceH
//---------------------------------------------------------------------------
#include <iosfwd>
#include "UnitEnumChessPieceType.h"
#include "UnitEnumChessPieceColor.h"
//---------------------------------------------------------------------------
//Read-only
struct ChessPiece
{
  ChessPiece()
    : mColor(white), mType(pawn), mIsNull(true) {}
  ChessPiece(
    const EnumChessPieceColor color,
    const EnumChessPieceType type)
    : mColor(color), mType(type), mIsNull(false) {}

  const EnumChessPieceColor GetColor() const { return mColor; }
  const EnumChessPieceType GetType() const { return mType; }
  const int IsNull() const { return mIsNull; }

  private:
    EnumChessPieceColor mColor;
    EnumChessPieceType mType;
    bool mIsNull;
};
//---------------------------------------------------------------------------
const bool operator==(const ChessPiece& lhs, const ChessPiece& rhs);
std::ostream& operator<<(std::ostream& os, const ChessPiece& piece);
//---------------------------------------------------------------------------
#endif
