//---------------------------------------------------------------------------
/*
ConnectThreeWidget. GUI independent ConnectThree widget.
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppConnectThreeWidget.htm
//---------------------------------------------------------------------------
#ifndef CONNECTTHREEWIDGET_H
#define CONNECTTHREEWIDGET_H

#include <bitset>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include "connectthree.h"
#include "connectthreefwd.h"
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace con3 {

struct ConnectThree;

///ConnectThreeWidget embodies the interaction with a user
///It keeps track which players are human and whose turn it is
struct ConnectThreeWidget
{
  enum class Key { up, right, down, left, select };

  explicit ConnectThreeWidget(
    const std::bitset<3>& is_player_human = std::bitset<3>(true),
    const int n_cols = 16,
    const int n_rows = 12);


  bool CanDoMove() const noexcept { return CanDoMove(m_x,m_y); }
  bool CanSelect(const int x, const int y) const noexcept;

  ///Let the computer do a move
  void DoComputerMove() noexcept;

  ///Press select at the current place
  void DoMove() noexcept;


  const boost::shared_ptr<const ConnectThree> GetGame() const noexcept { return m_game; }
  const std::bitset<3>& GetIsPlayerHuman() const noexcept { return m_is_player_human; }
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  bool IsComputerTurn() const noexcept;
  bool IsHuman(const Player player) const noexcept;
  void OnKeyPress(const Key key) noexcept;
  void Restart() noexcept;
  void Select(const int x, const int y) noexcept;
  void SetIsPlayerHuman(const std::bitset<3>& is_player_human) noexcept;
  const boost::shared_ptr<Move> SuggestMove() const noexcept;
  const boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;
  void Tick() noexcept;

  private:
  ~ConnectThreeWidget() noexcept {}
  friend void boost::checked_delete<>(ConnectThreeWidget*);
  friend void boost::checked_delete<>(const ConnectThreeWidget*);

  boost::shared_ptr<ConnectThree> m_game;
  std::bitset<3> m_is_player_human;

  //X coordinat of cursor
  int m_x;

  //Y coordinat of cursor
  int m_y;

  bool CanDoMove(const int x, const int y) const noexcept;
  void DoMove(const int x, const int y) noexcept;
  int PlayerToIndex(const Player player) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace con3
} //~namespace ribi

#endif // CONNECTTHREEWIDGET_H
