#include "connectthreemovefactory.h"

#include <cassert>
#include "connectthreemove.h"

#include "trace.h"

const boost::shared_ptr<ribi::con3::Move> ribi::con3::MoveFactory::Create(
  const int x, const int y, const Player player) const noexcept
{
  const boost::shared_ptr<Move> move {
    new Move(x,y,player)
  };
  assert(move);
  return move;
}

#ifndef NDEBUG
void ribi::con3::MoveFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::con3::MoveFactory::Test");
  TRACE("Finished ribi::con3::MoveFactory::Test successfully");
}
#endif
