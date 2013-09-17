//---------------------------------------------------------------------------
/*
  SearchAndDestroyChess 2, Kriegspiel/Dark Chess game
  Copyright (C) 2008  Rich�l Bilderbeek

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
#include <cassert>
#include <stdexcept>
#pragma hdrstop

#include "UnitEnumChessPieceType.h"
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const EnumChessPieceType& type)
{
  switch (type)
  {
    case pawn  : os << "P"; return os;
    case knight: os << "N"; return os;
    case bishop: os << "B"; return os;
    case rook  : os << "R"; return os;
    case queen : os << "Q"; return os;
    case king  : os << "K"; return os;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown color");
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
