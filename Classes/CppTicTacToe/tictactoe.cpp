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
#include "tictactoe.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <iostream>
#include <stdexcept>

#include "textcanvas.h"
#include "trace.h"

#pragma GCC diagnostic pop

///TicTacToe default contructor creates an empty board,
///where the current turn is to player1.
ribi::TicTacToe::TicTacToe()
  : m_signal_changed{},
    m_board(boost::extents[3][3]),
    m_current_player(ribi::TicTacToe::player1)
{
  #ifndef NDEBUG
  Test();
  #endif

  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = ribi::TicTacToe::empty;
  }

  assert(GetCurrentTurn() == 0);
  assert(GetCurrentPlayer() == ribi::TicTacToe::player1);
}

///TicTacToe contructor from summized state integer.
ribi::TicTacToe::TicTacToe(const int state)
  : m_signal_changed{},
    m_board(boost::extents[3][3]),
    m_current_player(-1)
{
  SetSummarizedState(state);

  assert(GetCurrentPlayer() == ribi::TicTacToe::player1
    ||   GetCurrentPlayer() == ribi::TicTacToe::player2);
}

bool ribi::TicTacToe::CanDoMove(const int x, const int y) const
{
  if (m_board[x][y]==0) return true;
  return false;
}

void ribi::TicTacToe::DoMove(const int x, const int y)
{
  assert(CanDoMove(x,y));
  //std::clog << "Player " << m_current_player
  //  << ": (" << x << "," << y << ")\n";
  m_board[x][y] = m_current_player;
  m_current_player = (m_current_player == 1 ? 2 : 1);
  m_signal_changed(this);
}

int ribi::TicTacToe::GetCurrentTurn() const
{
  int turn = 0;
  for (int i=0; i!=9; ++i)
  {
    if (m_board[i/3][i%3] != ribi::TicTacToe::empty) ++turn;
  }
  return turn;
}

int ribi::TicTacToe::GetSquare(const int x,const int y) const
{
  return m_board[x][y];
}

int ribi::TicTacToe::GetSummarizedState() const
{
  int z = m_board[0][0];
  for (int i=1; i!=9; ++i)
  {
    z += (m_board[i/3][i%3] * IntPower(3,i));
  }
  z += (m_current_player * IntPower(3,9));
  return z;
}

const std::string ribi::TicTacToe::GetVersion() noexcept
{
  return "1.5";
}

const std::vector<std::string> ribi::TicTacToe::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2010-09-19: version 1.3: made CanDoMove method a const member function",
    "2014-01-27: version 1.4: added ToTextCanvas",
    "2014-02-03: version 1.5: added m_signal_changed"
  };
  return v;
}

int ribi::TicTacToe::GetWinner() const
{
  //Check rows
  for (int y=0; y!=3; ++y)
  {
    if (m_board[0][y] != ribi::TicTacToe::empty
     && m_board[0][y] == m_board[1][y]
     && m_board[1][y] == m_board[2][y])
      return m_board[0][y];
  }
  //Check collumns
  for (int x=0; x!=3; ++x)
  {
    if (m_board[x][0] != ribi::TicTacToe::empty
     && m_board[x][0] == m_board[x][1]
     && m_board[x][1] == m_board[x][2])
       return m_board[x][0];
  }
  //Check diagonal
  if (m_board[0][0] != ribi::TicTacToe::empty
   && m_board[0][0] == m_board[1][1]
   && m_board[1][1] == m_board[2][2])
    return m_board[1][1];
  //Check other diagonal
  if (m_board[0][2] != ribi::TicTacToe::empty
   && m_board[0][2] == m_board[1][1]
   && m_board[1][1] == m_board[2][0])
    return m_board[1][1];
  //Check for draw
  if (NoEmptySquares())return ribi::TicTacToe::draw;
  //No winner
  return ribi::TicTacToe::no_winner;
}

int ribi::TicTacToe::IntPower(const int base, const int exponent)
{
  assert(exponent != 0
    && "When calculating IntPower(x,0) the result "
       "might be zero or one, depending on the context");
  assert(exponent > 0);

  int result = base;
  for (int i=1; i!=exponent; ++i)
  {
    result*=base;
  }
  return result;
}

bool ribi::TicTacToe::NoEmptySquares() const
{
  for (int i=0; i!=9; ++i)
  {
    if (m_board[i/3][i%3] == ribi::TicTacToe::empty) return false;
  }
  return true;
}

void ribi::TicTacToe::Restart() noexcept
{
  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = ribi::TicTacToe::empty;
  }
  m_current_player = ribi::TicTacToe::player1;

  m_signal_changed(this);
}

void ribi::TicTacToe::SetBoard(const boost::multi_array<int,2>& board)
{
  if (m_board == board) return;

  m_board = board;

  #ifndef NDEBUG
  {
    for (int i=0; i!=9; ++i)
    {
      const int z = m_board[i/3][i%3];
      assert(z == ribi::TicTacToe::empty
          || z == ribi::TicTacToe::player1
          || z == ribi::TicTacToe::player2);
    }
  }
  #endif

  m_signal_changed(this);
}

