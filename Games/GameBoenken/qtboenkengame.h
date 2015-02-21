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
#ifndef BOENKENGAME_H
#define BOENKENGAME_H

#include <vector>
#include <boost/shared_ptr.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "boenkenarenasettings.h"
#include "boenkencontrols.h"
#include "qtboenkensprite.h"
#pragma GCC diagnostic pop

struct QPainter;

namespace ribi {

namespace Boenken {

struct Sprite;
struct SpriteBall;
struct SpriteMoving;
struct SpriteNonMoving;
struct SpritePlayer;

///Boenken contains the game.
///Boenken can be displayed by DialogMain
struct Game
{
  Game(
    const ArenaSettings& arena_settings,
    const Controls& controls,
    std::vector<boost::shared_ptr<SpritePlayer   > > players,
    std::vector<boost::shared_ptr<SpriteBall     > > balls,
    std::vector<boost::shared_ptr<SpriteNonMoving> > obstacles);

  void drawPlayers(QPainter& painter) const;
  int getWidth()  const;
  int getHeight() const;
  const std::pair<int,int> GetScore() const;
  void pressKey(const int key);
  //void resize(const int width, const int height);
  void tick();

  private:
  ///'Real' sprites
  std::vector<boost::shared_ptr<SpritePlayer   > > m_players;
  std::vector<boost::shared_ptr<SpriteBall     > > m_balls;
  std::vector<boost::shared_ptr<SpriteNonMoving> > m_obstacles;
  ///Sprite copies for group-specific routines
  const std::vector<SpriteMoving*> m_moving_sprites;
  const std::vector<Sprite      *> m_sprites;
  ///
  const ArenaSettings m_arena_settings;
  const Controls m_controls;

  ///Collect all moving sprites
  static const std::vector<SpriteMoving*> CollectMovingSprites(
    std::vector<boost::shared_ptr<SpritePlayer> > players,
    std::vector<boost::shared_ptr<SpriteBall  > > balls);

  static const std::vector<Sprite*> CollectSprites(
    std::vector<boost::shared_ptr<SpritePlayer   > > players,
    std::vector<boost::shared_ptr<SpriteBall     > > balls,
    std::vector<boost::shared_ptr<SpriteNonMoving> > obstacles);

  ///Test this class
  static void Test() noexcept;

};

} //~namespace Boenken

} //~namespace ribi

#endif // BOENKENGAME_H
