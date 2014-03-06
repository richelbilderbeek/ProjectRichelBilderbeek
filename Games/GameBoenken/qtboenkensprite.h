//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2014 Richel Bilderbeek

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
#ifndef BOENKENSPRITE_H
#define BOENKENSPRITE_H

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"


#include <QPixmap>
#pragma GCC diagnostic pop

namespace ribi {

namespace Boenken {

///Sprite is the ABC of anything that must be drawn on screen
struct Sprite
{
  Sprite(
    const double x,
    const double y,
    const int size,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b);
  Sprite(const Sprite&) = delete;
  Sprite& operator=(const Sprite&) = delete;

  ///The size (width==height) in pixels
  const int m_size;

  ///The globe part of the Sprite
  const QPixmap m_pixmap;

  double getX() const noexcept { return m_x; }
  double getY() const noexcept { return m_y; }

  ///The x,y,w,h of the sprite
  QRect rect() const;

  const QPixmap& pixmap() const noexcept;

  ///Every sprite must be drawn to the screen
  virtual void Draw(QPainter& painter) const;

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Sets the arena size,
  ///that is Sprite::m_maxx and Sprite::m_maxy.
  ///SpriteBall::SetGoalPoles defines the vertical
  ///range of the goal posts
  ///Every sprite must be within the arena
  static void setArenaSize(const int width, const int height);

  ///dummy_make_me_abstract ensures that
  ///Sprite and SpriteMoving
  ///are abstract base classes
  virtual void dummy_make_me_abstract() const = 0;

  protected:
  double m_x;
  double m_y;
  static int m_maxx;
  static int m_maxy;

  //private:
  //Ensure Sprite can only be deleted by boost::checked_delete
  virtual ~Sprite() noexcept {}
  //friend void boost::checked_delete<>(Sprite* x);

  ///Draws a globe with a nice 3D effect\n
  ///From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
  static QPixmap DrawGlobe(
    const int width,
    const int height,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b);

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy) noexcept;

  ///DoPerfectElasticCollision calculates the impulses after a
  ///collision.
  ///From http://www.richelbilderbeek.nl/CppDoPerfectElasticCollision.htm
  static void DoPerfectElasticCollision(
    const double angleCollision,
    double& angle1,
    double& speed1,
    double& angle2,
    double& speed2) noexcept;

  private:
  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

};

} //~namespace Boenken

} //~namespace ribi

#endif // SPRITE_H
