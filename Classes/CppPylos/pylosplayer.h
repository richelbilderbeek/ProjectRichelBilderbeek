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
#ifndef PYLOSPLAYER_H
#define PYLOSPLAYER_H

#include "pylosfwd.h"
#include "pylospositionstate.h"

namespace ribi {

namespace pylos {

enum class Player { player1, player2 };
///Toggles between the two players
void Toggle(Player& player);
///Convert a PositionState to Player
Player ToPlayer(const PositionState& state);

bool operator==(const Player& player, const PositionState& state);
bool operator!=(const Player& player, const PositionState& state);

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSPLAYER_H



