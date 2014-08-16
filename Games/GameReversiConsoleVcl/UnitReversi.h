//---------------------------------------------------------------------------
/*
    Reversi, a simple board game
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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitReversiH
#define UnitReversiH
//---------------------------------------------------------------------------
#include <vector>
enum Square { empty, player1, player2 };
//---------------------------------------------------------------------------
struct Reversi
{
  Reversi(const int size);
  const std::vector<std::vector<Square> >& GetBoard() const;
  const Square GetSquare(const int x, const int y) const;
  void DoMove(const int x, const int y, const Square player);
  void SetSquare(const int x, const int y, const Square player);
  const bool IsValidMove(const int x, const int y, const Square player) const;
  const std::vector< std::pair<int,int> > GetValidMoves(const Square player) const;
  const int GetSize() const;
  const int Count(const Square player) const;

  private:
  std::vector<std::vector<Square> > mBoard;

  const bool IsValidMoveUp(const int x, const int y, const Square player) const;
  const bool IsValidMoveUpLeft(const int x, const int y, const Square player) const;
  const bool IsValidMoveLeft(const int x, const int y, const Square player) const;
  const bool IsValidMoveDownLeft(const int x, const int y, const Square player) const;
  const bool IsValidMoveDown(const int x, const int y, const Square player) const;
  const bool IsValidMoveDownRight(const int x, const int y, const Square player) const;
  const bool IsValidMoveRight(const int x, const int y, const Square player) const;
  const bool IsValidMoveUpRight(const int x, const int y, const Square player) const;

  void DoMoveUp(const int x, int y, const Square player);
  void DoMoveUpLeft(int x, int y, const Square player);
  void DoMoveLeft(int x, const int y, const Square player);
  void DoMoveDownLeft(int x, int y, const Square player);
  void DoMoveDown(const int x, int y, const Square player);
  void DoMoveDownRight(int x, int y, const Square player);
  void DoMoveRight(int x, const int y, const Square player);
  void DoMoveUpRight(int x, int y, const Square player);

};

const Square GetSquareXy(const std::vector<std::vector<Square> >& board, const int x, const int y);
const Square GetOtherPlayer(const Square player);

#endif
