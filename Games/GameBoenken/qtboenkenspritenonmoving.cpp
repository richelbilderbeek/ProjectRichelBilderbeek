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
#include "qtboenkenspritenonmoving.h"

#include <cassert>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>
#include "geometry.h"
#include "qtboenkenspritemoving.h"
#include "qtboenkenspriteplayer.h"
#include "testtimer.h"
#include "trace.h"

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

void ribi::Boenken::SpriteNonMoving::Collision(
  const SpriteNonMoving &obstacle, SpriteMoving &moving
)
{
  if (!Sprite::IsCollision(obstacle,moving)) return;
  /*

    O     -
          |
          | dy (in this case > 0)
          |
        M -
    |---|
      dx (in this case > 0)
  */
  const double dx = moving.getX() - obstacle.getX();
  const double dy = moving.getY() - obstacle.getY();
  #ifndef NDEBUG
  const double distance = Geometry().GetDistance(dx,dy);
  #endif
  //const double collision_distance
  //  = boost::numeric_cast<double>(obstacle.m_size + moving.m_size) / 2.0;
  //Obtain the relative angle between the players

  /*

    O
     \
      \
       \
        M

  angle_players in this case 135 degrees

  */
  const double angle_players = Geometry().GetAngleClockScreen(dx,dy);

  //Obtain the moving sprite's current impulse
  double moving_angle = moving.CalcImpulseAngle();
  double moving_speed = moving.CalcImpulseSpeed();
  //Obstacles have opposite impulse
  const double pi = boost::math::constants::pi<double>();
  double obstacle_angle = moving_angle + pi;
  double obstancle_speed = moving_speed;
  //Obtain the new impulses
  DoPerfectElasticCollision(angle_players, obstacle_angle,obstancle_speed,moving_angle,moving_speed);
  //Set the player's new impulse
  const double dx2 =  std::sin(moving_angle) * moving_speed;
  const double dy2 = -std::cos(moving_angle) * moving_speed;
  moving.SetSpeed(dx2,dy2);
    //Let the player move away from each perpendicalar to the collision axis
  /*
  {
    const double go_away_distance = collision_distance - distance;
    assert(go_away_distance > 0);
    const double go_away_dx2 =  std::sin(angle_players +  0.0) * (go_away_distance / 2.0);
    const double go_away_dy2 = -std::cos(angle_players +  0.0) * (go_away_distance / 2.0);
    moving.Move(go_away_dx2,go_away_dy2);
  }
  */
  //Let the player move again
  moving.Move();
  #ifndef NDEBUG
  {
    const double new_dx = moving.getX() - obstacle.getX();
    const double new_dy = moving.getY() - obstacle.getY();
    const double new_distance = Geometry().GetDistance(new_dx,new_dy);
    if (new_distance < distance)
    {
      std::clog << "Players should in general move away after a collision\n";
    }
    assert(new_distance > distance && "Players should move away after a collision");
  }
  #endif
}

#ifndef NDEBUG
void ribi::Boenken::SpriteNonMoving::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const double obstacle_x = 160.0;
  const double obstacle_y = 100.0;
  const SpriteNonMoving obstacle(
    obstacle_x, //x
    obstacle_y, //y
    32   //size
  );
  SpritePlayer player(
    obstacle_x, //x
    obstacle_y, //y
    0.0, //angle
    32,  //size
    255, //r
    255, //g
    255  //b
  );
  // Player below obstacle, moves up
  {
    player.SetX(obstacle_x);
    player.SetY(obstacle_y + 30.0);
    player.SetSpeed(0.0,-4.0);
    assert(player.GetDeltaY() < -3.99);
    assert(IsCollision(obstacle,player));
    SpriteNonMoving::Collision(obstacle,player);
    assert(player.GetDeltaY() > 1.0 && "Be gentle, due to friction");
  }
  // Player right of obstacle, moves left
  {
    player.SetX(obstacle_x + 30.0);
    player.SetY(obstacle_y + 0.0);
    player.SetSpeed(-4.0,0.0);
    assert(player.GetDeltaX() < -3.99);
    assert(IsCollision(obstacle,player));
    SpriteNonMoving::Collision(obstacle,player);
    assert(player.GetDeltaX() > 1.0 && "Be gentle, due to friction");
  }

  // Player above obstacle, moves down
  {
    player.SetX(obstacle_x + 0.0);
    player.SetY(obstacle_y - 30.0);
    player.SetSpeed(0.0,4.0);
    assert(player.GetDeltaY() > 3.99);
    assert(IsCollision(obstacle,player));
    SpriteNonMoving::Collision(obstacle,player);
    assert(player.GetDeltaY() < -1.0 && "Be gentle, due to friction");
  }
  // Player left of obstacle, moves right
  {
    player.SetX(obstacle_x - 30.0);
    player.SetY(obstacle_y + 0.0);
    player.SetSpeed(4.0,0.0);
    assert(player.GetDeltaX() >  3.99);
    assert(IsCollision(obstacle,player));
    SpriteNonMoving::Collision(obstacle,player);
    assert(player.GetDeltaX() < -1.0 && "Be gentle, due to friction");
  }
}
#endif // NDEBUG
