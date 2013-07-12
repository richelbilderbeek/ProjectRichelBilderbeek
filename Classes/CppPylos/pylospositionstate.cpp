//---------------------------------------------------------------------------
/*
Pylos::PositionState, Pylos enum class for the state of a position
Copyright (C) 2010-2012 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPylos.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pylospositionstate.h"

#include <cassert>
#include <stdexcept>

#include "pylosplayer.h"

namespace Pylos {

char ToChar(const PositionState state)
{
  switch (state)
  {
    case PositionState::empty: return '.';
    case PositionState::player1: return 'X';
    case PositionState::player2: return 'O';
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown PositionState in ToChar");
}

PositionState ToPositionState(const Player& player)
{
  switch (player)
  {
    case Player::player1: return PositionState::player1;
    case Player::player2: return PositionState::player2;
    //default: break;
  }
  assert(!"Should not get here");
  throw std::logic_error("Cannot convert this Player to a PositionState");
}

bool operator==(const PositionState state, const Player& player)
{
  return player == state;
}

bool operator!=(const PositionState state, const Player& player)
{
  return player != state;
}

} //~namespace Pylos

