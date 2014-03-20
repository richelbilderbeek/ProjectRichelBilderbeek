//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game class
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppTicTacToe.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "tictactoeboard.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <iostream>
#include <stdexcept>

#include "textcanvas.h"
#include "tictactoehelper.h"
#include "trace.h"

#pragma GCC diagnostic pop

///TicTacToe default contructor creates an empty board,
///where the current turn is to player1.
ribi::tictactoe::Board::Board() noexcept
  : m_signal_changed{},
    m_board(boost::extents[3][3])
    //m_current_player(TicTacToePlayer::player1)
{
  #ifndef NDEBUG
  Test();
  #endif

  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = Square::empty;
  }
}

ribi::tictactoe::Board::Board(const int state)
  : m_signal_changed{},
    m_board(boost::extents[3][3])
{
  SetSummarizedState(state);
}

bool ribi::tictactoe::Board::CanDoMove(const int x, const int y) const noexcept
{
  if (!CanGetSquare(x,y)) return false;
  if (m_board[x][y] != Square::empty) return false;
  return true;
}

bool ribi::tictactoe::Board::CanGetSquare(const int x, const int y) const noexcept
{
  if (x < 0) return false;
  if (y < 0) return false;
  if (x >= 3) return false;
  if (y >= 3) return false;
  return true;
}

void ribi::tictactoe::Board::DoMove(const int x, const int y, const Player player) noexcept
{
  assert(CanDoMove(x,y));
  //std::clog << "Player " << m_current_player
  //  << ": (" << x << "," << y << ")\n";
  m_board[x][y] = Helper().PlayerToSquare(player);
  m_signal_changed(this);
}


ribi::tictactoe::Square ribi::tictactoe::Board::GetSquare(const int x, const int y) const noexcept
{
  assert(CanGetSquare(x,y));
  return m_board[x][y];
}

int ribi::tictactoe::Board::GetSummarizedState() const noexcept
{
  int z = SquareToState(m_board[0][0]);
  for (int i=1; i!=9; ++i)
  {
    z += (SquareToState(m_board[i/3][i%3]) * Helper().IntPower(3,i));
  }
  return z;
}

std::string ribi::tictactoe::Board::GetVersion() noexcept
{
  return "1.6";
}

std::vector<std::string> ribi::tictactoe::Board::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2010-09-19: version 1.3: made CanDoMove method a const member function",
    "2014-01-27: version 1.4: added ToTextCanvas",
    "2014-02-03: version 1.5: added m_signal_changed",
    "2014-03-17: version 1.6: use enum classes, use of noexcept, extracted Game"
  };
  return v;
}

ribi::tictactoe::Winner ribi::tictactoe::Board::GetWinner() const noexcept
{
  //Check rows
  for (int y=0; y!=3; ++y)
  {
    if (m_board[0][y] != Square::empty
     && m_board[0][y] == m_board[1][y]
     && m_board[1][y] == m_board[2][y])
      return Helper().SquareToWinner(m_board[0][y]);
  }
  //Check collumns
  for (int x=0; x!=3; ++x)
  {
    if (m_board[x][0] != Square::empty
     && m_board[x][0] == m_board[x][1]
     && m_board[x][1] == m_board[x][2])
       return Helper().SquareToWinner(m_board[x][0]);
  }
  //Check diagonal
  if (m_board[0][0] != Square::empty
   && m_board[0][0] == m_board[1][1]
   && m_board[1][1] == m_board[2][2])
    return Helper().SquareToWinner(m_board[1][1]);
  //Check other diagonal
  if (m_board[0][2] != Square::empty
   && m_board[0][2] == m_board[1][1]
   && m_board[1][1] == m_board[2][0])
    return Helper().SquareToWinner(m_board[1][1]);
  //Check for draw
  if (NoEmptySquares()) return Winner::draw;
  //No winner
  return Winner::no_winner;
}

bool ribi::tictactoe::Board::NoEmptySquares() const noexcept
{
  for (int i=0; i!=9; ++i)
  {
    if (m_board[i/3][i%3] == Square::empty) return false;
  }
  return true;
}



void ribi::tictactoe::Board::Restart() noexcept
{
  if (GetSummarizedState() == 0) return;

  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = Square::empty;
  }
  m_signal_changed(this);
}

void ribi::tictactoe::Board::SetBoard(const boost::multi_array<Square,2>& board) noexcept
{
  if (m_board == board) return;
  m_board = board;
  m_signal_changed(this);
}

void ribi::tictactoe::Board::SetSquare(
  const int x, const int y, const Square square_state) noexcept
{
  if (m_board[x][y] == square_state) return;

  m_board[x][y] = square_state;

  //Internal test
  assert(GetSquare(x,y)==square_state);

  m_signal_changed(this);
}

