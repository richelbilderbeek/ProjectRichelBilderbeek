//---------------------------------------------------------------------------
/*
ConnectThreeWidget. GUI independent ConnectThree widget.
Copyright (C) 2010 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "connectthreewidget.h"
#pragma GCC diagnostic pop

#include <cassert>
#include "connectthree.h"

ribi::ConnectThreeWidget::ConnectThreeWidget(
  const std::bitset<3>& is_player_human,
  const int n_cols,
  const int n_rows)
  : m_game(new ConnectThree(n_cols,n_rows)),
    m_is_player_human(is_player_human)
{
  assert(m_game);
}

void ribi::ConnectThreeWidget::DoMove(const int x,const int y)
{
  m_game->DoMove(x,y);
}

const ribi::ConnectThree * ribi::ConnectThreeWidget::GetGame() const noexcept
{
  return m_game.get();
}

//ConnectThree * ribi::ConnectThreeWidget::GetGame()
//{
//  return m_game.get();
//}

const std::string ribi::ConnectThreeWidget::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::ConnectThreeWidget::GetVersionHistory() noexcept
{
  return {
    "2011-04-20: version 1.0: initial version"
  };
}

bool ribi::ConnectThreeWidget::IsComputerTurn() const noexcept
{
  assert(m_game);
  return !IsHuman(m_game->GetActivePlayer());
}

bool ribi::ConnectThreeWidget::IsHuman(const int player_index) const
{
  assert(ConnectThree::player1 == 0);
  assert(ConnectThree::player2 == 1);
  assert(ConnectThree::player3 == 2);
  assert(player_index >= 0);
  assert(player_index < static_cast<int>(m_is_player_human.size()));
  return m_is_player_human[player_index];
}

void ribi::ConnectThreeWidget::Restart()
{
  assert(m_game);
  m_game->Restart();
}

void ribi::ConnectThreeWidget::SetIsPlayerHuman(const std::bitset<3>& is_player_human)
{
  if (m_is_player_human != is_player_human)
  {
    //Only restart game if something changed
    m_is_player_human = is_player_human;
    Restart();
  }
}

const boost::tuple<int,int,int> ribi::ConnectThreeWidget::SuggestMove() const
{
  return m_game->SuggestMove(this->GetIsPlayerHuman());
}

///Tick does either wait for a human to make his/her move
///or lets a computer do its move. Tick must be called by
///external timers like Wt::WTimer or QTimer.
void ribi::ConnectThreeWidget::Tick()
{
  if (IsComputerTurn())
  {
    const boost::tuple<int,int,int> m = m_game->SuggestMove(this->GetIsPlayerHuman());
    m_game->DoMove(m.get<0>(),m.get<1>());
  }
}
