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
#ifndef WTCONNECTTHREEGAMEDIALOG_H
#define WTCONNECTTHREEGAMEDIALOG_H

#include <bitset>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#include "connectthreefwd.h"
#pragma GCC diagnostic pop

namespace Wt
{
  struct WTimer;
}


namespace ribi {
namespace con3 {

///WtConnectThreeGameDialog contains the
///ConnectThree game.
struct WtConnectThreeGameDialog : public Wt::WContainerWidget
{
  enum State { state_playing, state_winner };
  explicit WtConnectThreeGameDialog(
    const boost::shared_ptr<const ConnectThreeResources> resources,
    const std::bitset<3>& is_player_human = std::bitset<3>(true)
  );
  WtConnectThreeGameDialog(const WtConnectThreeGameDialog&) = delete;
  WtConnectThreeGameDialog& operator=(const WtConnectThreeGameDialog&) = delete;
  bool HasWinner() const { return m_state == state_winner; }
  void PauseTimer();
  void RestartGame();
  void SetIsPlayerHuman(const std::bitset<3>& is_player_human);
  void StartTimer();

  private:
  ~WtConnectThreeGameDialog();
  WtConnectThreeWidget * m_board;
  std::bitset<3> m_is_player_human;
  std::vector<Wt::WImage *> m_players;
  const boost::shared_ptr<const ConnectThreeResources> m_resources;
  State m_state;
  Wt::WTimer * const m_timer;

  void DoComputerTurn();
  void OnValidMove();
  void ShowGame();
  void ShowWinner();
  void UpdatePlayersPanel();
};

} //~namespace con3
} //~namespace ribi

#endif // WTCONNECTTHREEGAMEDIALOG_H
