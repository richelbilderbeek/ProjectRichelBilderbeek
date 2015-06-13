#include "chessmovefactory.h"

#include <cassert>

#include "chessmove.h"
#include "testtimer.h"

ribi::Chess::MoveFactory::MoveFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

const boost::shared_ptr<ribi::Chess::Move>
  ribi::Chess::MoveFactory::Create(const std::string& s) const
{
  const boost::shared_ptr<ribi::Chess::Move> p {
    new Move(s)
  };
  #ifdef TODO_ISSUE_176
  assert(p);
  #endif
  return p;
}

const boost::shared_ptr<ribi::Chess::Move> ribi::Chess::MoveFactory::Create(
  const boost::shared_ptr<const Chess::Square> from,
  const boost::shared_ptr<const Chess::Square> to) const
{
  const std::string s = from->ToStr() + " " + to->ToStr();
  return Create(s);
}

const boost::shared_ptr<ribi::Chess::Move>
  ribi::Chess::MoveFactory::DeepCopy(
    const Move& move
  ) const
{
  const boost::shared_ptr<ribi::Chess::Move> p {
    Create(move.ToStr())
  };
  assert(p);
  return p;
}

#ifndef NDEBUG
void ribi::Chess::MoveFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    Chess::Move("a2-a3");
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
