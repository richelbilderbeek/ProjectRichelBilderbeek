//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#ifndef QTCONNECTTHREEGAMEDIALOG_H
#define QTCONNECTTHREEGAMEDIALOG_H

#include <bitset>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop


namespace Ui {
  class QtConnectThreeGameDialog;
}

namespace ribi {
namespace con3 {

struct QtConnectThreeWidget;
struct ConnectThreeResources;

class QtConnectThreeGameDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtConnectThreeGameDialog(
    const boost::shared_ptr<const ConnectThreeResources> resources,
    QWidget *parent = 0,
    const std::bitset<3>& is_player_human = std::bitset<3>(true)) noexcept;
  QtConnectThreeGameDialog(const QtConnectThreeGameDialog&) = delete;
  QtConnectThreeGameDialog& operator=(const QtConnectThreeGameDialog&) = delete;
  ~QtConnectThreeGameDialog() noexcept;

  boost::signals2::signal<void ()> m_signal_close;

public slots:
  void DoComputerTurn() noexcept;

private:
  Ui::QtConnectThreeGameDialog *ui;
  QtConnectThreeWidget * const m_board;
  const std::bitset<3>& m_is_player_human;

  ///The filenames
  const boost::shared_ptr<const ConnectThreeResources> m_resources;

  ///OnValidMove is called after a valid move. The game
  ///is either terminated, or the next player can do
  ///his/her move.
  void OnValidMove() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace con3
} //~namespace ribi

#endif // QTCONNECTTHREEGAMEDIALOG_H
