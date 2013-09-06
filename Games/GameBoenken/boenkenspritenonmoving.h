//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2012 Richel Bilderbeek

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
#ifndef BOENKENSPRITENONMOVING_H
#define BOENKENSPRITENONMOVING_H

#include <boost/checked_delete.hpp>

#include "boenkensprite.h"

namespace ribi {

namespace Boenken {

struct SpriteMoving;

///SpriteNonMoving are obstacles.
///Obstacles are grey per default
///and can only be deleted by boost::checked_delete
struct SpriteNonMoving : public Sprite
{
  SpriteNonMoving(
    const double x,
    const double y,
    const int size = 32,
    const unsigned char r = 255,
    const unsigned char g = 255,
    const unsigned char b = 255)
    : Sprite(x,y,size,r,g,b)
  {

  }

  public:
  void setX(const double x) { m_x = x; }
  void setY(const double y) { m_y = y; }
  static void Collision(SpriteNonMoving * const p1, SpriteMoving * const p2);

  ///SpriteNonMoving is no base class
  void dummy_make_me_abstract() const {}

  private:
  ///Ensure SpriteNonMoving can only be deleted by boost::checked_delete
  virtual ~SpriteNonMoving() {}
  friend void boost::checked_delete<>(SpriteNonMoving* x);
};

} //~namespace Boenken

} //~namespace ribi

#endif // BOENKENSPRITENONMOVING_H
