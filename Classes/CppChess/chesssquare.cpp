#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include "chesssquare.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::Chess::Square::Square(const Chess::File& x, const Chess::Rank& y)
  : m_file(x), m_rank(y)
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::Chess::Square::Square(const std::string &s)
  : m_file(Chess::File(boost::lexical_cast<std::string>(s.at(0)))),
    m_rank(Chess::Rank(boost::lexical_cast<std::string>(s.at(1))))
{
  #ifndef NDEBUG
  Test();
  #endif
  if (s.empty()) throw std::logic_error("An empty string cannot be converted to a chess square");
  if (s.size() != 2)
  {
    throw std::logic_error("A string to be converted to a chess square must consist of exactly two characters");
  }
}

//ribi::Chess::Square::Square(const char * const s)
//  : m_x(Chess::File(s[0]),
//    m_y(Chess::Rank(boost::lexical_cast<int>(s[1])))
//{
//  assert(s);
//  assert(std::strlen(s) == 2);
//}

ribi::Chess::Color ribi::Chess::Square::GetColor() const
{
  return ((this->GetFile().ToInt() + this->GetRank().ToInt()) % 2 == 1 ? Color::white : Color::black);
}

std::string ribi::Chess::Square::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::Chess::Square::GetVersionHistory()
{
  return {
    "2012-01-25: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::Chess::Square::Test() noexcept
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
      Chess::File::Test();
      Chess::Rank::Test();

      FTRACE("Test Chess::Square operators and constructor");
      {
        Chess::Square s("a1");
        Chess::Square t("a1");
        Chess::Square u(t);
        Chess::Square v("a2");
        assert(s == t);
        assert(t == u);
        assert(s != v);
        assert(u != v);
      }

      {
        FTRACE("Test a1");
        Chess::Square s("a1");
        assert(s.GetFile().ToStr() == "a");
        assert(s.GetRank().ToStr() == "1");
        assert(s.GetFile().ToInt() == 0);
        assert(s.GetRank().ToInt() == 0);
        assert(s.GetColor() == Color::black);
      }
      {
        FTRACE("Test b1");
        Chess::Square s("b1");
        assert(s.GetFile().ToStr() == "b");
        assert(s.GetRank().ToStr() == "1");
        assert(s.GetFile().ToInt() == 1);
        assert(s.GetRank().ToInt() == 0);
        assert(s.GetColor() == Color::white);
      }
      {
        FTRACE("Test a2");
        Chess::Square s("a2");
        assert(s.GetFile().ToStr() == "a");
        assert(s.GetRank() == Chess::Rank("2"));
        assert(s.GetFile().ToInt() == 0);
        assert(s.GetRank().ToInt() == 1);
        assert(s.GetColor() == Color::white);
      }
      {
        FTRACE("Test d1");
        Chess::Square s("d1");
        assert(s.GetColor() == Color::white);
      }
      {
        FTRACE("Test d8");
        Chess::Square s("d8");
        assert(s.GetColor() == Color::black);
      }
      {
        FTRACE("Test g8");
        Chess::Square s("g8");
        assert(s.GetFile().ToStr() == "g");
        assert(s.GetRank() == Rank("8"));
        assert(s.GetFile().ToInt() == 6);
        assert(s.GetRank().ToInt() == 7);
      }
      {
        FTRACE("Test known-to-be-valid squares");
        const std::vector<std::string> v =
        {
          "a1", "a8", "h1", "h8", "d4"
        };
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              Chess::Square x(s);
            }
            catch (std::exception& e)
            {
              TRACE(s);
              TRACE(e.what());
              assert("Should not get here");
            }
          }
        );
      }

      {
        FTRACE("Test known-to-be-invalid squares");
        const std::vector<std::string> v =
        {
          "A1", "a9", "H8", "h9", "i1", "a", "A", "1", "9", "a10", "h10", "aa1", "a1a", "11", "aa"
        };
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            bool ok = false;
            try
            {
              Chess::Square x(s);
            }
            catch (std::exception& e)
            {
              //Ok!
              ok = true;
            }
            if (!ok)
            {
              TRACE(s);
              assert("Should not get here");
            }
          }
        );
      }
      FTRACE("Tested Chess::Square successfully");
    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  t.detach();
  #endif
}
#endif

std::string ribi::Chess::Square::ToStr() const noexcept
{
  std::string s
    = boost::lexical_cast<std::string>(GetFile().ToStr())
    + boost::lexical_cast<std::string>(GetRank().ToStr());
  return s;
}

std::ostream& ribi::Chess::operator<<(std::ostream& os, const Square& s) noexcept
{
  os << s.ToStr();
  return os;
}

bool ribi::Chess::operator==(const Square& lhs, const Square& rhs) noexcept
{
  return lhs.GetFile() == rhs.GetFile()
    && lhs.GetRank() == rhs.GetRank();
}

bool ribi::Chess::operator!=(const Square& lhs, const Square& rhs) noexcept
{
  return !(lhs == rhs);
}
