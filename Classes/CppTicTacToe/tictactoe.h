//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game class
Copyright (C) 2010 Richel Bilderbeek

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
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iosfwd>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/multi_array.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///TicTacToe is a tic-tac-toe game class.
struct TicTacToe
{
  enum { empty     = 0 };
  enum { player1   = 1 };
  enum { player2   = 2 };
  enum { draw      = 3 };
  enum { no_winner = 4 };

  ///TicTacToe default contructor creates an empty board,
  ///where the current turn is to player1.
  TicTacToe();

  ///TicTacToe contructor from summized state integer.
  explicit TicTacToe(const int state);

  ///CanDoMove returns if a move at a certain position is valid.
  bool CanDoMove(const int x, const int y) const;

  ///DoMove lets m_current_player put his token at a certain
  ///position on the board.
  void DoMove(const int x, const int y);

  ///GetBoard returns the tic-tac-toe board.
  const boost::multi_array<int,2>& GetBoard() const { return m_board; }

  ///GetCurrentPlayer returns whose turn it is.
  int GetCurrentPlayer() const { return m_current_player; }

  ///GetCurrentTurn returns the turn number.
  int GetCurrentTurn() const;

  ///GetSquare returns the content at square (x,y)
  int GetSquare(const int x,const int y) const;

  ///GetSummarizedState returns an integer summarizing the
  ///state, which is both tic-tac-toe board and whose turn it is.
  int GetSummarizedState() const;

  ///GetVersion returns the TicTacToe version
  static const std::string GetVersion() { return "1.3.1"; }

  ///GetWinner returns the winner.
  ///* TicTacToe::player1   : player1 has won.
  ///* TicTacToe::player2   : player2 has won.
  ///* TicTacToe::draw      : draw.
  ///* TicTacToe::no_winner : no winner.
  ///The constant TicTacToe::empty should _not_ be returned.
  int GetWinner() const;

  ///SetBoard sets a tic-tac-toe board.
  void SetBoard(const boost::multi_array<int,2>& board);

  ///SetSquare sets the value of square (x,y).
  void SetSquare(const int x, const int y, const int square_state);

  ///SetSummarizedState sets the TicTacToe state,
  ///which is both tic-tac-toe board and whose turn it is.
  void SetSummarizedState(int state);

  private:

  ///m_board stores the board in an x-y-order.\n
  ///TicTacToe::empty : empty\n
  ///TicTacToe::player1 : occupied by player 1\n
  ///TicTacToe::player2 : occupied by player 2\n
  boost::multi_array<int,2> m_board;
  int m_current_player;

  ///NoEmptySquares determines whether there are no empty squares left.
  bool NoEmptySquares() const;

  friend std::ostream& operator<<(std::ostream& os,const TicTacToe& t);
};

std::ostream& operator<<(std::ostream& os,const TicTacToe& t);

bool operator==(const TicTacToe& lhs, const TicTacToe& rhs);

///From http://www.richelbilderbeek.nl/CppIntPower.htm
int IntPower(const int base, const int exponent);

//YYYY-MM-DD: version X.Y: [description]
//2010-09-19: version 1.3: made CanDoMove method a const method

} //~namespace ribi

#endif // TICTACTOE_H
