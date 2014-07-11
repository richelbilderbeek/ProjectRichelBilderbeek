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
#pragma hdrstop

#include "UnitReversi.h"
//---------------------------------------------------------------------------
#include <cassert>
//---------------------------------------------------------------------------
Reversi::Reversi(const int size)
  : mBoard(size,std::vector<Square>(size,empty))
{
  assert( size > 0);
  assert( mBoard.size() == mBoard[0].size() );

  const int x = size / 2 - 1;
  const int y = size / 2 - 1;
  SetSquare(x  ,y  ,player1);
  SetSquare(x+1,y  ,player2);
  SetSquare(x  ,y+1,player2);
  SetSquare(x+1,y+1,player1);
}
//---------------------------------------------------------------------------
const std::vector<std::vector<Square> >& Reversi::GetBoard() const
{
  return mBoard;
}
//---------------------------------------------------------------------------
const Square Reversi::GetSquare(const int x, const int y) const
{
  return GetSquareXy(mBoard,x,y);
}
//---------------------------------------------------------------------------
//Simply sets a square
void Reversi::SetSquare(const int x, const int y, const Square player)
{
  assert(player != empty);

  mBoard[y][x] = player;

  assert(GetSquare(x,y)==player);
}
//---------------------------------------------------------------------------
//Do a complete move
void Reversi::DoMove(const int x, const int y, const Square player)
{
  assert(IsValidMove(x,y,player)==true || "Invalid move!");

  if (IsValidMoveUp(       x,y,player) == true) DoMoveUp(       x  ,y-1,player);
  if (IsValidMoveUpLeft(   x,y,player) == true) DoMoveUpLeft(   x-1,y-1,player);
  if (IsValidMoveLeft(     x,y,player) == true) DoMoveLeft(     x-1,y  ,player);
  if (IsValidMoveDownLeft( x,y,player) == true) DoMoveDownLeft( x-1,y+1,player);
  if (IsValidMoveDown(     x,y,player) == true) DoMoveDown(     x  ,y+1,player);
  if (IsValidMoveDownRight(x,y,player) == true) DoMoveDownRight(x+1,y+1,player);
  if (IsValidMoveRight(    x,y,player) == true) DoMoveRight(    x+1,y  ,player);
  if (IsValidMoveUpRight(  x,y,player) == true) DoMoveUpRight(  x+1,y-1,player);
  SetSquare(x,y,player);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
const bool Reversi::IsValidMove(const int x, const int y, const Square player) const
{
  if (IsValidMoveUp(       x,y,player)==true) return true;
  if (IsValidMoveUpLeft(   x,y,player)==true) return true;
  if (IsValidMoveLeft(     x,y,player)==true) return true;
  if (IsValidMoveDownLeft( x,y,player)==true) return true;
  if (IsValidMoveDown(     x,y,player)==true) return true;
  if (IsValidMoveDownRight(x,y,player)==true) return true;
  if (IsValidMoveRight(    x,y,player)==true) return true;
  if (IsValidMoveUpRight(  x,y,player)==true) return true;
  return false;
}
//---------------------------------------------------------------------------
const bool Reversi::IsValidMoveUp(const int x, const int y, const Square player) const
{
  int b = y - 1;
  if (b < 1) return false;
  if (GetSquare(x,b) != GetOtherPlayer(player)) return false;
  while (b > 0)
  {
    b--;
    if (GetSquare(x,b) == player) return true;
    if (GetSquare(x,b) == empty) return false;
  }
  return false;
}
//---------------------------------------------------------------------------
const bool Reversi::IsValidMoveUpLeft(const int x, const int y, const Square player) const
{
  int a = x - 1;
  int b = y - 1;
  if (a < 1 || b < 1) return false;
  if (GetSquare(a,b) != GetOtherPlayer(player)) return false;
  while (a > 0 && b > 0)
  {
    a--;
    b--;
    if (GetSquare(a,b) == player) return true;
    if (GetSquare(a,b) == empty) return false;
  }
  return false;
}
//---------------------------------------------------------------------------
const bool Reversi::IsValidMoveLeft(const int x, const int y, const Square player) const
{
  int a = x - 1;
  if (a < 1) return false;
  if (GetSquare(a,y) != GetOtherPlayer(player)) return false;
  while (a > 0)
  {
    a--;
    if (GetSquare(a,y) == player) return true;
    if (GetSquare(a,y) == empty) return false;
  }
  return false;
}
//---------------------------------------------------------------------------
const bool Reversi::IsValidMoveDownLeft(const int x, const int y, const Square player) const
{
  const int size = mBoard.size();
  int a = x - 1;
  int b = y + 1;

  if (a < 1) return false;
  if (b > size -1 ) return false;
  if (GetSquare(a,b) != GetOtherPlayer(player)) return false;
  while (a > 0 && b < size - 1)
  {
    a--;
    b++;
    if (GetSquare(a,b) == player) return true;
    if (GetSquare(a,b) == empty) return false;
  }
  return false;
}
//---------------------------------------------------------------------------
const bool Reversi::IsValidMoveDown(const int x, const int y, const Square player) const
{
  const int size = mBoard.size();
  int b = y + 1;
  if (b > size -1 ) return false;
  if (GetSquare(x,b) != GetOtherPlayer(player)) return false;
  while (b < size - 1)
  {
    b++;
    if (GetSquare(x,b) == player) return true;
    if (GetSquare(x,b) == empty ) return false;
  }
  return false;
}
//---------------------------------------------------------------------------
const bool Reversi::IsValidMoveDownRight(const int x, const int y, const Square player) const
{
  const int size = mBoard.size();
  int a = x + 1;
  int b = y + 1;
  if (a > size - 1) return false;
  if (b > size -1 ) return false;
  if (GetSquare(a,b) != GetOtherPlayer(player)) return false;
  while (a < size - 1 && b < size - 1)
  {
    b++;
    a++;
    if (GetSquare(a,b) == player) return true;
    if (GetSquare(a,b) == empty ) return false;
  }
  return false;
}
//---------------------------------------------------------------------------
const bool Reversi::IsValidMoveRight(const int x, const int y, const Square player) const
{
  const int size = mBoard.size();
  int a = x + 1;
  if (a > size - 1) return false;
  if (GetSquare(a,y) != GetOtherPlayer(player)) return false;
  while (a < size - 1)
  {
    a++;
    if (GetSquare(a,y) == player) return true;
    if (GetSquare(a,y) == empty) return false;
  }
  return false;
}
//---------------------------------------------------------------------------
const bool Reversi::IsValidMoveUpRight(const int x, const int y, const Square player) const
{
  const int size = mBoard.size();
  int a = x + 1;
  int b = y - 1;
  if (a > size - 1) return false;
  if (b < 1) return false;
  if (GetSquare(a,b) != GetOtherPlayer(player)) return false;
  while (a < size - 1 && b > 0)
  {
    a++;
    b--;
    if (GetSquare(a,b) == player) return true;
    if (GetSquare(a,b) == empty) return false;
  }
  return false;
}
//---------------------------------------------------------------------------
const std::vector< std::pair<int,int> > Reversi::GetValidMoves(const Square player) const
{
  const int size = mBoard.size();
  std::vector< std::pair<int,int> > v;
  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      if (IsValidMove(x,y,player)==true)
      {
        v.push_back( std::make_pair(x,y) );
      }
    }
  }
  return v;
}
//---------------------------------------------------------------------------
void Reversi::DoMoveUp(const int x, int y, const Square player)
{
  while ( GetSquare(x,y) == GetOtherPlayer(player) )
  {
    SetSquare(x,y,player);
    --y;
  }
}
//---------------------------------------------------------------------------
void Reversi::DoMoveUpLeft(int x, int y, const Square player)
{
  while ( GetSquare(x,y) == GetOtherPlayer(player) )
  {
    SetSquare(x,y,player);
    --y;
    --x;
  }
}
//---------------------------------------------------------------------------
void Reversi::DoMoveLeft(int x, const int y, const Square player)
{
  while ( GetSquare(x,y) == GetOtherPlayer(player) )
  {
    SetSquare(x,y,player);
    --x;
  }

}
//---------------------------------------------------------------------------
void Reversi::DoMoveDownLeft(int x, int y, const Square player)
{
  while ( GetSquare(x,y) == GetOtherPlayer(player) )
  {
    SetSquare(x,y,player);
    ++y;
    --x;
  }
}
//---------------------------------------------------------------------------
void Reversi::DoMoveDown(const int x, int y, const Square player)
{
  while ( GetSquare(x,y) == GetOtherPlayer(player) )
  {
    SetSquare(x,y,player);
    ++y;
  }
}
//---------------------------------------------------------------------------
void Reversi::DoMoveDownRight(int x, int y, const Square player)
{
  while ( GetSquare(x,y) == GetOtherPlayer(player) )
  {
    SetSquare(x,y,player);
    ++y;
    ++x;
  }
}
//---------------------------------------------------------------------------
void Reversi::DoMoveRight(int x, const int y, const Square player)
{
  while ( GetSquare(x,y) == GetOtherPlayer(player) )
  {
    SetSquare(x,y,player);
    ++x;
  }
}
//---------------------------------------------------------------------------
void Reversi::DoMoveUpRight(int x, int y, const Square player)
{
  while ( GetSquare(x,y) == GetOtherPlayer(player) )
  {
    SetSquare(x,y,player);
    --y;
    ++x;
  }
}
//---------------------------------------------------------------------------
const int Reversi::GetSize() const
{
  return mBoard.size();
}
//---------------------------------------------------------------------------
const int Reversi::Count(const Square player) const
{
  const int size = GetSize();

  int sum = 0;

  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      if (mBoard[x][y] == player) ++sum;
    }
  }
  return sum;
}
//---------------------------------------------------------------------------
const Square GetOtherPlayer(const Square player)
{
  switch (player)
  {
    case player1: return player2;
    case player2: return player1;
  }
  assert(!"Invalid player");
  return empty;
}
//---------------------------------------------------------------------------
const Square GetSquareXy(
  const std::vector<std::vector<Square> >& board,
  const int x, const int y)
{
  const int size = board.size();
  assert(x >= 0);
  assert(y >= 0);
  assert(x < size);
  assert(y < size);
  return board[y][x];
}
//---------------------------------------------------------------------------


#pragma package(smart_init)
