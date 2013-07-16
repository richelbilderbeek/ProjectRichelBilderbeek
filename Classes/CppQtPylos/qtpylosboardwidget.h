//---------------------------------------------------------------------------
/*
PylosWidget, widget to display Pylos class
Copyright (C) 2010 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifndef QTPYLOSBOARDWIDGET_H
#define QTPYLOSBOARDWIDGET_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include <QWidget>

#include "qtpyloswidget.h"
#include "pylosboard.h"

struct QPaintEvent;

///PylosWidget manages a Pylos::Board and facilitates its user interface
class QtPylosBoardWidget : public QtPylosWidget
{
  Q_OBJECT
public:
  QtPylosBoardWidget();

  ///CanRemove specifies if current player can remove one or
  ///two marble(s) at the requested position(s).
  bool CanRemove(const std::vector<Pylos::Coordinat>& v) const;

  ///CanSet tests if the current player can be set at the Coordinat
  bool CanSet(const Pylos::Coordinat& c) const;

  ///CanSetPlayer determines is the active Player can be changed.
  ///CanSetPlayer returns false if there are marbles to be removed
  bool CanSetPlayer(const Pylos::Player player) const;

  ///CanTransfer specifies if current player can transfer
  ///the marble at the specified coordinat for movement
  bool CanTransfer(const Pylos::Coordinat& c) const;

  ///CanTransfer specifies if current player can transfer his marble
  ///to a new, higher position
  bool CanTransfer(
    const Pylos::Coordinat& from,
    const Pylos::Coordinat& to) const;

  ///GetPylos returns a read-only pylos
  const Pylos::Board * GetBoard() { return m_board.get(); }

  ///GetCurrentTurn returns whose turn it is now
  Pylos::Player GetCurrentTurn() const;

  ///GetLayerSize returns how many marbles this is wide/height.
  ///For exaple; layer 0 has 4x4 marbles, so GetLayerSize
  ///will return 4.
  int GetLayerSize(const int layer) const;

  ///Obtain the MustRemoveState of the widget
  Pylos::MustRemoveState GetMustRemove() const { return m_must_remove; }

  ///Obtain the PositionState at a certain coordinat
  Pylos::PositionState Get(const Pylos::Coordinat& c) const;

  ///GetSelector returns the selector's current coodinat
  //const Pylos::Coordinat& GetSelector() const { return m_select; }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Return the possible winner
  Pylos::Winner GetWinner() const;

  ///Remove lets the current player remove one or two marbles
  void Remove(const std::vector<Pylos::Coordinat>& v);

  ///Set makes current player place his marble
  ///at the specified position. After Set,
  ///GetMustRemove must be called to determine if
  ///the current player must remove some marbles
  void Set(const Pylos::Coordinat& c);

  ///SetPlayer determines which player is allowed to make a move
  void SetPlayer(const Pylos::Player player);

  ///StartAdvanced cleans the board to start a game
  ///with advanced rules
  void StartAdvanced();

  ///StartBasic cleans the board to start a game
  ///with basic rules
  void StartBasic();

  ///Transfer lets current player tranfer his marble to a new, higher position
  void Transfer(
    const Pylos::Coordinat& from,
    const Pylos::Coordinat& to);


signals:

  ///PlayerChanged is emitted when the active player has changed
  void PlayerChanged();

private:

  //Pylos::QtSprites m_sprites;
  boost::shared_ptr<Pylos::Board> m_board;

  ///m_must_remove tracks if the user must remove one/two marbles
  Pylos::MustRemoveState m_must_remove;

  ///m_player is the player that is allowed to do a move
  Pylos::Player m_player;

};

#endif // QTPYLOSBOARDWIDGET_H

