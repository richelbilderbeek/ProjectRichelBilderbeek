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
#include "qtboenkengame.h"



#include <QPainter>

#include "boenkenarenasettings.h"
#include "qtboenkensprite.h"
#include "qtboenkenspriteball.h"
#include "qtboenkenspritemoving.h"
#include "qtboenkenspritenonmoving.h"
#include "qtboenkenspriteplayer.h"
#include "testtimer.h"

#pragma GCC diagnostic pop

ribi::Boenken::Game::Game(
  const ArenaSettings& arena_settings,
  const Controls& controls,
  std::vector<boost::shared_ptr<SpritePlayer   > > players,
  std::vector<boost::shared_ptr<SpriteBall     > > balls,
  std::vector<boost::shared_ptr<SpriteNonMoving> > obstacles)
  : m_players(players),
    m_balls(balls),
    m_obstacles(obstacles),
    m_moving_sprites(CollectMovingSprites(players,balls)),
    m_sprites(CollectSprites(players,balls,obstacles)),
    m_arena_settings(arena_settings),
    m_controls(controls)
{
  #ifndef NDEBUG
  Test();
  #endif
  ///Reset the score to 0-0
  SpriteBall::ResetScore();

  ///Set the friction
  SpriteMoving::SetFriction(m_arena_settings.friction);

  ///Set the arena size for the Sprites
  Sprite::setArenaSize(this->getWidth(),this->getHeight());

  ///Keep the right goal posts at the right side
  ///Assume this is done!
  assert(m_obstacles.size() >= 4
    && "There must be at least four goal posts");
  //m_obstacles[2]->setX(width - m_obstacles[2]->m_size);
  //m_obstacles[3]->setX(width - m_obstacles[3]->m_size);

  ///Set the goal area
  assert(m_obstacles.size() >= 4
    && "There must be at least four goal posts");
  const double goal_y_top    = m_obstacles[0]->getY();
  const double goal_y_bottom = m_obstacles[1]->getY();
  assert(goal_y_top <= goal_y_bottom);
  SpriteBall::SetGoalPoles(goal_y_top,goal_y_bottom);
}

const std::vector<ribi::Boenken::SpriteMoving*> ribi::Boenken::Game::CollectMovingSprites(
  std::vector<boost::shared_ptr<SpritePlayer> > players,
  std::vector<boost::shared_ptr<SpriteBall  > > balls)
{
  std::vector<SpriteMoving*> v;
  for(boost::shared_ptr<SpritePlayer> i: players)
  {
    assert(i);
    SpriteMoving * const s = i.get();
    assert(s);
    v.push_back(s);
  }
  for(boost::shared_ptr<SpriteBall> i: balls)
  {
    assert(i);
    SpriteMoving * const s = i.get();
    assert(s);
    v.push_back(s);
  }
  return v;
}

const std::vector<ribi::Boenken::Sprite*> ribi::Boenken::Game::CollectSprites(
  std::vector<boost::shared_ptr<SpritePlayer   > > players,
  std::vector<boost::shared_ptr<SpriteBall     > > balls,
  std::vector<boost::shared_ptr<SpriteNonMoving> > obstacles)
{
  std::vector<Sprite*> v;
  for(boost::shared_ptr<SpritePlayer> i: players)
  {
    assert(i);
    Sprite * const s = i.get();
    assert(s);
    v.push_back(s);
  }
  for(boost::shared_ptr<SpriteBall> i: balls)
  {
    assert(i);
    Sprite * const s = i.get();
    assert(s);
    v.push_back(s);
  }
  for(boost::shared_ptr<SpriteNonMoving> i: obstacles)
  {
    assert(i);
    Sprite * const s = i.get();
    assert(s);
    v.push_back(s);
  }
  return v;
}

void ribi::Boenken::Game::drawPlayers(QPainter& painter) const
{
  for(const Sprite * const s: m_sprites)
  {
    s->Draw(painter);
  }
}

int ribi::Boenken::Game::getHeight() const
{
  return m_arena_settings.height();
}

const std::pair<int,int> ribi::Boenken::Game::GetScore() const
{
  return SpriteBall::GetScore();
}

int ribi::Boenken::Game::getWidth() const
{
  return m_arena_settings.width();
}


void ribi::Boenken::Game::pressKey(const int key)
{
  const std::size_t n_players = m_controls.m_names.size();
  for (std::size_t i=0; i!=n_players; ++i)
  {
    if (key == m_controls.m_keys_accel[i]) m_players[i]->Accelerate();
    if (key == m_controls.m_keys_turn[i] ) m_players[i]->TurnRight();
  }
  switch (key)
  {
    ///F1 is the debugging key
    ///F2 is the debugging key, after which there is a quit
    case Qt::Key_F1:
    case Qt::Key_F2:
    {
      //std::clog << "Player coordinats:\n";
      //BOOST_FOREACH(boost::shared_ptr<SpritePlayer>& s,m_players)
      {
        //std::clog << s.get() << ": (" << s->getX() << "," << s->getY() << ")\n";
      }
      //std::clog << "Ball coordinats:\n";
      //BOOST_FOREACH(boost::shared_ptr<SpriteBall>& s,m_balls)
      {
        //std::clog << s.get() << ": (" << s->getX() << "," << s->getY() << ")\n";
      }
      //std::clog << "Moving sprite coordinats (must match above):\n";
      //BOOST_FOREACH(SpriteMoving * s,m_moving_sprites)
      {
        //std::clog << s << ": (" << s->getX() << "," << s->getY() << ")\n";
      }
    }
  }
  if (key == Qt::Key_F2) std::exit(1);
}

void ribi::Boenken::Game::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const boost::shared_ptr<SpritePlayer> p(new SpritePlayer(
      0.0,0.0,0.0,8,0,0,0));
    assert(p);
  }
  {
    const boost::shared_ptr<SpriteBall> p(new SpriteBall(0.0,0.0));
    assert(p);
  }
  {
    const boost::shared_ptr<SpriteNonMoving> p(new SpriteNonMoving(0.0,0.0));
    assert(p);
  }
  {
    ArenaSettings arena_settings;
    const Controls controls;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}

///Moves all sprites
void ribi::Boenken::Game::tick()
{
  ///Move all moving sprites
  for(SpriteMoving* const s: m_moving_sprites)
  {
    assert(s);
    s->Move();
  }

  ///Check all moving sprite collisions with moving sprites
  {
    for(SpriteMoving* const s1: m_moving_sprites)
    {
      for(SpriteMoving* const s2: m_moving_sprites)
      {
        assert(s1);
        assert(s2);
        if (s1 <= s2) continue;
        SpritePlayer::Collision(s1,s2);
      }
    }
  }

  ///Check all moving sprite collisions with non-moving sprites
  {
    for(boost::shared_ptr<SpriteNonMoving>& s1: m_obstacles)
    {
      for(SpriteMoving* const s2: m_moving_sprites)
      {
        SpriteNonMoving::Collision(*s1,*s2);
      }
    }
  }
}
