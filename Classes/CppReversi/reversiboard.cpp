#include "reversiboard.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>

#include "trace.h"
#pragma GCC diagnostic pop

ribi::reversi::Board::Board(const int size)
  : m_board(size,std::vector<int>(size,empty))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(size > 0);
  assert(size == this->GetSize());
  assert(m_board.size() == m_board[0].size() );

  const int x = size / 2 - 1;
  const int y = size / 2 - 1;
  Set(x  ,y  ,player1);
  Set(x+1,y  ,player2);
  Set(x  ,y+1,player2);
  Set(x+1,y+1,player1);
}

/*
ribi::reversi::Board::Board(const Board& other)
  : m_board(other.m_board)
{

}
ribi::reversi::Board& ribi::reversi::Board::operator=(const Board& other)
{
  m_board = other.m_board;
  return *this;
}
*/

bool ribi::reversi::Board::CanDoMove(const int x, const int y, const int player) const noexcept
{
  assert(x >= 0);
  assert(y >= 0);
  assert(x < this->GetSize());
  assert(y < this->GetSize());
  if (Get(x,y) != empty) return false;
  for (const std::pair<int,int> d: CreateDeltas())
  {
    int cur_x = x + d.first;
    int cur_y = y + d.second;
    //Must be a valid direction
    if (cur_x < 0 || cur_y < 0 || cur_x >= GetSize() || cur_y >= GetSize()) continue;
    //Adjacent square must be of opponent
    if (Get(cur_x,cur_y) != GetOtherPlayer(player)) continue;
    assert(Get(cur_x,cur_y) != empty);
    //Follow the trail until
    // - player is found -> Can do move
    // - empty is found -> Cannot do move
    // - other player is found -> Search on
    while (1)
    {
      cur_x += d.first;
      cur_y += d.second;
      //Must be a valid direction
      if (cur_x < 0 || cur_y < 0 || cur_x >= GetSize() || cur_y >= GetSize()) break;
      if (Get(cur_x,cur_y) == empty) break;
      if (Get(cur_x,cur_y) == player)
      {
        return true;
      }
    }
  }
  return false;
}

int ribi::reversi::Board::Count(const int player) const noexcept
{
  const int size = GetSize();

  int sum = 0;

  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      if (Get(x,y) == player) ++sum;
    }
  }
  return sum;
}

const std::vector<std::pair<int,int>> ribi::reversi::Board::CreateDeltas() noexcept
{
  std::vector<std::pair<int,int>> v;
  for (int dx = -1; dx != 2; ++dx)
  {
    for (int dy = -1; dy != 2; ++dy)
    {
      if (dx != 0 || dy != 0) v.push_back( std::make_pair(dx,dy));
    }
  }
  assert(v.size() == 8);
  return v;
}

void ribi::reversi::Board::DoMove(const int x, const int y, const int player) noexcept
{
  assert(CanDoMove(x,y,player));
  #ifndef NDEBUG
  const Board before(*this);
  #endif

  //Collect the deltas tomodify the color
  std::vector<std::pair<int,int>> v;
  for (const std::pair<int,int> d: CreateDeltas())
  {
    int cur_x = x + d.first;
    int cur_y = y + d.second;
    //Must be a valid direction
    if (cur_x < 0 || cur_y < 0 || cur_x >= GetSize() || cur_y >= GetSize()) continue;
    //Adjacent square must be of opponent
    if (Get(cur_x,cur_y) != GetOtherPlayer(player)) continue;
    assert(Get(cur_x,cur_y) != empty);
    //Follow the trail until
    // - player is found -> Can do move
    // - empty is found -> Cannot do move
    // - other player is found -> Search on
    while (1)
    {
      cur_x += d.first;
      cur_y += d.second;
      //Must be a valid direction
      if (cur_x < 0 || cur_y < 0 || cur_x >= GetSize() || cur_y >= GetSize()) break;
      if (Get(cur_x,cur_y) == empty) break;
      if (Get(cur_x,cur_y) == player)
      {
        v.push_back(d); //Found delta
        break; //Next delta
      }
    }
  }
  assert(!v.empty());

  for (const std::pair<int,int> d: v)
  {
    int cur_x = x + d.first;
    int cur_y = y + d.second;
    //Adjacent square must be of opponent
    assert(Get(cur_x,cur_y) == GetOtherPlayer(player));
    Set(cur_x,cur_y,player);
    //Follow the trail until
    // - player is found -> Can do move
    while (1)
    {
      cur_x += d.first;
      cur_y += d.second;
      //Must be a valid direction
      assert(!(cur_x < 0 || cur_y < 0 || cur_x >= GetSize() || cur_y >= GetSize()));
      if (Get(cur_x,cur_y) == player) break;
      assert(Get(cur_x,cur_y) == GetOtherPlayer(player));
      Set(cur_x,cur_y,player);
    }
  }
  Set(x,y,player);
}

int ribi::reversi::Board::Get(const int x, const int y) const noexcept
{
  #ifndef NDEBUG
  const int sz = GetSize();
  assert(x >= 0);
  assert(y >= 0);
  assert(x < sz);
  assert(y < sz);
  #endif
  return m_board[y][x];
}

const std::string ribi::reversi::Board::GetVersion() noexcept
{
  return "2.0";
}


