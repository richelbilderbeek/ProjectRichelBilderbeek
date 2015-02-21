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
#ifndef BOENKENSPRITEBALL_H
#define BOENKENSPRITEBALL_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/checked_delete.hpp>
#include "qtboenkenspritemoving.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Boenken {

///SpriteBall is green per default
///and keeps track of the score
///and can only be deleted by boost::checked_delete
struct SpriteBall final : public SpriteMoving
{
  SpriteBall(
    const double x,
    const double y,
    const int size = 32,
    const unsigned char r =   0,
    const unsigned char g = 255,
    const unsigned char b =   0);
  void Move() noexcept;
  static void SetGoalPoles(const double goal_y_top,const double goal_y_bottom);
  static std::pair<int,int> GetScore() noexcept;
  static void ResetScore() noexcept { m_score_left = 0; m_score_right = 0; }
  static int CountBalls() noexcept { return sm_n_balls; }

  private:
  ///Ensure SpriteBall can only be deleted by boost::checked_delete
  ~SpriteBall() noexcept;
  friend void boost::checked_delete<>(SpriteBall* x);

  static double m_goal_y_top;
  static double m_goal_y_bottom;
  static int m_score_left;
  static int m_score_right;

  //The number of balls, for debugging purposes
  static int sm_n_balls;


};

} //~namespace Boenken {

} //~namespace ribi

#endif // BOENKENSPRITEBALL_H
