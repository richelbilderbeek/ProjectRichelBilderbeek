//---------------------------------------------------------------------------
/*
WtConnectThreeWidget, Wt widget for ConnectThree display
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
//From http://www.richelbilderbeek.nl/CppWtConnectThreeWidget.htm
//---------------------------------------------------------------------------
#ifndef WTCONNECTTHREEWIDGET_H
#define WTCONNECTTHREEWIDGET_H

#include <bitset>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include "connectthreefwd.h"
#include "connectthreeplayer.h"
#include "connectthreesquare.h"
#include "connectthreewinner.h"
#pragma GCC diagnostic pop

namespace Wt
{
  struct WPaintDevice;
  struct WTimer;
}

namespace ribi {
namespace con3 {

//struct ConnectThreeWidget;
//struct ConnectThreeResources;

///WtConnectThreeWidget is a Wt widget to display
///the area/board of the ConnectThree class.
struct WtConnectThreeWidget : public Wt::WPaintedWidget
{
  explicit WtConnectThreeWidget(
    const boost::shared_ptr<const ConnectThreeResources> resources,
    const std::bitset<3>& is_player_human = std::bitset<3>(true),
    const int n_cols = 16,
    const int n_rows = 12);

  void DoComputerTurn();
  Player GetActivePlayer() const;
  const std::bitset<3>& GetIsPlayerHuman() const;
  static std::string GetVersion();
  static std::vector<std::string> GetVersionHistory();
  Winner GetWinner() const;
  bool IsComputerTurn() const;
  void Restart();
  void SetIsPlayerHuman(const std::bitset<3>& is_player_human);

  ///m_signal_valid_move is emitted on a valid move,
  ///causing the game to be terminated or let
  ///the next player do his/her move.
  boost::signals2::signal<void ()> m_signal_valid_move;

  private:
  void OnClick(const Wt::WMouseEvent& e);
  void paintEvent(Wt::WPaintDevice *paintDevice);

  const boost::scoped_ptr<ConnectThreeWidget> m_widget;
  const std::vector<boost::shared_ptr<const Wt::WPainter::Image> > m_players;
  const boost::scoped_ptr<const Wt::WPainter::Image> m_empty;
  const boost::scoped_ptr<Wt::WTimer> m_timer;
  const Wt::WPainter::Image& GetImage(const Square sprite) const;
};

} //~namespace con3
} //~namespace ribi

#endif // WTCONNECTTHREEWIDGET_H
