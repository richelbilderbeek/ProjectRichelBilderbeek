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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "connectthree.h"

#include <algorithm>
#include <cassert>
#include <ctime>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#pragma GCC diagnostic pop

ribi::ConnectThree::ConnectThree(
  const int n_cols,
  const int n_rows)
  : m_area(n_cols, std::vector<int>(n_rows,no_player)),
    m_player(ConnectThree::player1)
{
  #ifndef NDEBUG
  Test();
  #endif
  Restart();
  //assert(m_is_player_human.size() == 3);
  assert(player1 == 0);
  assert(player2 == 1);
  assert(player3 == 2);
  assert(n_rows > 1); //Sure, a 2x2 board is useless, but should work
  assert(n_cols > 1); //Sure, a 2x2 board is useless, but should work
  assert(GetCols() == n_cols);
  assert(GetRows() == n_rows);
}

bool ribi::ConnectThree::CanDoMove(const int x, const int y) const noexcept
{
  return (
       x >= 0
    && x <  GetCols()
    && y >= 0
    && y <  GetCols()
    && m_area[x][y] == no_player);
}

bool ribi::ConnectThree::CanDoMove(const Move& p) const noexcept
{
  return CanDoMove(
    boost::tuples::get<0>(p),
    boost::tuples::get<1>(p));
}

void ribi::ConnectThree::DoMove(const int x, const int y)
{
  assert(
    (CreateInvalidMove().get<0>() == x
      && CreateInvalidMove().get<1>() == y)
    || CanDoMove(x,y));
  if (CreateInvalidMove().get<0>() == x
    && CreateInvalidMove().get<1>() == y)
  {
    return;
  }
  m_area[x][y] = m_player;
  m_player = GetNextPlayer();
}

void ribi::ConnectThree::DoMove(const Move& p)
{
  DoMove(
    boost::tuples::get<0>(p),
    boost::tuples::get<1>(p));
}

const std::string ribi::ConnectThree::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::ConnectThree::GetVersionHistory() noexcept
{
  return {
    "2010-12-28: version 0.1: initial seperation of game logic from GUI",
    "2011-01-09: version 0.2: converted square values to enum constant, fixed small constructor bug",
    "2011-01-11: version 1.0: added that the game can end in a draw. First tested and debugged version",
    "2011-04-19: version 1.1: added Restart method, removed m_is_player_human"
  };
}

int ribi::ConnectThree::GetWinner() const noexcept
{
  const int n_rows = GetRows();
  for (int y=0; y!=n_rows; ++y)
  {
    const int n_cols = GetCols();
    for (int x=0; x!=n_cols; ++x)
    {
      if (m_area[x][y] == no_player) continue;
      //Horizontal
      if (x + 2 < n_cols
        && m_area[x  ][y] == m_area[x+1][y]
        && m_area[x+1][y] == m_area[x+2][y])
      {
        return m_area[x][y];
      }
      //Vertical
      if (y + 2 < n_rows
        && m_area[x][y  ] == m_area[x][y+1]
        && m_area[x][y+1] == m_area[x][y+2])
      {
        return m_area[x][y];
      }
    }
  }
  //Check for draw
  {
    const Move m1 = MakeRandomMove();
    const Move m2 = CreateInvalidMove();
    assert(!CanDoMove(m2));
    if ( m1.get<0>() == m2.get<0>()
      && m1.get<1>() == m2.get<1>()
      && m1.get<2>() == m2.get<2>())
    {
      return draw;
    }
  }
  return no_player;
}

//bool ribi::ConnectThree::IsComputerTurn() const
//{
//  return !IsHuman(GetActivePlayer());
//}

bool ribi::ConnectThree::IsInvalidMove(const Move& p) noexcept
{
  const Move q = CreateInvalidMove();
  return
       p.get<0>() == q.get<0>()
    && p.get<1>() == q.get<1>()
    && p.get<2>() == q.get<2>();
}

///SuggestMove suggests a good move. If the game is a draw,
///it returns an invalid move.
const ribi::ConnectThree::Move ribi::ConnectThree::SuggestMove(
  const std::bitset<3>& is_player_human) const noexcept
{
  if (CanDoMove(CheckTwoHorizontalOwn())) return CheckTwoHorizontalOwn();
  if (CanDoMove(CheckTwoVerticalOwn()  )) return CheckTwoVerticalOwn();
  if (CanDoMove(CheckTwoOther(is_player_human))) return CheckTwoOther(is_player_human);
  if (CanDoMove(CheckTwoDiagonally()   )) return CheckTwoDiagonally();
  if (CanDoMove(CheckOneOther(is_player_human)        )) return CheckOneOther(is_player_human);
  return MakeRandomMove();
}

