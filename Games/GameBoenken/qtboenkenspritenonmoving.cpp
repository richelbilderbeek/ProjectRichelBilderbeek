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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtboenkenspritenonmoving.h"

#include <cassert>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>
#include "qtboenkenspritemoving.h"
#include "testtimer.h"

#pragma GCC diagnostic pop

ribi::Boenken::SpriteNonMoving::SpriteNonMoving(
  const double x,
  const double y,
  const int size,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b)
  : Sprite(x,y,size,r,g,b)
{
  #ifndef NDEBUG
  SpriteNonMoving::Test();
  #endif
}

void ribi::Boenken::SpriteNonMoving::Collision(SpriteNonMoving * const p1, SpriteMoving * const p2)
{
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
    //Obtain the moving sprite's current impulse
    double p2_a = p2->CalcImpulseAngle();
    double p2_s = p2->CalcImpulseSpeed();
    //Obstacles have opposite impulse
    const double pi = boost::math::constants::pi<double>();
    double p1_a = p2_a + pi;
    double p1_s = p1_s;
    //Obtain the new impulses
    DoPerfectElasticCollision(a, p1_a,p1_s,p2_a,p2_s);
    //Set the player's new impulse
    const double dx2 =  std::sin(p2_a) * p2_s;
    const double dy2 = -std::cos(p2_a) * p2_s;
    p2->SetSpeed(dx2,dy2);
    //Let the player move away from each perpendicalar to the collision axis
    {
      const double go_away_distance = collision_distance - distance;
      assert(go_away_distance > 0);
      const double go_away_dx2 =  std::sin(a +  0.0) * (go_away_distance / 2.0);
      const double go_away_dy2 = -std::cos(a +  0.0) * (go_away_distance / 2.0);
      p2->Move(go_away_dx2,go_away_dy2);
    }
    //Let the player move again
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

void ribi::Boenken::SpriteNonMoving::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  assert(!"Test for correct bouncing of balls with obstacles");
}
