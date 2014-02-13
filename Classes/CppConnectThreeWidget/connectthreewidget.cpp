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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "connectthreewidget.h"
#pragma GCC diagnostic pop

#include <cassert>
#include "connectthree.h"
#include "textcanvas.h"

ribi::con3::ConnectThreeWidget::ConnectThreeWidget(
  const std::bitset<3>& is_player_human,
  const int n_cols,
  const int n_rows)
  : m_game(new ConnectThree(n_cols,n_rows)),
    m_is_player_human(is_player_human),
    m_x{n_cols / 2},
    m_y{n_rows / 2}
{
  assert(m_game);
}

void ribi::con3::ConnectThreeWidget::DoMove(const int x,const int y)
{
  m_game->DoMove(x,y);
}

//ConnectThree * ribi::con3::ConnectThreeWidget::GetGame()
//{
//  return m_game.get();
//}

const std::string ribi::con3::ConnectThreeWidget::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::con3::ConnectThreeWidget::GetVersionHistory() noexcept
{
  return {
    "2011-04-20: version 1.0: initial version"
  };
}

bool ribi::con3::ConnectThreeWidget::IsComputerTurn() const noexcept
{
  assert(m_game);
  return !IsHuman(m_game->GetActivePlayer());
}

bool ribi::con3::ConnectThreeWidget::IsHuman(const int player_index) const
{
  assert(ConnectThree::player1 == 0);
  assert(ConnectThree::player2 == 1);
  assert(ConnectThree::player3 == 2);
  assert(player_index >= 0);
  assert(player_index < static_cast<int>(m_is_player_human.size()));
  return m_is_player_human[player_index];
}

void ribi::con3::ConnectThreeWidget::OnKeyPress(const Key key)
{
  switch (key)
  {
    case Key::up   : if (m_y > 0) --m_y; break;
    case Key::right: if (m_x + 1 < m_game->GetCols()) ++m_x; break;
    case Key::down : if (m_y + 1 < m_game->GetRows()) ++m_y; break;
    case Key::left : if (m_x > 0) --m_x; break;
    case Key::select:
      if (m_game->CanDoMove(m_x,m_y)) { m_game->DoMove(m_x,m_y); }
      break;
  }
}

void ribi::con3::ConnectThreeWidget::Restart()
{
  assert(m_game);
  m_game->Restart();
}

void ribi::con3::ConnectThreeWidget::SetIsPlayerHuman(const std::bitset<3>& is_player_human)
{
  if (m_is_player_human != is_player_human)
  {
    //Only restart game if something changed
    m_is_player_human = is_player_human;
    Restart();
  }
}

const boost::tuple<int,int,Player> ribi::con3::ConnectThreeWidget::SuggestMove() const
{
  return m_game->SuggestMove();
}

///Tick does either wait for a human to make his/her move
///or lets a computer do its move. Tick must be called by
///external timers like Wt::WTimer or QTimer.
void ribi::con3::ConnectThreeWidget::Tick()
{
  if (IsComputerTurn())
  {
    const boost::tuple<int,int,int> m = m_game->SuggestMove();
    m_game->DoMove(m.get<0>(),m.get<1>());
  }
}


const boost::shared_ptr<ribi::TextCanvas> ribi::con3::ConnectThreeWidget::ToTextCanvas() const noexcept
{
  assert(m_game);
  const int n_cols { m_game->GetCols() };
  const int n_rows { m_game->GetCols() };

  const boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(n_cols,n_rows)
  };
  for (int y=0; y!=n_rows; ++y)
  {
    for (int x=0; x!=n_cols; ++x)
    {
      char c = ' ';
      switch (m_game->GetSquare(x,y))
      {
        case ConnectThree::no_player: c = (x + y % 2 ? '.' : ' '); break;
        case ConnectThree::player1: c = 'O'; break;
        case ConnectThree::player2: c = 'X'; break;
        case ConnectThree::player3: c = 'A'; break;
        case ConnectThree::draw:
        default:
          assert(!"Should not get here");
      }
      canvas->PutChar(x,y,c);
    }
  }

  const char c = canvas->GetChar(m_x,m_y);
  char d = ' ';
  switch (c)
  {
    case ' ': d = '.'; break;
    case '.': d = ' '; break;
    case 'O': d = 'o'; break;
    case 'X': d = 'x'; break;
    case 'A': d = 'a'; break;
    case 'o': d = 'O'; break;
    case 'x': d = 'X'; break;
    case 'a': d = 'A'; break;
  }
  canvas->PutChar(m_x,m_y,d);
  return canvas;

  return canvas;
}
