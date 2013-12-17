//---------------------------------------------------------------------------
/*
Reversi, Reversi game class
Copyright (C) 2007  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolTestReversi.htm
//---------------------------------------------------------------------------
#ifndef REVERSI_H
#define REVERSI_H

#include <string>
#include <vector>

struct Reversi
{
  enum { empty   = 0};
  enum { player1 = 1};
  enum { player2 = 2};

  Reversi(const int size);

  bool CanDoMove(const int x, const int y) const;

  int Count(const int player) const;

  void DoMove(const int x, const int y);

  const std::vector<std::vector<int> >& GetBoard() const;

  int Get(const int x, const int y) const;

  int GetCurrentPlayer() const { return m_current_player; }

  int GetOtherPlayer() const;

  int GetSize() const;

  static const std::string GetVersion() { return "1.1"; }
  static const std::vector<std::string> GetVersionHistory();



  const std::vector< std::pair<int,int> > GetValidMoves() const;


  private:
  std::vector<std::vector<int> > m_board;
  int m_current_player;

  bool CanDoMoveUp(const int x, const int y) const;
  bool CanDoMoveUpLeft(const int x, const int y) const;
  bool CanDoMoveLeft(const int x, const int y) const;
  bool CanDoMoveDownLeft(const int x, const int y) const;
  bool CanDoMoveDown(const int x, const int y) const;
  bool CanDoMoveDownRight(const int x, const int y) const;
  bool CanDoMoveRight(const int x, const int y) const;
  bool CanDoMoveUpRight(const int x, const int y) const;

  void DoMoveUp(const int x, const int y);
  void DoMoveUpLeft(const int x, const int y);
  void DoMoveLeft(const int x, const int y);
  void DoMoveDownLeft(const int x, const int y);
  void DoMoveDown(const int x, const int y);
  void DoMoveDownRight(const int x, const int y);
  void DoMoveRight(const int x, const int y);
  void DoMoveUpRight(const int x, const int y);

  ///GetSurroundingCoordinats returns the surrounding
  ///coordinats in all eight directions for a given coordinat,
  ///in chronological direction.
  ///In the resulting std::vectors, this coordinat is omitted.
  const std::vector<std::vector<std::pair<int,int> > >
    GetSurroundingCoordinats(const int x,const int y) const;

  void TogglePlayer();

  void Set(const int x, const int y, const int state);

};

#endif // REVERSI_H
