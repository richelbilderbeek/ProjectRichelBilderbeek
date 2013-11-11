#include "chessmovefactory.h"

#include <cassert>

#include "chessmove.h"

const boost::shared_ptr<ribi::Chess::Move> ribi::Chess::MoveFactory::Create(const std::string& s)
{
  const boost::shared_ptr<ribi::Chess::Move> p {
    new Move(s)
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::Chess::Move> ribi::Chess::MoveFactory::Create(
  const boost::shared_ptr<const Chess::Square> from,
  const boost::shared_ptr<const Chess::Square> to)
{
  const std::string s = from->ToStr() + " " + to->ToStr();
  return Create(s);
}

const boost::shared_ptr<ribi::Chess::Move> ribi::Chess::MoveFactory::DeepCopy(const Move& move)
{
  const boost::shared_ptr<ribi::Chess::Move> p {
    Create(move.ToStr())
  };
  assert(p);
  return p;
}
