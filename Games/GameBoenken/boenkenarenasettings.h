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
#ifndef BOENKENARENASETTINGS_H
#define BOENKENARENASETTINGS_H

#include <utility>

namespace ribi {

namespace Boenken {

enum Formation
{
  straight_line,
  circle_inward,
  circle_outward
};

///ArenaSettings holds the parameters set in DialogArena
struct ArenaSettings
{
  std::pair<int,int> screen_size;
  int width() const { return screen_size.first; }
  int height() const { return screen_size.second; }
  int n_balls;
  int n_obstacles;
  Formation formation;
  double friction;
};

} //~namespace Boenken

} //~namespace ribi

#endif // BOENKENARENASETTINGS_H
