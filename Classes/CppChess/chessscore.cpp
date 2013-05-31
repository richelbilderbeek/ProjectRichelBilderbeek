
#include <iosfwd>
#include <stdexcept>

#ifndef NDEBUG
#include <algorithm>
#include <cassert>
#include <string>

#ifdef SADC_USE_THREADS
#include <thread>
#endif

#include <vector>
#include "trace.h"
#endif

#include "chessscore.h"

namespace Chess {

Score::Score(const std::string& s)
  : m_is_black_winner(s == std::string("0-1")),
    m_is_draw(s == std::string("1/2-1/2")),
    m_is_white_winner(s == std::string("1-0"))
{
  #ifndef NDEBUG
  Test();
  #endif
  if ( !m_is_black_winner
    && !m_is_draw
    && !m_is_white_winner)
  {
    throw std::logic_error("Chess::Score::Score exception: invalid score");
  }
}

const std::string Score::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> Score::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-01-25: version 1.0: initial version");
  return v;
}

#ifndef NDEBUG
void Score::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Chess::Score");
      //Test valid scores being valid
      {
        const std::vector<std::string> v = { "0-1", "1/2-1/2", "1-0" } ;
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              Chess::Score tmp(s);
            }
            catch (std::exception& e)
            {
              TRACE(s);
              assert("Should not get here");
            }
          }
        );
      }
      //Test invalid scores being invalid
      {
        const std::vector<std::string> v = { "1-1", "1/2-1", "1-1/2", "0-0", "a3", "a2 a3", "0-0-0", "Qd4", "Qd4 e5" } ;
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              Chess::Score tmp(s);
              TRACE(s)
              assert("Should not get here");
            }
            catch (std::exception& e)
            {
              //Okay: invalid Score is determined being invalid
            }
          }
        );
      }
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}
#endif

const std::string Score::ToStr() const
{
  if (m_is_black_winner) return "0-1";
  if (m_is_draw) return "1/2-1/2";
  if (m_is_white_winner) return "1-0";
  assert(!"Should not get here");
}

std::ostream& operator<<(std::ostream& os, const Score& s)
{
  os << s.ToStr();
  return os;
}

bool operator==(const Score& lhs, const Score& rhs)
{
  return
       lhs.IsBlackWinner() == rhs.IsBlackWinner()
    && lhs.IsDraw()        == rhs.IsDraw()
    && lhs.IsWhiteWinner() == rhs.IsWhiteWinner();
}

bool operator!=(const Score& lhs, const Score& rhs)
{
  return !(lhs==rhs);
}

} //~namespace Chess

