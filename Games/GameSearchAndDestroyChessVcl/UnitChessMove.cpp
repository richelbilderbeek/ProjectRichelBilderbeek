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
#pragma hdrstop

#include "UnitChessMove.h"
//---------------------------------------------------------------------------
const bool operator==(const ChessMove& lhs, const ChessMove& rhs)
{
  return (lhs.type == rhs.type
    && lhs.x1      == rhs.x1
    && lhs.y1      == rhs.y1
    && lhs.capture == rhs.capture
    && lhs.x2      == rhs.x2
    && lhs.y2      == rhs.y2);
}

#pragma package(smart_init)
