#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#include "chessbitboard.h"
#include "chesssquare.h"
#include "chesssquarefactory.h"
#include "trace.h"

ribi::Chess::BitBoard::BitBoard()
  : m_v(8,std::vector<bool>(8,false))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_v.size() == 8);
  assert(m_v[7].size() == 8);
}

std::string ribi::Chess::BitBoard::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::Chess::BitBoard::GetVersionHistory()
{
  return {
    "2012-01-25: version 1.0: initial version"
  };
}

void ribi::Chess::BitBoard::Set(const boost::shared_ptr<const Square> s, const bool value)
{
  const int x = s->GetFile().ToInt();
  const int y = s->GetRank().ToInt();
  #ifndef NDEBUG
  m_v.at(y).at(x) = value;
  #else
  m_v[y][x] = value;
  #endif
}

bool ribi::Chess::BitBoard::Get(const boost::shared_ptr<const Square> s) const
{
  const int x = s->GetFile().ToInt();
  const int y = s->GetRank().ToInt();
  #ifndef NDEBUG
  return m_v.at(y).at(x);
  #else
  return m_v[y][x];
  #endif
}

void ribi::Chess::BitBoard::Test() noexcept
{
  //Testing Chess::BitBoard exactly once
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  #ifdef MXE_SUPPORTS_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Chess::BitBoard");
      BitBoard b;

      assert(!b.Get(SquareFactory().Create("g8")));
      b.Set(SquareFactory().Create("g8"),true);
      assert( b.Get(SquareFactory().Create(("g8"))));
      b.Set(SquareFactory().Create("g8"),false);
      assert(!b.Get(SquareFactory().Create(("g8"))));
    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  t.detach();
  #endif
}

std::ostream& ribi::Chess::operator<<(std::ostream& os, const BitBoard& b)
{
  std::for_each(b.m_v.begin(),b.m_v.end(),
    [&os](const std::vector<bool>& v)
    {
      std::copy(v.begin(),v.end(),std::ostream_iterator<bool>(os,""));
      os << '\n';
    }
  );
  return os;
}

