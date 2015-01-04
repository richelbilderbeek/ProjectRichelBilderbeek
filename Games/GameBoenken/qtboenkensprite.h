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
  explicit Sprite(
    const double x,
    const double y,
    const int size,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b);
  Sprite(const Sprite&) = delete;
  Sprite& operator=(const Sprite&) = delete;
  virtual ~Sprite() = default;

  ///The size (width==height) in pixels
  const int m_size;

  ///The globe part of the Sprite
  const QPixmap m_pixmap;

  double getX() const noexcept { return GetX(); }
  double getY() const noexcept { return GetY(); }
  double GetX() const noexcept { return m_x; }
  double GetY() const noexcept { return m_y; }

  ///The x,y,w,h of the sprite
  QRect rect() const;

  const QPixmap& pixmap() const noexcept;

  ///Every sprite must be drawn to the screen
  virtual void Draw(QPainter& painter) const;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  static bool IsCollision(const Sprite& p1, const Sprite& p2) noexcept;

  ///Sets the arena size,
  ///that is Sprite::m_maxx and Sprite::m_maxy.
  ///SpriteBall::SetGoalPoles defines the vertical
  ///range of the goal posts
  ///Every sprite must be within the arena
  static void setArenaSize(const int width, const int height);

  void setX(const double x) noexcept { SetX(x); }
  void setY(const double y) noexcept { SetY(y); }
  void SetX(const double x) noexcept { m_x  = x; }
  void SetY(const double y) noexcept { m_y  = y; }

  protected:
  double m_x;
  double m_y;
  static int m_maxx;
  static int m_maxy;


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
