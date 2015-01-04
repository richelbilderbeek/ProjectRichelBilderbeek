//---------------------------------------------------------------------------
/*
pylos::PositionState, Pylos enum class for the state of a position
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
#ifndef PYLOSPOSITIONSTATE_H
#define PYLOSPOSITIONSTATE_H

#include "pylosfwd.h"
//#include "pylosplayer.h"

namespace ribi {

namespace pylos {

enum class PositionState { player1, player2, empty };
PositionState ToPositionState(const Player& player);
char ToChar(const PositionState state);

bool operator==(const PositionState state, const Player& player);
bool operator!=(const PositionState state, const Player& player);
//bool operator!(const PositionState& state);

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSPOSITIONSTATE_H