///SetSquare sets the value of square (x,y).
void ribi::TicTacToe::SetSquare(
  const int x, const int y, const int square_state)
{
  assert(square_state == ribi::TicTacToe::empty
    || square_state == ribi::TicTacToe::player1
    || square_state == ribi::TicTacToe::player2);

  if (m_board[x][y] == square_state) return;

  m_board[x][y] = square_state;

  //Internal test
  assert(GetSquare(x,y)==square_state);

  m_signal_changed(this);
}

void ribi::TicTacToe::SetSummarizedState(const int original_state)
{
  if (GetSummarizedState() == original_state) return;

  int s = original_state;
  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = s % 3;
    s/=3;
  }
  if (s!=ribi::TicTacToe::player1 && s != ribi::TicTacToe::player2)
  {
    throw std::invalid_argument("Invalid TicTacToe state");
  }

  m_current_player = s;

  //Internal check
  assert(GetSummarizedState()==original_state);

  m_signal_changed(this);
}

#ifndef NDEBUG
void ribi::TicTacToe::Test() noexcept
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
      TicTacToe t;
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == t);
    }
    //Check one-move states
    for (int i=0; i!=9; ++i)
    {
      TicTacToe t;
      t.DoMove(i/3,i%3);
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == t);
    }
    //Check two-move states
    for (int i=0; i!=8; ++i)
    {
      TicTacToe t;
      t.DoMove(i/3,i%3);
      t.DoMove(i/3,(i+1)%3);
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == t);
    }
    //Check draw detection
    {
      TicTacToe t;
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 0);
      t.DoMove(1,1);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 1);
      t.DoMove(0,0);
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 2);
      t.DoMove(1,2);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 3);
      t.DoMove(1,0);
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 4);
      t.DoMove(2,0);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 5);
      t.DoMove(0,2);
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 6);
      t.DoMove(0,1);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 7);
      t.DoMove(2,1);
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 8);
      t.DoMove(2,2);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 9);
      assert(t.GetWinner() == TicTacToe::draw);
    }
    //Check player1 wins horizontally detection
    {
      TicTacToe t;
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,2);
      assert(t.GetWinner() == TicTacToe::player1);
    }
    //Check player2 wins vertically detection
    {
      TicTacToe t;
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(2,2);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,2);
      assert(t.GetWinner() == TicTacToe::player2);
    }
    //Check player1 wins diagonally detection
    {
      TicTacToe t;
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,2);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(2,2);
      assert(t.GetWinner() == TicTacToe::player1);
    }
    //Check no-winner detection
    {
      TicTacToe t;
      t.DoMove(1,1);
      t.DoMove(0,0);
      t.DoMove(1,2);
      t.DoMove(1,0);
      t.DoMove(2,0);
      t.DoMove(0,2);
      t.DoMove(0,1);
      t.DoMove(2,1);
      //t.DoMove(2,2); //Final move to make a draw
      assert(t.GetWinner() == TicTacToe::no_winner);
    }
    //Check CanDoMove
    for (int i=0; i!=9; ++i)
    {
      TicTacToe t;
      t.DoMove(i/3,i%3);
      assert(t.CanDoMove(i/3,i%3)==false);
    }
    //Check all states
    //59049 = 3^10
    for (int i=0; i!=59049; ++i)
    {
      try
      {
        TicTacToe t(i);
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

const boost::shared_ptr<ribi::TextCanvas> ribi::TicTacToe::ToTextCanvas() const noexcept
{
  boost::shared_ptr<TextCanvas> c {
    new TextCanvas(3,3)
  };
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      switch (GetSquare(x,y))
      {
        case 0: c->PutChar(x,y,'.'); break;
        case 1: c->PutChar(x,y,'X'); break;
        case 2: c->PutChar(x,y,'O'); break;
        default: //OK
          break;
      }
    }
  }
  return c;
}


std::ostream& ribi::operator<<(std::ostream& os,const TicTacToe& t)
{
  os
    << t.GetSquare(0,0)
    << t.GetSquare(1,0)
    << t.GetSquare(2,0)
    << '\n'
    << t.GetSquare(0,1)
    << t.GetSquare(1,1)
    << t.GetSquare(2,1)
    << '\n'
    << t.GetSquare(0,2)
    << t.GetSquare(1,2)
    << t.GetSquare(2,2);
  return os;
}

bool ribi::operator==(const TicTacToe& lhs, const TicTacToe& rhs)
{
  return lhs.GetBoard() == rhs.GetBoard()
      && lhs.GetCurrentPlayer() == rhs.GetCurrentPlayer()
      && lhs.GetCurrentTurn() == rhs.GetCurrentTurn();
}
