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
#ifndef BOENKENSPRITEPLAYER_H
#define BOENKENSPRITEPLAYER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/checked_delete.hpp>
#include "qtboenkenspritemoving.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Boenken {

///SpritePlayer is a MovingSprite that can respond to input
///and can only be deleted by boost::checked_delete
struct SpritePlayer final : public SpriteMoving
{
  SpritePlayer(
    const double x,
    const double y,
    const double angle,
    const int size,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b
  );
  ~SpritePlayer();

  void Accelerate() noexcept;
  void Draw(QPainter& painter) const override;
  double GetAngle() const noexcept { return m_angle; }
  void Move() noexcept override;
  void SetSpeed(const double dx, const double dy) noexcept override;
  void TurnRight() noexcept;

  ///The SpritePlayer's ID
  const int m_id;

  private:
  ///Direction the player looks to
  ///Angle following the clock (0 = 12 o'clock, 0.5*pi = 3 o'clock)
  ///Note: the actual moving is done by m_dx and m_dy
  double m_angle;

  static const double m_acceleration;
  static const double m_turnspeed;
  static int ms_n_players;
};

} //~namespace Boenken

} //~namespace ribi

#endif // BOENKENSPRITEPLAYER_H
