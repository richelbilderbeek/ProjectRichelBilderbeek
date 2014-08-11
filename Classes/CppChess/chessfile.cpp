#include "chessfile.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::Chess::File::File(const std::string& s)
  : m_s(s)
{
  #ifndef NDEBUG
  Test();
  #endif
  if (m_s.empty()) throw std::logic_error("Chess files cannot be empty");
  if (m_s.size() != 1) throw std::logic_error("Chess files consist of exactly one character");
  const char c = m_s[0];
  if (c < 'a' || c > 'h') throw std::logic_error("Chess files go from a to and including h");
  assert(c >= 'a');
  assert(c <= 'h');
}

ribi::Chess::File::File(const int x)
  : m_s(IntToCharToStr(x))
{
  #ifndef NDEBUG
  Test();
  #endif
  if (x < 0 || x > 7) throw std::logic_error("X coordinats go from 0 to and including 7");

  #ifndef NDEBUG
  const char c = m_s[0];
  assert(m_s.size() == 1);
  assert(c >= 'a');
  assert(c <= 'h');
  #endif
}

std::string ribi::Chess::File::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::Chess::File::GetVersionHistory()
{
  return {
    "2012-01-25: version 1.0: initial version"
  };
}

std::string ribi::Chess::File::IntToCharToStr(const int x)
{
  char c = 'a' + x;
  return boost::lexical_cast<std::string>(c);
}

void ribi::Chess::File::Test() noexcept
{
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
    {
      if (verbose) { TRACE("Test Chess::File"); }

      if (verbose) { TRACE("Test valid Files from std::string"); }
      {
        const std::vector<std::string> v = {"a","b","c","d","e","f","g","h"};
        std::for_each(v.begin(),v.end(),[](const std::string& s) { Chess::File tmp(s); } );
      }
      if (verbose) { TRACE("Test valid Files from int"); }
      {
        const std::vector<int> v = {0,1,2,3,4,5,6,7};
        std::for_each(v.begin(),v.end(),[](const int& i) { File tmp(i); } );
      }
      if (verbose) { TRACE("Test invalid Files from std::string"); }
      {
        const std::vector<std::string> v = {"A","i"," ","H","I","1","7","aa","1a","a1" };
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              File tmp(s);
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
      if (verbose) { TRACE("Test invalid Files from int"); }
      {
        const std::vector<int> v = {-1,8,10,11,100,111};
        std::for_each(v.begin(),v.end(),
          [](const int& i)
          {
            try
            {
              File tmp(i);
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
      if (verbose) { TRACE("Test individual files intimately"); }
      {
        File f("a");
        assert(f.ToStr() == "a");
        assert(f.ToInt() == 0);
      }
      {
        File f("h");
        assert(f.ToStr() == "h");
        assert(f.ToInt() == 7);
      }
      {
        File f(0);
        assert(f.ToStr() == "a");
        assert(f.ToInt() == 0);
      }
      {
        File f(7);
        assert(f.ToStr() == "h");
        assert(f.ToInt() == 7);
      }
    }
}

int ribi::Chess::File::ToInt() const
{
  const char c = m_s[0];
  assert(c >= 'a');
  assert(c <= 'h');

  const int value = c - 'a';
  assert(value >= 0);
  assert(value < 8);
  return value;
}

bool ribi::Chess::operator==(const File& lhs, const File& rhs)
{
  return lhs.ToStr() == rhs.ToStr();
}
