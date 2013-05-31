
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#ifdef SADC_USE_THREADS
#include <thread>
#endif

#include "chessbitboard.h"
#include "chesssquare.h"
#include "chesssquarefactory.h"
#include "trace.h"

namespace Chess {

BitBoard::BitBoard()
  : m_v(8,std::vector<bool>(8,false))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_v.size() == 8);
  assert(m_v[7].size() == 8);
}

const std::string BitBoard::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> BitBoard::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-01-25: version 1.0: initial version");
  return v;
}

void BitBoard::Set(const Square& s, const bool value)
{
  const int x = s.GetFile().ToInt();
  const int y = s.GetRank().ToInt();
  #ifndef NDEBUG
  m_v.at(y).at(x) = value;
  #else
  m_v[y][x] = value;
  #endif
}

bool BitBoard::Get(const Square& s) const
{
  const int x = s.GetFile().ToInt();
  const int y = s.GetRank().ToInt();
  #ifndef NDEBUG
  return m_v.at(y).at(x);
  #else
  return m_v[y][x];
  #endif
}

void BitBoard::Test()
{
  //Testing Chess::BitBoard exactly once
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Chess::BitBoard");
      BitBoard b;

      assert(!b.Get(*SquareFactory::Create("g8")));
      b.Set(*SquareFactory::Create("g8"),true);
      assert( b.Get(*SquareFactory::Create(("g8"))));
      b.Set(*SquareFactory::Create("g8"),false);
      assert(!b.Get(*SquareFactory::Create(("g8"))));
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

std::ostream& operator<<(std::ostream& os, const BitBoard& b)
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

} //~ namespace Chess


