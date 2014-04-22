#include "chesssquarefactory.h"
#include "chesssquare.h"
const boost::shared_ptr<ribi::Chess::Square> ribi::Chess::SquareFactory::Create(
  const File& x,
  const Rank& y)
{
  const boost::shared_ptr<Square> s {
    new Square(x,y)
  };
  assert(s);
  return s;
}

const boost::shared_ptr<ribi::Chess::Square> ribi::Chess::SquareFactory::Create(
  const std::string& text)
{
  const boost::shared_ptr<Square> s {
    new Square(text)
  };
  assert(s);
  return s;
}

const boost::shared_ptr<ribi::Chess::Square> ribi::Chess::SquareFactory::DeepCopy(
  const boost::shared_ptr<const Square> s) noexcept
{
  const boost::shared_ptr<ribi::Chess::Square> t {
    SquareFactory::Create(s->ToStr())
  };
  assert(t);
  assert(*s == *t && "Must be a copy");
  assert(s != t && "Must be a deep copy");
  return t;
}
