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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtboenkenspritemoving.h"

#include <cassert>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include "geometry.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

int ribi::Boenken::SpriteMoving::sm_n_moving_sprites = 0;

///The fraction of impulse that is conserved \n
///1.0: no friction
///0.9: some friction
///0.1: much friction
double ribi::Boenken::SpriteMoving::m_friction = 0.995;

ribi::Boenken::SpriteMoving::SpriteMoving(
  const double x,
  const double y,
  const int size,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b)
  : Sprite(x,y,size,r,g,b),
    m_dx{0.0},
    m_dy{0.0}
{
  ++sm_n_moving_sprites;
}

ribi::Boenken::SpriteMoving::~SpriteMoving()
{
  --sm_n_moving_sprites;
}

double ribi::Boenken::SpriteMoving::CalcImpulseAngle() const noexcept
{
  return Geometry().GetAngleClockScreen(m_dx,m_dy);
}

double ribi::Boenken::SpriteMoving::CalcImpulseSpeed() const noexcept
{

  return Geometry().GetDistance(m_dx,m_dy);
}

void ribi::Boenken::SpriteMoving::SetFriction(const double friction)
{
  assert(friction  > 0.0);
  assert(friction <= 1.0);
  m_friction = friction;
}

void ribi::Boenken::SpriteMoving::Collision(SpriteMoving * const p1, SpriteMoving * const p2)
{
  assert(p1!=p2);
  assert(p1 > p2);
  const double dx = p2->getX() - p1->getX();
  const double dy = p2->getY() - p1->getY();
  const double distance = std::sqrt((dy * dy) + (dx * dx));
  const double collision_distance
    = boost::numeric_cast<double>(p1->m_size + p2->m_size) / 2.0;
  if (distance < collision_distance)
  {
    //A collision!
    //Obtain the relative angle between the players
    const double a = GetAngle(dx,dy);
    //Obtain the players' current impulses
    double p1_a = p1->CalcImpulseAngle();
    double p1_s = p1->CalcImpulseSpeed();
    double p2_a = p2->CalcImpulseAngle();
    double p2_s = p2->CalcImpulseSpeed();
    //Obtain the new impulses
    DoPerfectElasticCollision(a, p1_a,p1_s,p2_a,p2_s);
    //Set the players' new impulses
    const double dx1 =  std::sin(p1_a) * p1_s;
    const double dy1 = -std::cos(p1_a) * p1_s;
    const double dx2 =  std::sin(p2_a) * p2_s;
    const double dy2 = -std::cos(p2_a) * p2_s;
    p1->SetSpeed(dx1,dy1);
    p2->SetSpeed(dx2,dy2);
    //std::clog << "New impulses: (" << dx1 << "," << dy1 << ")"
    //  << " (" << dx2 << "," << dy2 << ")\n";
    //Let them move away from each perpendicalar to the collision axis
    {
      const double go_away_distance = collision_distance - distance;
      assert(go_away_distance > 0);
      const double pi = boost::math::constants::pi<double>();
      const double go_away_dx1 =  std::sin(a + pi) * (go_away_distance / 2.0);
      const double go_away_dy1 = -std::cos(a + pi) * (go_away_distance / 2.0);
      const double go_away_dx2 =  std::sin(a + 0.0) * (go_away_distance / 2.0);
      const double go_away_dy2 = -std::cos(a + 0.0) * (go_away_distance / 2.0);
      p1->Move(go_away_dx1,go_away_dy1);
      p2->Move(go_away_dx2,go_away_dy2);
    }
    //Let the players move again
    p1->Move();
    p2->Move();
    #ifndef NDEBUG
    {
      const double new_dx = p2->getX() - p1->getX();
      const double new_dy = p2->getY() - p1->getY();
      const double new_distance = std::sqrt((new_dy * new_dy) + (new_dx * new_dx));
      if (new_distance < distance)
      {
        //std::clog << "Players should in general move away after a collision\n";
      }
      //assert(new_distance > distance && "Players should move away after a collision");
    }
    #endif
  }
}

void ribi::Boenken::SpriteMoving::Draw(QPainter& painter) const
{
  //Draw the globe
  Sprite::Draw(painter);
  #ifdef DRAW_MOVING_SPRITE_IMPULSES
  //Determine the player center
  const double half_size = boost::numeric_cast<double>(m_size) / 2.0;
  const double x_mid = m_x + half_size;
  const double y_mid = m_y + half_size;
  //Draw the moving sprite's impulse
  const double x3 = x_mid + (std::sin(CalcImpulseAngle()) * CalcImpulseSpeed() * 10.0);
  const double y3 = y_mid - (std::cos(CalcImpulseAngle()) * CalcImpulseSpeed() * 10.0);
  painter.drawLine(x_mid,y_mid,x3,y3);
  #endif
}
