 //---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game class
Copyright (C) 2010-2015 Richel Bilderbeek

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
#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include <iosfwd>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/multi_array.hpp>

#include "tictactoeplayer.h"
#include "tictactoesquare.h"
#include "tictactoewinner.h"
#include "tictactoefwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tictactoe {

///Board is a dumb tic-tac-toe board class: it detects the winner, but does not
///know whose turn it is. TicTacToeGame does know this
struct Board
{
  ///TicTacToe default contructor creates an empty board,
  ///where the current turn is to player1.
  Board() noexcept;

  ///TicTacToe contructor from summized state integer.
  explicit Board(const int state);

  ///Can a player put his/her character at (x,y)?
  bool CanDoMove(const int x, const int y) const noexcept;

  ///Does the square exist?
  bool CanGetSquare(const int x, const int y) const noexcept;

  ///DoMove lets a player put his/her token at a certain position on the board.
  void DoMove(const int x, const int y, const Player player) noexcept;

  ///GetBoard returns the tic-tac-toe board.
  const boost::multi_array<Square,2>& GetBoard() const noexcept { return m_board; }

  ///GetSquare returns the content at square (x,y)
  Square GetSquare(const int x, const int y) const noexcept;

  ///GetSummarizedState returns an integer summarizing the
  ///state, which is both tic-tac-toe board and whose turn it is.
  ///In trinary, for lowest order digit:\n
  ///# : content\n
  ///0 : content of (0,0)\n
  ///1 : content of (1,0)\n
  ///2 : content of (2,0)\n
  ///3 : content of (0,1)\n
  ///4 : content of (1,1)\n
  ///5 : content of (2,1)\n
  ///6 : content of (0,2)\n
  ///7 : content of (1,2)\n
  ///8 : content of (2,2)\n
  ///9 : current turn\n
  ///Content is stored as:
  ///[#] : description\n
  /// 0  : empty\n
  /// 1  : player1\n
  /// 2  : player2\n
  int GetSummarizedState() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  Winner GetWinner() const noexcept;
  void Restart() noexcept;

  ///SetBoard sets a tic-tac-toe board.
  void SetBoard(const boost::multi_array<Square,2>& board) noexcept;

  ///SetSquare sets the value of square (x,y).
  void SetSquare(const int x, const int y, const Square square_state) noexcept;

  ///SetSummarizedState sets the board its state
  void SetSummarizedState(const int state) noexcept;

  ///Display it as a multi-line string
  std::string ToTextCanvas() const noexcept;

  boost::signals2::signal<void(Board*)> m_signal_changed;

  private:

  ///m_board stores the board in an x-y-order
  boost::multi_array<Square,2> m_board;

  ///NoEmptySquares determines whether there are no empty squares left.
  bool NoEmptySquares() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os,const Board& t) noexcept;
};

std::ostream& operator<<(std::ostream& os,const Board& t) noexcept;

bool operator==(const Board& lhs, const Board& rhs) noexcept;


} //~namespace tictactoe
} //~namespace ribi

#endif // TICTACTOEBOARD_H
