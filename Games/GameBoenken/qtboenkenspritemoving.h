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
#ifndef BOENKENSPRITEMOVING_H
#define BOENKENSPRITEMOVING_H

#include "qtboenkensprite.h"

namespace ribi {

namespace Boenken {

///SpriteMoving is an abstract base class
struct SpriteMoving: public Sprite
{
  SpriteMoving(
    const double x,
    const double y,
    const int size,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b);
  virtual ~SpriteMoving();

  double CalcImpulseAngle() const noexcept;
  double CalcImpulseSpeed() const noexcept;
  virtual void Draw(QPainter& painter) const override;
  double GetDeltaX() const noexcept { return m_dx; }
  double GetDeltaY() const noexcept { return m_dy; }
  virtual void Move() = 0;
  void Move(const double dx, const double dy) { m_dx += dx; m_dy += dy; }

  //void SetDeltaX(const double dx) noexcept { m_dx = dx; }
  //void SetDeltaY(const double dy) noexcept { m_dy = dy; }
  virtual void SetSpeed(const double dx, const double dy) noexcept { m_dx = dx; m_dy = dy; }

  static void SetFriction(const double friction);
  static void Collision(SpriteMoving * const p1, SpriteMoving * const p2);

  ///Debugging purposes
  static int CountMovingSprites() noexcept { return sm_n_moving_sprites; }

  protected:
  double m_dx;
  double m_dy;
  static double m_friction;
  static int sm_n_moving_sprites;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace Boenken

} //~namespace ribi

#endif // BOENKENSPRITEMOVING_H