const std::vector<std::string> ribi::reversi::Board::GetVersionHistory() noexcept
{
  return {
    "2007-09-24: version 1.0: initial version developed under C++ Builder, called Reversi",
    "2010-09-24: version 1.1: initial port to Qt Creator",
    "2013-12-19: version 2.0: split interface in reversi::Board and reversi::Widget",
  };
}

void ribi::reversi::Board::Set(const int x, const int y, const int state) noexcept
{
  assert(x>=0 && x < GetSize());
  assert(y>=0 && y < GetSize());
  m_board[y][x] = state;
  assert(Get(x,y)==state);
}

int ribi::reversi::Board::GetOtherPlayer(const int player) noexcept
{
  switch (player)
  {
    case player1: return player2;
    case player2: return player1;
    default: assert(!"Should not get here");
  }
  assert(!"Should not get here");
  throw std::logic_error("Board::GetOtherPlayer: unknown player");
}


const std::vector<std::pair<int,int>> ribi::reversi::Board::GetValidMoves(const int player) const noexcept
{
  const int size = GetSize();
  std::vector< std::pair<int,int> > v;
  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      if (CanDoMove(x,y,player))
      {
        v.push_back( std::make_pair(x,y) );
      }
    }
  }
  return v;
}

int ribi::reversi::Board::GetSize() const noexcept
{
  return m_board.size();
}

#ifndef NDEBUG
void ribi::reversi::Board::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::reversi::Board::Test()");
  {
    Board r(4);
    assert(r.Get(1,1) == Board::player1);
    assert(r.Get(1,2) == Board::player2);
    assert(r.Get(2,1) == Board::player2);
    assert(r.Get(2,2) == Board::player1);
    assert(r.Get(0,0) == Board::empty);
    assert(r.Get(2,0) == Board::empty);
    assert(r.CanDoMove(2,0,Board::player1));
    assert(r.CanDoMove(3,1,Board::player1));
    assert(r.CanDoMove(0,2,Board::player1));
    assert(r.CanDoMove(1,3,Board::player1));
    assert(r.GetValidMoves(Board::player1).size() == 4);
  }
  //operator==
  {
    const Board r(5);
    Board s(5);
    assert(r == s);
    s.Set(0,0,player1);
    assert(r != s);
  }
  //operator<<
  for (int sz=4; sz!=10; ++sz)
  {
    const Board r(sz);
    std::stringstream s;
    s << r;
    Board t;
    s >> t;
    assert(r == t);

  }
  {
    std::stringstream s;
    s << "1112." << '\n'
      << "111.." << '\n'
      << "112.." << '\n'
      << "1.2.." << '\n'
      << "1.2..";
    Board r;
    s >> r;
    assert( r.CanDoMove(4,0,Board::player1));
    assert( r.CanDoMove(3,2,Board::player1));
    assert( r.CanDoMove(3,3,Board::player1));
    assert( r.CanDoMove(3,4,Board::player1));
    assert(!r.CanDoMove(3,1,Board::player1));
  }
  //Play random games
  for (int sz = 4; sz != 10; ++sz)
  {
    Board r(sz);
    int player = Board::player1;
    while (!r.GetValidMoves(player).empty())
    {
      std::vector<std::pair<int,int>> m {
        r.GetValidMoves(player)
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const std::pair<int,int> move = m[0];
      assert(r.CanDoMove(move.first,move.second,player));
      r.DoMove(move.first,move.second,player);
      player = GetOtherPlayer(player);
    }
  }
  TRACE("Finished ribi::reversi::Board::Test()");
}
#endif

bool ribi::reversi::operator==(const ribi::reversi::Board& lhs, const ribi::reversi::Board& rhs)
{
  return lhs.GetBoard() == rhs.GetBoard();
}

bool ribi::reversi::operator!=(const ribi::reversi::Board& lhs, const ribi::reversi::Board& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::reversi::operator<<(std::ostream& os, const ribi::reversi::Board& r)
{
  for(const std::vector<int>& line: r.m_board)
  {
    std::transform(line.begin(),line.end(),
      std::ostream_iterator<std::string>(os,""),
      [](const int square)
      {
        switch (square)
        {
          case Board::empty  : return ".";
          case Board::player1: return "1";
          case Board::player2: return "2";
          default: assert(!"Should not get here");
        }
        assert(!"Should not get here");
        throw std::logic_error("operator<<(std::ostream& os, const Board& r): Unknown square type");
      }
    );
    os << '\n';
  }
  return os;
}

std::istream& ribi::reversi::operator>>(std::istream& is, ribi::reversi::Board& r)
{
  std::vector<std::string> v;
  {
    //Read first line
    {
      std::string s;
      is >> s;
      assert(is);
      v.push_back(s);
    }
    //Read next lines
    assert(!v.empty());
    const int size = static_cast<int>(v[0].size());
    for (int i=1; i!=size; ++i)
    {
      std::string s;
      is >> s;
      assert(is);
      assert(s.size() == v[0].size());
      v.push_back(s);
    }
    assert(size == static_cast<int>(v.size()));
  }
  r = Board(static_cast<int>(v.size()));
  {
    const int size = static_cast<int>(v.size());
    for (int y=0; y!=size; ++y)
    {
      const std::string& line = v[y];
      for (int x=0; x!=size; ++x)
      {
        const char c = line[x];
        switch (c)
        {
          case '1': r.Set(x,y,Board::player1); break;
          case '2': r.Set(x,y,Board::player2); break;
          case '.': r.Set(x,y,Board::empty); break;
          default: assert(!"Should not get here");
        }
      }
    }
  }
  return is;
}
