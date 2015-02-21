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
#ifndef PYLOSMUSTREMOVESTATE_H
#define PYLOSMUSTREMOVESTATE_H

#include <string>

#include "pylosfwd.h"

namespace ribi {

namespace pylos {

///After placing (Set) or moving (Transfer) a marble, the MustRemoveState
///will be removed. These are:
///- no: no marbles need to be removed before next player's move
///- player1: player1 has to remove one or two marbles. This is determined
///  by the player that places or moves his/her marbles.
///- player2: player2 has to remove one or two marbles. This is determined
///  by the player that places or moves his/her marbles.
enum class MustRemoveState { player1, player2, no };
MustRemoveState ToMustRemoveState(const Player& player);
std::string ToStr(const MustRemoveState state);

//bool operator==(const MustRemoveState& state, const MustRemoveState& player);
//bool operator!=(const MustRemoveState& state, const MustRemoveState& player);
bool operator!(const MustRemoveState& state);

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSMUSTREMOVESTATE_H
