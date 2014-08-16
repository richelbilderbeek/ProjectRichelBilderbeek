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
#include <iostream>
#pragma hdrstop

#include "UnitChessPiece.h"
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const ChessPiece& piece)
{
  if (piece.IsNull()==true)
  {
    os << "  ";
  }
  else
  {
    os << piece.GetColor() << piece.GetType();
  }
  return os;
}
//---------------------------------------------------------------------------
const bool operator==(const ChessPiece& lhs, const ChessPiece& rhs)
{
  return (lhs.GetType() == rhs.GetType()
    && lhs.GetColor() == rhs.GetColor()
    && lhs.IsNull() == rhs.IsNull() );
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
