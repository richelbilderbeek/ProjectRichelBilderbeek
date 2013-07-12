
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

//From http://www.richelbilderbeek.nl/GameBoenken.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "boenkenspriteplayer.h"

#include <cassert>
#include <cmath>

//Terrible #define, but my crosscompiler cannot find the definition of M_PI in cmath.h :-(
#ifndef M_PI
# define M_PI		3.14159265358979323846	/* pi */
#endif

#include <boost/numeric/conversion/cast.hpp>

#include <QPainter>


namespace Boenken {

///The acceleration (i.e. change of impulse)
///if a player presses accelerate
const double SpritePlayer::m_acceleration = 1.0;

///The speed of turning around
///if a player presses turn
const double SpritePlayer::m_turnspeed = M_PI / 10.0;

///The number of SpritePlayers.
///for debugging purposes
int SpritePlayer::ms_n_players = 0;

SpritePlayer::SpritePlayer(
  const double x,
  const double y,
  const double angle,
  const int size,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b)
  : SpriteMoving(x,y,size,r,g,b),
    m_id(ms_n_players),
    m_angle(angle)

{
  ++ms_n_players;
  //std::clog << "The " << ms_n_players
  //  << "th player is created at ("
  //  << this->getX() << ","
  //  << this->getY() << ")\n";
}

SpritePlayer::~SpritePlayer()
{
  //std::clog << "The " << ms_n_players
  //  << "th player is destroyed\n";
  --ms_n_players;
  assert(ms_n_players >= 0);
}

void SpritePlayer::Move()
{
  ///Move the sprite
  m_x += m_dx;
  m_y += m_dy;

  ///Calculate the sprites maximal coordinats
  const double maxx = this->m_maxx - this->m_size;
  const double maxy = this->m_maxy - this->m_size;
  assert(maxx > 0);
  assert(maxy > 0);

  ///Move moving sprite into the arena
  if (m_x <  0.0)
  {
    m_x =  0.0; m_dx =  std::fabs(m_dx);
    //std::clog << "Player #" << m_id << " moved to right to ("
    //  << m_x << "," << m_y << ")\n";
  }
  if (m_y <  0.0)
  {
    m_y =  0.0; m_dy =  std::fabs(m_dy);
    //std::clog << "Player #" << m_id << " moved downwards to ("
    //  << m_x << "," << m_y << ")\n";
  }
  if (m_x > maxx)
  {
    m_x = maxx; m_dx = -std::fabs(m_dx);
    //std::clog << "Player #" << m_id << " moved to left to ("
    //  << m_x << "," << m_y << ")\n";
  }
  if (m_y > maxy)
  {
    m_y = maxy; m_dy = -std::fabs(m_dy);
    //std::clog << "Player #" << m_id << " moved upwards to ("
    //  << m_x << "," << m_y << ")\n";
  }

  ///Decrease the speed due to friction
  m_dx *= m_friction;
  m_dy *= m_friction;
}


void SpritePlayer::Accelerate()
{
  m_dx += (std::sin(m_angle) * m_acceleration);
  m_dy -= (std::cos(m_angle) * m_acceleration);
}

void SpritePlayer::TurnRight()
{
  m_angle+=m_turnspeed;
}

void SpritePlayer::Draw(QPainter& painter) const
{
  //Draw the globe and possibly impulse
  SpriteMoving::Draw(painter);
  //Determine the player center
  const double half_size = boost::numeric_cast<double>(m_size) / 2.0;
  const double x_mid = m_x + half_size;
  const double y_mid = m_y + half_size;
  //Draw the line the player looks at
  const double x2 = x_mid + (std::sin(m_angle) * half_size);
  const double y2 = y_mid - (std::cos(m_angle) * half_size);
  painter.drawLine(x_mid,y_mid,x2,y2);
}

} //~namespace Boenken

