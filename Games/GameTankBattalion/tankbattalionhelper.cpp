#include "tankbattalionhelper.h"

#include <cassert>

ribi::taba::SpriteType ribi::taba::Helper::ToPlayerSpriteType(const Direction d) const noexcept
{
  switch (d)
  {
    case Direction::up: return SpriteType::player_up;
    case Direction::right: return SpriteType::player_right;
    case Direction::down: return SpriteType::player_down;
    case Direction::left: return SpriteType::player_left;
    default: assert(!"ribi::taba::Helper::ToPlayerSpriteType: should not get here");
  }
}
