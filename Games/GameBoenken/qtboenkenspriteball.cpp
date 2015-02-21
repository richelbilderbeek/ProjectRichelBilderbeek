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
#include "qtboenkenspriteball.h"

#include <cassert>

///The y-coordinat of the top goal post
double ribi::Boenken::SpriteBall::m_goal_y_top = 100.0;

///The y-coordinat of the bottom goal post
double ribi::Boenken::SpriteBall::m_goal_y_bottom = 300.0;

///The current score for the left team
int ribi::Boenken::SpriteBall::m_score_left = 0;

///The current score for the right team
int ribi::Boenken::SpriteBall::m_score_right = 0;

//The number of balls, for debugging purposes
int ribi::Boenken::SpriteBall::sm_n_balls = 0;

ribi::Boenken::SpriteBall::SpriteBall(
  const double x,
  const double y,
  const int size,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b)
: SpriteMoving(x,y,size,r,g,b)
{
  ++sm_n_balls;
  //std::clog << "A ball is created at ("
  //  << this->getX() << ","
  //  << this->getY() << ")\n";
}

ribi::Boenken::SpriteBall::~SpriteBall() noexcept
{
  --sm_n_balls;
  assert(sm_n_balls >= 0);
}


void ribi::Boenken::SpriteBall::SetGoalPoles(
  const double goal_y_top,
  const double goal_y_bottom)
{
  m_goal_y_top    = goal_y_top;
  m_goal_y_bottom = goal_y_bottom;
  assert(m_goal_y_top < m_goal_y_bottom
    && "Assume the top pole is on top");
}

void ribi::Boenken::SpriteBall::Move() noexcept
{
  const double maxx = this->m_maxx - this->m_size;
  const double maxy = this->m_maxy - this->m_size;
  m_x += m_dx;
  m_y += m_dy;

  ///Move moving sprite into the arena at all costs
  if (m_x <  0.0)
  {
    if (m_y  > m_goal_y_top && m_y < m_goal_y_bottom)
    {
      //GOAL!
      ++m_score_right;
      //std::clog << "Ball at ("<< m_x << "," << m_y << ")"
      //  << " hit the left goal, defined in height range <"
      //  << m_goal_y_top << "," << m_goal_y_bottom << ">\n";
    }
    m_x = 0.0;
    m_dx = std::fabs(m_dx);
    //std::clog << "Ball moved to the right to (" << m_x << "," << m_y << ")\n";
  }
  else
  {
    if (m_x > maxx)
    {
      if (m_y  > m_goal_y_top && m_y < m_goal_y_bottom)
      {
        ///GOAL!
        ++m_score_left;
        //std::clog << "Ball at ("<< m_x << "," << m_y << ")"
        //  << " hit the right goal, defined in height range <"
        //  << m_goal_y_top << "," << m_goal_y_bottom << ">\n";
      }
      m_x = maxx;
      m_dx = -std::fabs(m_dx);
      //std::clog << "Ball moved to the left to (" << m_x << "," << m_y << ")\n";
    }
  }
  if (m_y <  0.0)
  {
    m_y  =  0.0;
    m_dy = std::fabs(m_dy);
    //std::clog << "Ball moved downwards to (" << m_x << "," << m_y << ")\n";

  }
  else
  {
    if (m_y > maxy)
    {
      m_y  = maxy;
      m_dy = -std::fabs(m_dy);
      //std::clog << "Ball moved upwards to (" << m_x << "," << m_y << ")\n";
    }
  }
  m_dx *= m_friction;
  m_dy *= m_friction;
}

std::pair<int,int> ribi::Boenken::SpriteBall::GetScore() noexcept
{
  return std::make_pair(m_score_left,m_score_right);
}