const ribi::ConnectThree::Move ribi::ConnectThree::CheckTwoHorizontalOwn() const noexcept
{
  const int n_rows = GetRows();
  for (int y=0; y!=n_rows; ++y)
  {
    const int n_cols = GetCols();
    for (int x=0; x!=n_cols-1; ++x) //-1 to prevent out of range
    {
      //Two consequtive selfs
      if (m_area[x][y] == m_player && m_area[x+1][y] == m_player)
      {
        if (x >= 1)
        {
          if (m_area[x-1][y] == no_player)
          {
            const Move p(x-1,y);
            assert(CanDoMove(p));
            return p;
          }
        }
        if (x < n_cols-2 && m_area[x+2][y] == no_player)
        {
          const Move p(x+2,y);
          assert(CanDoMove(p));
          return p;
        }
      }
      //Perhaps a gap?
      if (x < n_cols-2)
      {
        if (m_area[x][y] == m_player && m_area[x+1][y] == no_player && m_area[x+2][y] == m_player)
        {
          const Move p(x+1,y);
          assert(CanDoMove(p));
          return p;
        }
      }
    }
  }
  assert(!CanDoMove(CreateInvalidMove()));
  return CreateInvalidMove();
}

const ribi::ConnectThree::Move ribi::ConnectThree::CheckTwoVerticalOwn() const noexcept
{
  const int n_rows = GetRows();
  assert(n_rows > 1);
  for (int y=0; y!=n_rows-1; ++y) //-1 to prevent out of range
  {
    const int n_cols = GetCols();
    assert(n_cols > 1);
    for (int x=0; x!=n_cols; ++x)
    {
      //Two consequtive selfs?
      if (m_area[x][y] == m_player && m_area[x][y+1] == m_player)
      {
        if (y >= 1)
        {
          if (m_area[x][y-1] == no_player)
          {
            const Move p(x,y-1);
            assert(CanDoMove(p));
            return p;
          }
        }
        if (y < n_rows-2)
        {
          if (m_area[x][y+2] == no_player)
          {
            const Move p(x,y+2);
            assert(CanDoMove(p));
            return p;
          }
        }
      }
      //Perhaps a gap?
      if (y < n_rows-2)
      {
        if (m_area[x][y] == m_player && m_area[x][y+1] == no_player && m_area[x][y+2] == m_player)
        {
          const Move p(x,y+1);
          assert(CanDoMove(p));
          return p;
        }
      }
    }
  }
  assert(!CanDoMove(CreateInvalidMove()));
  return CreateInvalidMove();
}

const ribi::ConnectThree::Move ribi::ConnectThree::CheckTwoOther(
  const std::bitset<3>& is_player_human) const noexcept
{
  const Moves moves(GetAllPossibleMoves());

  const int nMoves = moves.size();
  if (nMoves==0) return CreateInvalidMove();
  {
    //Get anti-human moves
    Moves v;
    BOOST_FOREACH(const Move& m, moves)
    {
      assert(CanDoMove(m));
      //Player is human
      if (is_player_human[boost::tuples::get<2>(m)])
        v.push_back(m);
    }
    //If there are anti-player moves, choose one at random
    if (!v.empty())
    {
      const Move m = v[std::rand() % v.size()];
      assert(CanDoMove(m));
      return
        boost::tuples::make_tuple(
          boost::tuples::get<0>(m),
          boost::tuples::get<1>(m),
          boost::tuples::get<2>(m));
    }
  }
  {
    //Get moves anti-next-player
    const int next_player_index = GetNextPlayer();
    Moves v;
    BOOST_FOREACH(const Move& m, moves)
    {
      assert(CanDoMove(m));
      if (boost::tuples::get<2>(m) == next_player_index)
        v.push_back(m);
    }
    //If there are anti-next-player moves, choose one at random
    if (!v.empty())
    {
      const Move m = v[std::rand() % v.size()];
      assert(CanDoMove(m));
      return
        boost::tuples::make_tuple(
          boost::tuples::get<0>(m),
          boost::tuples::get<1>(m),
          boost::tuples::get<2>(m));
    }
  }
  //Choose a move at random
  {
    const Move m = moves[std::rand() % moves.size()];
    assert(CanDoMove(m));
    return
      boost::tuples::make_tuple(
        boost::tuples::get<0>(m),
        boost::tuples::get<1>(m),
        boost::tuples::get<2>(m));
  }
}

