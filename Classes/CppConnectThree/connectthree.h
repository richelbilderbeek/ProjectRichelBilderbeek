//---------------------------------------------------------------------------
/*
ConnectThree. A connect-three class.
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
//From http://www.richelbilderbeek.nl/CppConnectThree.htm
//---------------------------------------------------------------------------
#ifndef CONNECTTHREE_H
#define CONNECTTHREE_H
//---------------------------------------------------------------------------
#include <bitset>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/tuple/tuple.hpp>
//---------------------------------------------------------------------------
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

  bool CanDoMove(const int x, const int y) const;
  void DoMove(const int x, const int y);
  void DoMove(const Move& p);
  int GetActivePlayer() const { return m_player; }
  int GetCols() const;
  int GetRows() const;
  int GetSquare(const int x, const int y) const { return m_area[x][y]; }
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
  int GetWinner() const;
  bool IsInvalidMove(const Move& p) const;
  const Move SuggestMove(const std::bitset<3>& is_player_human) const;
  void Restart();

private:
  ~ConnectThree() {}
  friend void boost::checked_delete<>(ConnectThree*);

  //X-Y-ordered 2D std::vector
  std::vector<std::vector<int> > m_area;
  int m_player;

  bool CanDoMove(const Move& p) const;
  const Move CheckOneOther(const std::bitset<3>& is_player_human) const;
  const Move CheckTwoDiagonally() const;
  const Move CheckTwoHorizontalOwn() const;
  const Move CheckTwoOther(const std::bitset<3>& is_player_human) const;
  const Move CheckTwoVerticalOwn() const;
  const Move CreateInvalidMove() const;
  const Moves GetAllPossibleMoves() const;
  int GetNextPlayer() const;
  int GetNextPlayer(const int player) const;
  static double GetRandomUniform();
  const Moves GetTwoHorizontalOtherMoves() const;
  const Moves GetTwoVerticalOtherMoves() const;
  const Move MakeRandomMove() const;

};
//---------------------------------------------------------------------------
#endif // CONNECTTHREE_H
