
#include <cassert>
#include <stdexcept>

#include "chessplayer.h"

std::string ribi::Chess::PlayerToStr(const Player player) noexcept
{
  switch (player)
  {
    case Player::black: return "black";
    case Player::white: return "white";
  }
  assert(!"Unknown Player in PlayerToStr");
  throw std::logic_error("Unknown Player in PlayerToStr");
}
