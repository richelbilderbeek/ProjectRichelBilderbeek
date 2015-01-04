//---------------------------------------------------------------------------
/*
pylos::MustRemoveState, Pylos enum class for the state of a removal
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


#include "pylosmustremovestate.h"

#include <cassert>
#include <stdexcept>

#include "pylosplayer.h"



ribi::pylos::MustRemoveState ribi::pylos::ToMustRemoveState(const Player& player)
{
  switch (player)
  {
    case Player::player1: return MustRemoveState::player1;
    case Player::player2: return MustRemoveState::player2;
  }
  assert(!"Unknown value for Player");
  throw std::logic_error("Unknown value for Player");
}

std::string ribi::pylos::ToStr(const MustRemoveState state)
{
  switch (state)
  {
    case MustRemoveState::player1: return "player1";
    case MustRemoveState::player2: return "player2";
    case MustRemoveState::no: return "no";
  }
  assert(!"Unknown value for MustRemoveState");
  throw std::logic_error("Unknown value for MustRemoveState");
}

bool ribi::pylos::operator!(const MustRemoveState& state)
{
  return state == MustRemoveState::no;
}
