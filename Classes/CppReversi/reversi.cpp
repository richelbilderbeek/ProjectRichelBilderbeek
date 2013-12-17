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
#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>

#include "reversi.h"
#pragma GCC diagnostic pop

ribi::Reversi::Reversi(const int size)
  : m_board(size,std::vector<int>(size,empty)),
    m_current_player(player1)
{
  assert( size > 0);
  assert( m_board.size() == m_board[0].size() );

  const int x = size / 2 - 1;
  const int y = size / 2 - 1;
  Set(x  ,y  ,player1);
  Set(x+1,y  ,player2);
  Set(x  ,y+1,player2);
  Set(x+1,y+1,player1);
}

bool ribi::Reversi::CanDoMove(const int x, const int y) const
{
  assert(x >= 0);
  assert(y >= 0);
  assert(!"TODO");
  return false;
  /*
  typedef std::pair<int,int> Coordinat;
  typedef std::vector<Coordinat> Line;
  const std::vector<Line> v = GetSurroundingCoordinats(x,y);

  BOOST_FOREACH(const Line& line, v)
  {
    int state = 0;
    BOOST_FOREACH(const Coordinat& c, line)
    {
      switch (state)
      {
        case 0: //0 = first square, must be other player
          state = (Get(c.first,c.second) == GetOtherPlayer() ? 1 : -1);
          break;
        case 1: //1 = second to seventh square, must not be player
        {
          switch(Get(c.first,c.second)
          {
            case (GetCurrentPlayer() ? -1 : 1);
          state = (Get(c.first,c.second) == GetCurrentPlayer() ? -1 : 1);
        }
      }
    }
  }
  */
}

//Do a complete move
void ribi::Reversi::DoMove(const int x, const int y)
{
  assert(CanDoMove(x,y)==true || "Invalid move!");
  const int player = GetCurrentPlayer();
  if (CanDoMoveUp(       x,y)) DoMoveUp(       x  ,y-1);
  if (CanDoMoveUpLeft(   x,y)) DoMoveUpLeft(   x-1,y-1);
  if (CanDoMoveLeft(     x,y)) DoMoveLeft(     x-1,y  );
  if (CanDoMoveDownLeft( x,y)) DoMoveDownLeft( x-1,y+1);
  if (CanDoMoveDown(     x,y)) DoMoveDown(     x  ,y+1);
  if (CanDoMoveDownRight(x,y)) DoMoveDownRight(x+1,y+1);
  if (CanDoMoveRight(    x,y)) DoMoveRight(    x+1,y  );
  if (CanDoMoveUpRight(  x,y)) DoMoveUpRight(  x+1,y-1);
  Set(x,y,player);
}

int ribi::Reversi::Get(const int x, const int y) const
{
  const int sz = GetSize();
  assert(x >= 0);
  assert(y >= 0);
  assert(x < sz);
  assert(y < sz);
  return m_board[y][x];
}

const std::vector<std::string> ribi::Reversi::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back(std::string("YYYY-MM-DD: version X.Y: [descripion]"));
  v.push_back(std::string(
    "2007-09-24: version 1.0: "
    "initial version developed under C++ Builder"));
  v.push_back(std::string(
    "2010-09-24: version 1.1: "
    "initial port to Qt Creator"));
  return v;
}

//Simply sets a square
void ribi::Reversi::Set(const int x, const int y, const int state)
{
  assert(x>=0 && x < GetSize());
  assert(y>=0 && y < GetSize());
  m_board[y][x] = state;
  assert(Get(x,y)==state);
  TogglePlayer();
}

void ribi::Reversi::TogglePlayer()
{
  switch (GetCurrentPlayer())
  {
    case player1: m_current_player = player2; return;
    case player2: m_current_player = player1; return;
    default: assert(!"Should not get here");
  }
}



