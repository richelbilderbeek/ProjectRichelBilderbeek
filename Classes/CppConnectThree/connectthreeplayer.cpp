#include "connectthreeplayer.h"

#include <cassert>
#include <stdexcept>

ribi::con3::Player ribi::con3::GetNextPlayer(const ribi::con3::Player player) noexcept
{
  switch (player)
  {
    case Player::player1: return Player::player2;
    case Player::player2: return Player::player3;
    case Player::player3: return Player::player1;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown value of Player");
}
