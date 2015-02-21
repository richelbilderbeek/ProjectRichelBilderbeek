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
#ifndef QTBOENKENMENUDIALOG_H
#define QTBOENKENMENUDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtBoenkenMenuDialog;
}

namespace ribi {

struct QtBoenkenPlayersDialog;
struct QtBoenkenArenaDialog;
struct QtBoenkenControlsDialog;

namespace Boenken
{
  struct ArenaSettings;
  struct SpriteBall;
  struct SpriteNonMoving;
  struct SpritePlayer;
}

///QtBoenkenMenuDialog
///
///Gathers all options to start a game
class QtBoenkenMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtBoenkenMenuDialog(QWidget *parent = 0);
  QtBoenkenMenuDialog(const QtBoenkenMenuDialog&) = delete;
  QtBoenkenMenuDialog& operator=(const QtBoenkenMenuDialog&) = delete;
  ~QtBoenkenMenuDialog() noexcept;

private:
  Ui::QtBoenkenMenuDialog *ui;
  boost::shared_ptr<QtBoenkenControlsDialog> m_controls;
  boost::shared_ptr<QtBoenkenPlayersDialog> m_players;
  boost::shared_ptr<QtBoenkenArenaDialog> m_arena;

  static const std::vector<boost::shared_ptr<Boenken::SpritePlayer> > CreatePlayers(
    const Boenken::ArenaSettings& a);

  static const std::vector<boost::shared_ptr<Boenken::SpriteBall> > CreateBalls(
    const Boenken::ArenaSettings& a);

  static const std::vector<boost::shared_ptr<Boenken::SpriteNonMoving> > CreateObstacles(
    const Boenken::ArenaSettings& a);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void onControlsClick();
  void onPlayersClick();
  void onArenaClick();
  void onStartClick();
  void onTrainClick();
  void onAboutClick();
};

} //~namespace ribi

#endif // QTBOENKENMENUDIALOG_H
