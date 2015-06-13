#include "chesssquarefactory.h"

#include <cassert>

#include "chesssquare.h"
#include "trace.h"
#include "testtimer.h"

ribi::Chess::SquareFactory::SquareFactory() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

const boost::shared_ptr<ribi::Chess::Square> ribi::Chess::SquareFactory::Create(
  const File& x,
  const Rank& y
) const noexcept
{
  const boost::shared_ptr<Square> s {
    new Square(x,y)
  };
  assert(s);
  return s;
}

const boost::shared_ptr<ribi::Chess::Square> ribi::Chess::SquareFactory::Create(
  const std::string& text) const noexcept
{
  try
  {
    const boost::shared_ptr<Square> s {
      new Square(text)
    };
    assert(s);
    return s;
  }
  catch (std::exception&)
  {
    boost::shared_ptr<Square> s;
    assert(!s);
    return s;
  }
}

const boost::shared_ptr<ribi::Chess::Square> ribi::Chess::SquareFactory::CreateFromMove(
  const std::string& text) const noexcept
{
  if (text.size() < 2)
  {
    boost::shared_ptr<Square> s;
    assert(!s);
    return s;
  }
  try
  {
    const boost::shared_ptr<Square> s {
      new Square(text.substr(0,2))
    };
    assert(s);
    return s;
  }
  catch (std::exception&)
  {
    //Ok
  }
  if (text.size() < 3)
  {
    boost::shared_ptr<Square> s;
    assert(!s);
    return s;
  }
  try
  {
    const boost::shared_ptr<Square> s {
      new Square(text.substr(1,2))
    };
    assert(s);
    return s;
  }
  catch (std::exception&)
  {
    boost::shared_ptr<Square> s;
    assert(!s);
    return s;
  }
}

boost::shared_ptr<ribi::Chess::Square> ribi::Chess::SquareFactory::DeepCopy(
  const boost::shared_ptr<const Square> s) const noexcept
{
  const boost::shared_ptr<ribi::Chess::Square> t {
    SquareFactory::Create(s->ToStr())
  };
  assert(t);
  assert(*s == *t && "Must be a copy");
  assert(s != t && "Must be a deep copy");
  return t;
}

#ifndef NDEBUG
void ribi::Chess::SquareFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    Square("a1");
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //const bool verbose{false};
  const SquareFactory s;
  assert(s.Create("a3"));
  assert(!s.Create("Na3"));
  assert(!s.Create("O-O"));
  assert(s.CreateFromMove("Na3"));
  assert(s.CreateFromMove("a3"));
  assert(!s.CreateFromMove("O-O"));
}
#endif
