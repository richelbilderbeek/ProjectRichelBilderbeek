#include "chessrank.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include "trace.h"
#pragma GCC diagnostic pop

ribi::Chess::Rank::Rank(const std::string& y)
  : m_rank(y)
{
  #ifndef NDEBUG
  Test();
  #endif
  if (m_rank.size() != 1)
  {
    throw std::logic_error("A chess ranks consists of a single-chacter std::string with values from 1 to and including 8");
  }
  try
  {
    boost::lexical_cast<int>(y);
  }
  catch (boost::bad_lexical_cast& e)
  {
    throw std::logic_error("A chess ranks consists of a value from 1 to and including 8");
  }
  const int i = boost::lexical_cast<int>(y);

  if (i < 1 || i > 8)
  {
    throw std::logic_error("Chess ranks go from 1 to and including 8");
  }
  assert(boost::lexical_cast<int>(m_rank) >= 1);
  assert(boost::lexical_cast<int>(m_rank) <= 8);
}

ribi::Chess::Rank::Rank(const int y)
  : m_rank(boost::lexical_cast<std::string>(y + 1))
{
  #ifndef NDEBUG
  Test();
  #endif
  if (y < 0 || y > 7)
  {
    throw std::logic_error("Chessboard y coordinats go from 0 to and including 7");
  }
}

std::string ribi::Chess::Rank::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::Chess::Rank::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-01-25: version 1.0: initial version");
  return v;
}

void ribi::Chess::Rank::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef MXE_SUPPORTS_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Chess::Rank");

      FTRACE("Test valid Ranks from std::string");
      {
        const std::vector<std::string> v = {"1","2","3","4","5","6","7","8"};
        std::for_each(v.begin(),v.end(),[](const std::string& s) { Rank tmp(s); } );
      }
      FTRACE("Test valid Ranks from int");
      {
        const std::vector<int> v = {0,1,2,3,4,5,6,7};
        std::for_each(v.begin(),v.end(),[](const int& i) { Rank tmp(i); } );
      }
      FTRACE("Test invalid Ranks from std::string");
      {
        const std::vector<std::string> v = {"0","9","a","h"," ","A","I","aa","1a","a1","11" };
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              Rank tmp(s);
              TRACE(s);
              assert(!"Should not get here");
            }
            catch (std::exception& e)
            {
              //OK!
            }
          }
        );
      }
      FTRACE("Test invalid Ranks from int");
      {
        const std::vector<int> v = {-1,8,10,11,100,111};
        std::for_each(v.begin(),v.end(),
          [](const int& i)
          {
            try
            {
              Rank tmp(i);
              TRACE(i);
              assert(!"Should not get here");
            }
            catch (std::exception& e)
            {
              //OK!
            }
          }
        );
      }
      FTRACE("Test individual ranks intimately");
      {
        Rank r("1");
        assert(r.ToStr() == "1");
        assert(r.ToInt() == 0);
      }
      {
        Rank r("8");
        assert(r.ToStr() == "8");
        assert(r.ToInt() == 7);
      }
      {
        Rank r(0);
        assert(r.ToStr() == "1");
        assert(r.ToInt() == 0);
      }
      {
        Rank r(7);
        assert(r.ToStr() == "8");
        assert(r.ToInt() == 7);
      }
    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  t.detach();
  #endif
}

int ribi::Chess::Rank::ToInt() const
{
  assert(boost::lexical_cast<int>(m_rank) >= 1);
  assert(boost::lexical_cast<int>(m_rank) <= 8);
  return boost::lexical_cast<int>(m_rank) - 1;
}

const std::string& ribi::Chess::Rank::ToStr() const
{
  return m_rank;
}

bool ribi::Chess::operator==(const Chess::Rank& lhs, const Chess::Rank& rhs)
{
  return lhs.ToStr() == rhs.ToStr();
}
