//---------------------------------------------------------------------------
/*
pylos::Player, Pylos enum class for the players
Copyright (C) 2010-2015 Richel Bilderbeek

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


#include "pylosplayer.h"

#include <cassert>
#include <stdexcept>

#include "pylospositionstate.h"



void ribi::pylos::Toggle(Player& player)
{
  player = (player == Player::player1 ? Player::player2 : Player::player1);
}

ribi::pylos::Player ribi::pylos::ToPlayer(const PositionState& state)
{
  switch (state)
  {
    case PositionState::player1: return Player::player1;
    case PositionState::player2: return Player::player2;
    default: break;
  }
  assert(!"Should not get here");
  throw std::logic_error("Cannot convert this PositionState to a Player");
}

bool ribi::pylos::operator==(const Player& player, const PositionState& state)
{
  switch (player)
  {
    case Player::player1: return state == PositionState::player1;
    case Player::player2: return state == PositionState::player2;
  }
  return false;
}

bool ribi::pylos::operator!=(const Player& player, const PositionState& state)
{
  return !(player==state);
}
