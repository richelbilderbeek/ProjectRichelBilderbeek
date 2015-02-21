//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#ifndef BOENKENCONTROLS_H
#define BOENKENCONTROLS_H

#include <string>
#include <vector>

namespace ribi {

namespace Boenken {

///Controls contains the control keys
///and the players' names
///Controls is created by DialogControls
struct Controls
{
  std::vector<int> m_keys_accel;
  std::vector<int> m_keys_turn;
  std::vector<std::string> m_names;
};

} //~namespace Boenken

} //~namespace ribi

#endif // BOENKENCONTROLS_H
