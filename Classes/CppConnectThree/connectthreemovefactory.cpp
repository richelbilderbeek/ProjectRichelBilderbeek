#include "connectthreemovefactory.h"

#include <cassert>
#include "connectthreemove.h"

const boost::shared_ptr<ribi::con3::Move> ribi::con3::MoveFactory::Create(
  const int x, const int y, const Player player) const noexcept
{
  const boost::shared_ptr<Move> move {
    new Move(x,y,player)
  };
  assert(move);
  return move;
}