bool ribi::Reversi::CanDoMoveUp(const int x, const int y) const
{
  int b = y - 1;
  if (b < 1) return false;
  if ( Get(x,b) != empty
    || Get(x,b) != GetOtherPlayer()) return false;
  const int player = GetCurrentPlayer();
  while (b > 0)
  {
    b--;
    if (Get(x,b) == player) return true;
    if (Get(x,b) == empty) return false;
  }
  return false;
}

bool ribi::Reversi::CanDoMoveUpLeft(const int x, const int y) const
{
  int a = x - 1;
  int b = y - 1;
  if (a < 1 || b < 1) return false;
  if (Get(a,b) != GetOtherPlayer()) return false;
  const int player = GetCurrentPlayer();
  while (a > 0 && b > 0)
  {
    a--;
    b--;
    if (Get(a,b) == player) return true;
    if (Get(a,b) == empty) return false;
  }
  return false;
}

bool ribi::Reversi::CanDoMoveLeft(const int x, const int y) const
{
  int a = x - 1;
  if (a < 1) return false;
  if (Get(a,y) != GetOtherPlayer()) return false;
  const int player = GetCurrentPlayer();
  while (a > 0)
  {
    a--;
    if (Get(a,y) == player) return true;
    if (Get(a,y) == empty) return false;
  }
  return false;
}

bool ribi::Reversi::CanDoMoveDownLeft(const int x, const int y) const
{
  const int size = m_board.size();
  int a = x - 1;
  int b = y + 1;

  if (a < 1) return false;
  if (b > size -1 ) return false;
  if (Get(a,b) != GetOtherPlayer()) return false;
  const int player = GetCurrentPlayer();
  while (a > 0 && b < size - 1)
  {
    a--;
    b++;
    if (Get(a,b) == player) return true;
    if (Get(a,b) == empty) return false;
  }
  return false;
}

bool ribi::Reversi::CanDoMoveDown(const int x, const int y) const
{
  const int sz = m_board.size();
  int b = y;
  if (b == sz - 1 ) return false;
  if (Get(x,b) != GetOtherPlayer()) return false;
  const int player = GetCurrentPlayer();
  while (b != sz)
  {
    b++;
    if (Get(x,b) == player) return true;
    if (Get(x,b) == empty ) return false;
  }
  return false;
}

bool ribi::Reversi::CanDoMoveDownRight(const int x, const int y) const
{
  const int size = m_board.size();
  int a = x + 1;
  int b = y + 1;
  if (a > size - 1) return false;
  if (b > size -1 ) return false;
  if (Get(a,b) != GetOtherPlayer()) return false;
  const int player = GetCurrentPlayer();
  while (a < size - 1 && b < size - 1)
  {
    b++;
    a++;
    if (Get(a,b) == player) return true;
    if (Get(a,b) == empty ) return false;
  }
  return false;
}

bool ribi::Reversi::CanDoMoveRight(const int x, const int y) const
{
  const int size = m_board.size();
  int a = x + 1;
  if (a > size - 1) return false;
  if (Get(a,y) != GetOtherPlayer()) return false;
  const int player = GetCurrentPlayer();
  while (a < size - 1)
  {
    a++;
    if (Get(a,y) == player) return true;
    if (Get(a,y) == empty) return false;
  }
  return false;
}

bool ribi::Reversi::CanDoMoveUpRight(const int x, const int y) const
{
  const int size = m_board.size();
  int a = x + 1;
  int b = y - 1;
  if (a > size - 1) return false;
  if (b < 1) return false;
  if (Get(a,b) != GetOtherPlayer()) return false;
  const int player = GetCurrentPlayer();
  while (a < size - 1 && b > 0)
  {
    a++;
    b--;
    if (Get(a,b) == player) return true;
    if (Get(a,b) == empty) return false;
  }
  return false;
}

const std::vector< std::pair<int,int> > ribi::Reversi::GetValidMoves() const
{
  const int size = m_board.size();
  std::vector< std::pair<int,int> > v;
  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      if (CanDoMove(x,y))
      {
        v.push_back( std::make_pair(x,y) );
      }
    }
  }
  return v;
}

