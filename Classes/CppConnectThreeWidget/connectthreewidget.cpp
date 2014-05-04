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
#include <stdexcept>

#include "connectthree.h"
#include "connectthreemove.h"
#include "textcanvas.h"
#include "trace.h"

ribi::con3::ConnectThreeWidget::ConnectThreeWidget(
  const std::bitset<3>& is_player_human,
  const int n_cols,
  const int n_rows)
  : m_game(new ConnectThree(n_cols,n_rows)),
    m_is_player_human(is_player_human),
    m_x{n_cols / 2},
    m_y{n_rows / 2}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_game);
}

bool ribi::con3::ConnectThreeWidget::CanDoMove(const int x,const int y) const noexcept
{
  return m_game->CanDoMove(x,y);
}

bool ribi::con3::ConnectThreeWidget::CanSelect(const int x, const int y) const noexcept
{
  return
       x >= 0 && x < GetGame()->GetCols()
    && y >= 0 && y < GetGame()->GetRows()
    && GetGame()->GetSquare(x,y) == Square::empty;
}

std::bitset<3> ribi::con3::ConnectThreeWidget::CreateDefaultIsPlayerHuman() noexcept
{
  std::bitset<3> b;
  b[0] = true;
  b[1] = true;
  b[2] = true;
  return b;
}

void ribi::con3::ConnectThreeWidget::DoComputerMove() noexcept
{
  const auto move = SuggestMove();
  assert(CanDoMove(move->GetX(),move->GetY()));
  DoMove(move->GetX(),move->GetY());
}

void ribi::con3::ConnectThreeWidget::DoMove() noexcept
{
  assert(CanDoMove());
  assert(CanDoMove(m_x,m_y));
  m_game->DoMove(m_x,m_y);
}

void ribi::con3::ConnectThreeWidget::DoMove(const int x,const int y) noexcept
{
  assert(CanDoMove(x,y));
  m_game->DoMove(x,y);
}

std::string ribi::con3::ConnectThreeWidget::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::con3::ConnectThreeWidget::GetVersionHistory() noexcept
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

bool ribi::con3::ConnectThreeWidget::IsHuman(const Player player) const noexcept
{
  const int player_index = PlayerToIndex(player);
  assert(player_index >= 0);
  assert(player_index < static_cast<int>(m_is_player_human.size()));
  return m_is_player_human[player_index];
}

void ribi::con3::ConnectThreeWidget::OnKeyPress(const Key key) noexcept
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

int ribi::con3::ConnectThreeWidget::PlayerToIndex(const Player player) const noexcept
{
  switch(player)
  {
    case Player::player1: return 0;
    case Player::player2: return 1;
    case Player::player3: return 2;
    default:
      assert(!"Should not get here");
      throw std::logic_error("Unknown player");
  }
}

void ribi::con3::ConnectThreeWidget::Restart() noexcept
{
  assert(m_game);
  m_game->Restart();
}

void ribi::con3::ConnectThreeWidget::Select(const int x, const int y) noexcept
{
  assert(CanSelect(x,y));
  m_x = x;
  m_y = y;
}

void ribi::con3::ConnectThreeWidget::SetIsPlayerHuman(const std::bitset<3>& is_player_human) noexcept
{
  if (m_is_player_human != is_player_human)
  {
    //Only restart game if something changed
    m_is_player_human = is_player_human;
    Restart();
  }
}

const boost::shared_ptr<ribi::con3::Move> ribi::con3::ConnectThreeWidget::SuggestMove() const noexcept
{
  return m_game->SuggestMove(m_is_player_human);
}

#ifndef NDEBUG
void ribi::con3::ConnectThreeWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::con3::ConnectThreeWidget::Test");
  const boost::shared_ptr<ConnectThreeWidget> widget {
    new ConnectThreeWidget
  };
  assert(widget->IsHuman(Player::player1));
  assert(widget->IsHuman(Player::player2));
  assert(widget->IsHuman(Player::player3));
  assert(widget->GetGame()->GetCols() == 16);
  assert(widget->GetGame()->GetRows() == 12);
  while (widget->GetGame()->GetWinner() == Winner::no_winner)
  {
    switch ((std::rand() >> 4) % 5)
    {
      case 0: widget->OnKeyPress(Key::up); break;
      case 1: widget->OnKeyPress(Key::right); break;
      case 2: widget->OnKeyPress(Key::down); break;
      case 3: widget->OnKeyPress(Key::left); break;
      case 4: widget->OnKeyPress(Key::select); break;
    }
  }
  TRACE("Finished ribi::con3::ConnectThreeWidget::Test successfully");
}
#endif

///Tick does either wait for a human to make his/her move
///or lets a computer do its move. Tick must be called by
///external timers like Wt::WTimer or QTimer.
void ribi::con3::ConnectThreeWidget::Tick() noexcept
{
  if (IsComputerTurn())
  {
    const auto m = m_game->SuggestMove(m_is_player_human);
    m_game->DoMove(m);
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
        case Square::empty  : c = (x + y % 2 ? '.' : ' '); break;
        case Square::player1: c = 'O'; break;
        case Square::player2: c = 'X'; break;
        case Square::player3: c = 'A'; break;
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
}