const ribi::ConnectThree::Move ribi::ConnectThree::CreateInvalidMove() noexcept
{
  ribi::ConnectThree::Move p(-1,-1,ConnectThree::no_player);
  return p;
}

///GetAllPossibleMoves returns all possible moves.
///* boost::get<0>: x coordinat
///* boost::get<1>: y coordinat
///* boost::get<2>: player that would dislike this move
const ribi::ConnectThree::Moves
  ribi::ConnectThree::GetAllPossibleMoves() const noexcept
{
  ribi::ConnectThree::Moves v(GetTwoHorizontalOtherMoves());
  const ribi::ConnectThree::Moves w(GetTwoVerticalOtherMoves());
  std::copy(w.begin(),w.end(),std::back_inserter(v));
  return v;
}

const ribi::ConnectThree::Moves ribi::ConnectThree::GetTwoHorizontalOtherMoves() const noexcept
{
  const int n_rows = GetRows();
  Moves moves;
  for (int y=0; y!=n_rows; ++y)
  {
    const int n_cols = GetCols();
    for (int x=0; x!=n_cols-1; ++x) //-1 to prevent out of range
    {
      //Check consequtive
      if (m_area[x][y]!=no_player && m_area[x][y] == m_area[x+1][y])
      {
        //Check A X B
        if (x > 0 && m_area[x-1][y] == no_player)
        {
          const Move m
            = boost::tuples::make_tuple(x-1,y,m_area[x][y]);
          assert(CanDoMove(m));
          moves.push_back(m);
        }
        //Check X B C
        if (x < n_cols-2 && m_area[x+2][y] == no_player)
        {
          const Move m
            = boost::tuples::make_tuple(x+2,y,m_area[x][y]);
          assert(CanDoMove(m));
          moves.push_back(m);
        }
      }
      //Check gap, also X B C
      if (m_area[x][y] != no_player && x + 2 < n_cols && m_area[x+1][y] == no_player && m_area[x][y] == m_area[x+2][y])
      {
        const Move m
          = boost::tuples::make_tuple(x+1,y,m_area[x][y]);
        assert(CanDoMove(m));
        moves.push_back(m);
      }

    }
  }
  return moves;
}

//A X B C (x is focus of for loop)
const ribi::ConnectThree::Moves ribi::ConnectThree::GetTwoVerticalOtherMoves() const noexcept
{
  const int n_rows = GetRows();
  ribi::ConnectThree::Moves v;

  for (int y=0; y!=n_rows-1; ++y) //-1 to prevent out of range
  {
    const int n_cols = GetCols();
    for (int x=0; x!=n_cols; ++x)
    {
      //Check consequtive
      if (m_area[x][y] != no_player && m_area[x][y] == m_area[x][y+1])
      {
        //Check A X B
        if (y > 0 && m_area[x][y-1] == no_player)
        {
          const Move m = boost::tuples::make_tuple(x,y-1,m_area[x][y]);
          assert(CanDoMove(m));
          v.push_back(m);
        }
        //Check X B C
        if (y < n_rows-2 && m_area[x][y+2] == no_player)
        {
          const Move m = boost::tuples::make_tuple(x,y+2,m_area[x][y]);
          assert(CanDoMove(m));
          v.push_back(m);
        }
      }
      //Check gap, also X B C
      if (m_area[x][y] != no_player && y < n_rows && m_area[x][y+1] == no_player && m_area[x][y] == m_area[x][y+2])
      {
        const Move m = boost::tuples::make_tuple(x,y+1,m_area[x][y]);
        assert(CanDoMove(m));
        v.push_back(m);
      }
    }
  }
  return v;
}

