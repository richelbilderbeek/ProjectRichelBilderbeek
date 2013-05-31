//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2011 Richel Bilderbeek

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
//---------------------------------------------------------------------------
#include <bitset>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
namespace Wt
{
  struct WTimer;
}
//---------------------------------------------------------------------------
struct WtConnectThreeWidget;
//---------------------------------------------------------------------------
///WtConnectThreeGameDialog contains the
///ConnectThree game.
struct WtConnectThreeGameDialog : public Wt::WContainerWidget
{
  enum State { state_playing, state_winner };
  WtConnectThreeGameDialog(const std::bitset<3>& is_player_human = std::bitset<3>(true));

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
  State m_state;
  Wt::WTimer * const m_timer;

  void DoComputerTurn();
  void OnValidMove();
  void ShowGame();
  void ShowWinner();
  void UpdatePlayersPanel();
};
//---------------------------------------------------------------------------
#endif // WTCONNECTTHREEGAMEDIALOG_H
