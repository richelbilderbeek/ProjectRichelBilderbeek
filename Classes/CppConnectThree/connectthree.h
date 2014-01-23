//---------------------------------------------------------------------------
/*
ConnectThree. A connect-three class.
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
//From http://www.richelbilderbeek.nl/CppConnectThree.htm
//---------------------------------------------------------------------------
#ifndef CONNECTTHREE_H
#define CONNECTTHREE_H

#include <bitset>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/tuple/tuple.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct ConnectThree
{
  typedef boost::tuple<int,int,int> Move;
  typedef std::vector<Move> Moves;
  enum { no_player = -1 };
  enum { player1   =  0 };
  enum { player2   =  1 };
  enum { player3   =  2 };
  enum { draw      =  3 };

  explicit ConnectThree(
    const int n_cols = 16,
    const int n_rows = 12);

  bool CanDoMove(const int x, const int y) const noexcept;
  void DoMove(const int x, const int y);
  void DoMove(const Move& p);
  int GetActivePlayer() const noexcept { return m_player; }
  int GetCols() const noexcept;
  int GetRows() const noexcept;
  int GetSquare(const int x, const int y) const { return m_area[x][y]; }
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///GetWinner returns the index of the winner.
  ///Returns draw if the board is full without a winner
  ///Returns no_player if there are still free squares
  int GetWinner() const noexcept;
  static bool IsInvalidMove(const Move& p) noexcept;

  void Restart() noexcept;

  ///SuggestMove suggests a good move. If the game is a draw,
  ///it returns an invalid move.
  const Move SuggestMove(const std::bitset<3>& is_player_human) const noexcept;



private:
  ~ConnectThree() noexcept {}
  friend void boost::checked_delete<>(ConnectThree*);
  friend void boost::checked_delete<>(const ConnectThree*);

  //X-Y-ordered 2D std::vector
  std::vector<std::vector<int> > m_area;
  int m_player;

  bool CanDoMove(const Move& p) const noexcept;
  const Move CheckOneOther(const std::bitset<3>& is_player_human) const noexcept;
  const Move CheckTwoDiagonally() const noexcept;
  const Move CheckTwoHorizontalOwn() const noexcept;
  const Move CheckTwoOther(const std::bitset<3>& is_player_human) const noexcept;
  const Move CheckTwoVerticalOwn() const noexcept;
  static const Move CreateInvalidMove() noexcept;
  const Moves GetAllPossibleMoves() const noexcept;
  int GetNextPlayer() const noexcept;
  int GetNextPlayer(const int player) const noexcept;
  static double GetRandomUniform() noexcept;
  const Moves GetTwoHorizontalOtherMoves() const noexcept;
  const Moves GetTwoVerticalOtherMoves() const noexcept;
  const Move MakeRandomMove() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const ConnectThree& c);


} //~namespace ribi

#endif // CONNECTTHREE_H