const ribi::ConnectThree::Move ribi::ConnectThree::CheckTwoDiagonally() const noexcept
{
  ribi::ConnectThree::Moves v;

  const int n_rows = GetRows();
  for (int y=0; y!=n_rows-1; ++y) //-1 To prevent out of range
  {
    const int n_cols = GetCols();
    for (int x=0; x!=n_cols-1; ++x) //-1 to prevent out of range
    {
      if (m_area[x][y] == m_player && m_area[x+1][y+1] == m_player)
      {
        if (m_area[x+1][y] == no_player)
        {
          const Move m = boost::tuples::make_tuple(x+1,y,m_area[x][y]);
          assert(CanDoMove(m));
          v.push_back(m);
        }
        if (m_area[x][y+1] == no_player)
        {
          const Move m = boost::tuples::make_tuple(x,y+1,m_area[x][y]);
          assert(CanDoMove(m));
          v.push_back(m);
        }
      }
    }
  }
  if (v.empty()) return CreateInvalidMove();
  const Move m = v[std::rand() % v.size()];
  assert(CanDoMove(m));
  return m;
}

const ribi::ConnectThree::Move ribi::ConnectThree::CheckOneOther(
  const std::bitset<3>& is_player_human) const noexcept
{
  ribi::ConnectThree::Moves v;

  const int n_rows = GetRows();

  for (int y=0; y!=n_rows; ++y)
  {
    const int n_cols = GetCols();
    for (int x=0; x!=n_cols; ++x)
    {
      if (m_area[x][y] != no_player)
      {
        if (y >= 1 && m_area[x][y-1] == no_player)
        {
          const Move m = boost::tuples::make_tuple(x,y-1,m_area[x][y]);
          assert(CanDoMove(m));
          v.push_back(m);
        }
        if (y < n_rows-1)
        {
          if (m_area[x][y+1] == no_player)
          {
            const Move m = boost::tuples::make_tuple(x,y+1,m_area[x][y]);
            assert(CanDoMove(m));
            v.push_back(m);
          }
        }
        if (x >= 1)
        {
          if (m_area[x-1][y] == no_player)
          {
            const Move m = boost::tuples::make_tuple(x-1,y,m_area[x][y]);
            assert(CanDoMove(m));
            v.push_back(m);
          }
        }
        if (x < n_cols-1)
        {
          if (m_area[x+1][y] == no_player)
          {
            const Move m = boost::tuples::make_tuple(x+1,y,m_area[x][y]);
            assert(CanDoMove(m));
            v.push_back(m);
          }
        }
      }
    }
  }
  if (v.empty()) return CreateInvalidMove();

  {
    //Get anti-human moves
    Moves w;
    BOOST_FOREACH(const Move& m, v)
    {
      assert(CanDoMove(m));
      if (is_player_human[boost::tuples::get<2>(m)])
        w.push_back(m);
    }
    //If there are anti-player moves, choose one at random
    if (!w.empty())
    {
      const Move m = w[std::rand() % w.size()]; //ex-bug ('w.size()' was 'v.size()')
      assert(CanDoMove(m));
      return
        boost::tuples::make_tuple(
          boost::tuples::get<0>(m),
          boost::tuples::get<1>(m),
          boost::tuples::get<2>(m));
    }
  }

  {
    //Get moves anti-next-player
    const int next_player_index = GetNextPlayer();
    Moves w;
    BOOST_FOREACH(const Move& m, v)
    {
      assert(CanDoMove(m));
      if (boost::tuples::get<2>(m) == next_player_index)
        w.push_back(m);
    }
    //If there are anti-next-player moves, choose one at random
    if (!w.empty())
    {
      const Move m = w[std::rand() % w.size()];
      assert(CanDoMove(m));
      return
        boost::tuples::make_tuple(
          boost::tuples::get<0>(m),
          boost::tuples::get<1>(m),
          boost::tuples::get<2>(m));
    }
  }
  //Choose a move at random
  {
    const Move m = v[std::rand() % v.size()];
    assert(CanDoMove(m));
    return
      boost::tuples::make_tuple(
        boost::tuples::get<0>(m),
        boost::tuples::get<1>(m),
        boost::tuples::get<2>(m));
  }
}

