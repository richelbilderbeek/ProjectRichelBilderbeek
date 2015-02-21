//---------------------------------------------------------------------------
/*
PylosWidget, widget to display Pylos class
Copyright (C) 2010-2015 Richel Bilderbeek

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

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>

#include <QWidget>

#include "qtpyloswidget.h"
#include "pylosboard.h"
#pragma GCC diagnostic pop

struct QPaintEvent;

namespace ribi {
namespace pylos {

///PylosWidget manages a pylos::Board and facilitates its user interface
class QtPylosBoardWidget : public QtPylosWidget
{
  Q_OBJECT
public:
  QtPylosBoardWidget();
  QtPylosBoardWidget(const QtPylosBoardWidget&) = delete;
  QtPylosBoardWidget& operator=(const QtPylosBoardWidget&) = delete;
  ~QtPylosBoardWidget() noexcept {}

  ///CanRemove specifies if current player can remove one or
  ///two marble(s) at the requested position(s).
  bool CanRemove(const std::vector<pylos::Coordinat>& v) const;

  ///CanSet tests if the current player can be set at the Coordinat
  bool CanSet(const pylos::Coordinat& c) const;

  ///CanSetPlayer determines is the active Player can be changed.
  ///CanSetPlayer returns false if there are marbles to be removed
  bool CanSetPlayer(const pylos::Player player) const;

  ///CanTransfer specifies if current player can transfer
  ///the marble at the specified coordinat for movement
  bool CanTransfer(const pylos::Coordinat& c) const;

  ///CanTransfer specifies if current player can transfer his marble
  ///to a new, higher position
  bool CanTransfer(
    const pylos::Coordinat& from,
    const pylos::Coordinat& to) const;

  ///GetPylos returns a read-only pylos
  const pylos::Board * GetBoard() { return m_board.get(); }

  ///GetCurrentTurn returns whose turn it is now
  pylos::Player GetCurrentTurn() const;

  ///GetLayerSize returns how many marbles this is wide/height.
  ///For exaple; layer 0 has 4x4 marbles, so GetLayerSize
  ///will return 4.
  int GetLayerSize(const int layer) const;

  ///Obtain the MustRemoveState of the widget
  pylos::MustRemoveState GetMustRemove() const { return m_must_remove; }

  ///Obtain the PositionState at a certain coordinat
  pylos::PositionState Get(const pylos::Coordinat& c) const;

  ///GetSelector returns the selector's current coodinat
  //const pylos::Coordinat& GetSelector() const { return m_select; }

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Return the possible winner
  pylos::Winner GetWinner() const;

  ///Remove lets the current player remove one or two marbles
  void Remove(const std::vector<pylos::Coordinat>& v);

  ///Set makes current player place his marble
  ///at the specified position. After Set,
  ///GetMustRemove must be called to determine if
  ///the current player must remove some marbles
  void Set(const pylos::Coordinat& c);

  ///SetPlayer determines which player is allowed to make a move
  void SetPlayer(const pylos::Player player);

  ///StartAdvanced cleans the board to start a game
  ///with advanced rules
  void StartAdvanced();

  ///StartBasic cleans the board to start a game
  ///with basic rules
  void StartBasic();

  ///Transfer lets current player tranfer his marble to a new, higher position
  void Transfer(
    const pylos::Coordinat& from,
    const pylos::Coordinat& to);


signals:

  ///PlayerChanged is emitted when the active player has changed
  void PlayerChanged();

private:

  //pylos::QtSprites m_sprites;
  boost::shared_ptr<pylos::Board> m_board;

  ///m_must_remove tracks if the user must remove one/two marbles
  pylos::MustRemoveState m_must_remove;

  ///m_player is the player that is allowed to do a move
  pylos::Player m_player;

};

} //~namespace pylos
} //~namespace ribi

#endif // QTPYLOSBOARDWIDGET_H