void ribi::Reversi::DoMoveUp(const int x, int y)
{
  const int player = GetCurrentPlayer();
  while ( Get(x,y) == GetOtherPlayer() )
  {
    Set(x,y,player);
    --y;
  }
}

void ribi::Reversi::DoMoveUpLeft(int x, int y)
{
  const int player = GetCurrentPlayer();
  while ( Get(x,y) == GetOtherPlayer() )
  {
    Set(x,y,player);
    --y;
    --x;
  }
}

void ribi::Reversi::DoMoveLeft(int x, const int y)
{
  const int player = GetCurrentPlayer();
  while ( Get(x,y) == GetOtherPlayer() )
  {
    Set(x,y,player);
    --x;
  }

}

void ribi::Reversi::DoMoveDownLeft(int x, int y)
{
  const int player = GetCurrentPlayer();
  while ( Get(x,y) == GetOtherPlayer() )
  {
    Set(x,y,player);
    ++y;
    --x;
  }
}

void ribi::Reversi::DoMoveDown(const int x, int y)
{
  const int player = GetCurrentPlayer();
  while ( Get(x,y) == GetOtherPlayer() )
  {
    Set(x,y,player);
    ++y;
  }
}

void ribi::Reversi::DoMoveDownRight(int x, int y)
{
  const int player = GetCurrentPlayer();
  while ( Get(x,y) == GetOtherPlayer() )
  {
    Set(x,y,player);
    ++y;
    ++x;
  }
}

void ribi::Reversi::DoMoveRight(int x, const int y)
{
  const int player = GetCurrentPlayer();
  while ( Get(x,y) == GetOtherPlayer() )
  {
    Set(x,y,player);
    ++x;
  }
}

void ribi::Reversi::DoMoveUpRight(int x, int y)
{
  const int player = GetCurrentPlayer();
  while ( Get(x,y) == GetOtherPlayer() )
  {
    Set(x,y,player);
    --y;
    ++x;
  }
}

int ribi::Reversi::GetSize() const
{
  return m_board.size();
}

///GetSurroundingCoordinats returns the surrounding
///coordinats in all eight directions for a given coordinat,
///in chronological direction.
///In the resulting std::vectors, this coordinat is omitted.
const std::vector<std::vector<std::pair<int,int> > >
  ribi::Reversi::GetSurroundingCoordinats(const int x, const int y) const
{
  const int sz = GetSize();
  std::vector<std::vector<std::pair<int,int> > > v;
  //Directions are clockwise, where direction 0 denotes up
  for (int direction=0; direction!=8; ++direction)
  {
    int dx = 0;
    switch (direction)
    {
      case 1: case 2: case 3: dx =  1; break;
      case 5: case 6: case 7: dx = -1; break;
      default: break; //dx remains 0
    }
    int dy = 0;
    switch (direction)
    {
      case 7: case 0: case 1: dy = -1; break;
      case 3: case 4: case 5: dy =  1; break;
      default: break; //dy remains 0
    }
    std::vector<std::pair<int,int> > w;
    for (int i=1; i!=sz; ++i)
    {
      const int xs = x + (i*dx);
      const int ys = y + (i*dy);
      if (xs < 0 || ys < 0 || xs == sz || ys == sz) break;
      w.push_back(std::make_pair(xs,ys));
    }
    v.push_back(w);
  }
  //Also empty std::vectors are put in v
  assert(v.size() == 8);
  return v;
}

int ribi::Reversi::Count(const int player) const
{
  const int size = GetSize();

  int sum = 0;

  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      if (m_board[x][y] == player) ++sum;
    }
  }
  return sum;
}

int ribi::Reversi::GetOtherPlayer() const
{
  switch (GetCurrentPlayer())
  {
    case player1: return player2;
    case player2: return player1;
    default: assert(!"Should not get here");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::Reversi::GetOtherPlayer: invalid player");
}