const ribi::ConnectThree::Move ribi::ConnectThree::MakeRandomMove() const noexcept
{
  std::vector<boost::tuple<int,int,int> > v;
  const int n_cols = GetCols();
  const int n_rows = GetRows();

  for (int y=0; y!=n_rows; ++y)
  {
    for (int x=0; x!=n_cols; ++x)
    {
      if (this->GetSquare(x,y) == no_player)
      {
        v.push_back(boost::tuples::make_tuple(
          x,
          y,
          static_cast<int>(no_player)));
      }
    }
  }
  if (v.empty())
  {
    assert(!CanDoMove(CreateInvalidMove()));
    return this->CreateInvalidMove();
  }
  const int index = std::rand() % v.size();
  return v[index];
}

int ribi::ConnectThree::GetCols() const noexcept
{
  assert(!m_area.empty());
  return m_area.size();
}

int ribi::ConnectThree::GetNextPlayer(const int player) const noexcept
{
  assert(player!=no_player);
  switch (player)
  {
    case player1: return player2;
    case player2: return player3;
    case player3: return player1;
  }
  assert(!"Should not get here");
  return no_player;
}

int ribi::ConnectThree::GetNextPlayer() const noexcept
{
  return GetNextPlayer(m_player);
}

//From http://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double ribi::ConnectThree::GetRandomUniform() noexcept
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}

int ribi::ConnectThree::GetRows() const noexcept
{
  assert(!m_area.empty());
  return m_area[0].size();
}

void ribi::ConnectThree::Restart() noexcept
{
  m_area = std::vector<std::vector<int> >(GetCols(),
    std::vector<int>(GetRows(),no_player));
  m_player = ribi::ConnectThree::player1;
}

#ifndef NDEBUG
void ribi::ConnectThree::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Can a 2x2 game be played without exceptions thrown
  const int n_rows = 2;
  const int n_cols = 2;
  ConnectThree c(n_cols,n_rows);
  std::bitset<3> is_player_human;
  is_player_human[0] = true;
  is_player_human[1] = true;
  is_player_human[2] = true;
  assert(c.GetCols() == n_cols);
  assert(c.GetRows() == n_rows);
  assert(c.GetActivePlayer() == ConnectThree::player1);
  assert( c.CanDoMove(0,0));
  assert( c.CanDoMove(0,1));
  assert( c.CanDoMove(1,0));
  assert( c.CanDoMove(1,1));
  assert(!c.IsInvalidMove(Move(0,0)));
  assert( c.IsInvalidMove(Move(0,n_rows)));
  assert( c.IsInvalidMove(Move(n_rows,0)));
  assert(!IsInvalidMove( c.SuggestMove(is_player_human))); //No moves left
  assert(c.GetWinner() == ConnectThree::no_player); //No winner yet
  c.DoMove(0,0);
  assert(c.GetActivePlayer() == ConnectThree::player2);
  assert(!c.CanDoMove(0,0));
  assert( c.CanDoMove(0,1));
  assert( c.CanDoMove(1,0));
  assert( c.CanDoMove(1,1));
  assert(!IsInvalidMove(c.SuggestMove(is_player_human))); //No moves left
  assert(c.GetWinner() == ConnectThree::no_player); //No winner yet
  c.DoMove(0,1);
  assert(c.GetActivePlayer() == ConnectThree::player3);
  assert(!c.CanDoMove(0,0));
  assert(!c.CanDoMove(0,1));
  assert( c.CanDoMove(1,0));
  assert( c.CanDoMove(1,1));
  assert(!IsInvalidMove(c.SuggestMove(is_player_human))); //No moves left
  assert(c.GetWinner() == ConnectThree::no_player); //No winner yet
  c.DoMove(1,0);
  assert(c.GetActivePlayer() == ConnectThree::player1);
  assert(!c.CanDoMove(0,0));
  assert(!c.CanDoMove(0,1));
  assert(!c.CanDoMove(1,0));
  assert( c.CanDoMove(1,1));
  assert(!IsInvalidMove(c.SuggestMove(is_player_human))); //No moves left
  assert(c.GetWinner() == ConnectThree::no_player); //No winner yet
  c.DoMove(1,1);
  assert(c.GetActivePlayer() == ConnectThree::player2);
  assert(!c.CanDoMove(0,0));
  assert(!c.CanDoMove(0,1));
  assert(!c.CanDoMove(1,0));
  assert(!c.CanDoMove(1,1));
  assert( IsInvalidMove(c.SuggestMove(is_player_human))); //No moves left
  assert(c.GetWinner() == ConnectThree::draw);
}
#endif
