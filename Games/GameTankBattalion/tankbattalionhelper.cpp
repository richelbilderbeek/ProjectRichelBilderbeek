#include "tankbattalionhelper.h"

#include <cassert>
#include <stdexcept>

#include "tankbattalionkeys.h"
#include "trace.h"

ribi::taba::Helper::Helper()
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::taba::Direction ribi::taba::Helper::KeyToDirection(const Key k)
{
  assert(Keys().IsMovement(k)
    && "Only movement keys can be converted to a direction");
  switch (k)
  {
    case Key::up: return Direction::up;
    case Key::right: return Direction::right;
    case Key::down: return Direction::down;
    case Key::left: return Direction::left;
    default:
      assert(!"Should not use this key for a direction");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::taba::Helper::KeyToDirection: cannot convert Key to Direction");
}

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
  assert(!"ribi::taba::Helper::ToPlayerSpriteType: should not get here");
  throw std::logic_error("ribi::taba::Helper::ToPlayerSpriteType: unknown direction");
}

#ifndef NDEBUG
void ribi::taba::Helper::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::taba::Helper::Test");
  TRACE("Finished ribi::taba::Helper::Test successfully");
}
#endif