void ribi::tictactoe::Board::SetSummarizedState(const int original_state) noexcept
{
  if (GetSummarizedState() == original_state) return;

  assert(original_state >= 0);
  #ifndef NDEBUG
  if (original_state >= Helper().IntPower(3,9))
  {
    TRACE("ERROR");
  }
  #endif
  assert(original_state < Helper().IntPower(3,9));

  int s = original_state;
  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = StateToSquare(s % 3);
    s/=3;
  }

  //Internal check
  assert(GetSummarizedState()==original_state);

  m_signal_changed(this);
}





#ifndef NDEBUG
void ribi::tictactoe::Board::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TicTacToe::Test");
  {
    //Check empty board state
    {
      Board t;
      const int s = t.GetSummarizedState();
      Board u(s);
      assert(u == t);
    }
    //Check one-move states
    for (int i=0; i!=9; ++i)
    {
      Board t;
      t.DoMove(i/3,i%3,Player::player1);
      const int s = t.GetSummarizedState();
      Board u(s);
      assert(u == t);
    }
    //Check two-move states
    for (int i=0; i!=8; ++i)
    {
      Board t;
      t.DoMove(i/3,i%3,Player::player1);
      t.DoMove(i/3,(i+1)%3,Player::player2);
      const int s = t.GetSummarizedState();
      Board u(s);
      assert(u == t);
    }
    //Check draw detection
    {
      Board t;
      t.DoMove(1,1,Player::player1);
      t.DoMove(0,0,Player::player2);
      t.DoMove(1,2,Player::player1);
      t.DoMove(1,0,Player::player2);
      t.DoMove(2,0,Player::player1);
      t.DoMove(0,2,Player::player2);
      t.DoMove(0,1,Player::player1);
      t.DoMove(2,1,Player::player2);
      t.DoMove(2,2,Player::player1);
      assert(t.GetWinner() == Winner::draw);
    }
    //Check player1 wins horizontally detection
    {
      Board t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,1,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,2,Player::player1);
      assert(t.GetWinner() == Winner::player1);
    }
    //Check player2 wins vertically detection
    {
      Board t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,1,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(2,2,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,2,Player::player2);
      assert(t.GetWinner() == Winner::player2);
    }
    //Check player1 wins diagonally detection
    {
      Board t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1,Player::player1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,2,Player::player2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(2,2,Player::player1);
      assert(t.GetWinner() == Winner::player1);
    }
    //Check no-winner detection
    {
      Board t;
      t.DoMove(1,1,Player::player1);
      t.DoMove(0,0,Player::player2);
      t.DoMove(1,2,Player::player1);
      t.DoMove(1,0,Player::player2);
      t.DoMove(2,0,Player::player1);
      t.DoMove(0,2,Player::player2);
      t.DoMove(0,1,Player::player1);
      t.DoMove(2,1,Player::player2);
      //t.DoMove(2,2); //Final move to make a draw
      assert(t.GetWinner() == Winner::no_winner);
    }
    //Check CanDoMove
    for (int i=0; i!=9; ++i)
    {
      Board t;
      t.DoMove(i/3,i%3,Player::player1);
      assert(!t.CanDoMove(i/3,i%3));
    }
    //Check all states
    for (int i=0; i!=Helper().IntPower(3,9); ++i)
    {
      try
      {
        Board t(i);
        assert(t.GetSummarizedState() == i);
      }
      catch (std::exception&)
      {
        //No problem
      }
    }
  }
  TRACE("Finished ribi::TicTacToe::Test successfully");
}
#endif

boost::shared_ptr<ribi::TextCanvas> ribi::tictactoe::Board::ToTextCanvas() const noexcept
{
  boost::shared_ptr<TextCanvas> c {
    new TextCanvas(3,3)
  };
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      c->PutText(x,y,SquareToStr(GetSquare(x,y)));
    }
  }
  return c;
}


std::ostream& ribi::tictactoe::operator<<(std::ostream& os,const ribi::tictactoe::Board& t) noexcept
{
  os
    << SquareToStr(t.GetSquare(0,0))
    << SquareToStr(t.GetSquare(1,0))
    << SquareToStr(t.GetSquare(2,0))
    << '\n'
    << SquareToStr(t.GetSquare(0,1))
    << SquareToStr(t.GetSquare(1,1))
    << SquareToStr(t.GetSquare(2,1))
    << '\n'
    << SquareToStr(t.GetSquare(0,2))
    << SquareToStr(t.GetSquare(1,2))
    << SquareToStr(t.GetSquare(2,2))
  ;
  return os;
}

bool ribi::tictactoe::operator==(const ribi::tictactoe::Board& lhs, const ribi::tictactoe::Board& rhs) noexcept
{
  return lhs.GetBoard() == rhs.GetBoard();
}
