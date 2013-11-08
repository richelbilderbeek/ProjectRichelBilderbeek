
#include <cassert>
#include <exception>
#include <iostream>

#include "chesscolor.h"
#include "chessplayer.h"
#include "trace.h"

const std::string ribi::Chess::ColorToStr(const Color c)
{
  switch (c)
  {
    case Color::black        : return "black";
    case Color::indeterminate: return "indeterminate";
    case Color::white        : return "white";
    case Color::red          : return "red";
    case Color::green        : return "green";
    case Color::blue         : return "blue";
  }
  assert(!"Should not get here");
  throw std::logic_error("Chess::ColorToStr: unimplemented Color");
}

ribi::Chess::Player ribi::Chess::ColorToPlayer(const Color c)
{
  switch (c)
  {
    case Color::white: return Player::white;
    case Color::black: return Player::black;
    default: break;
  }
  #ifndef NDEBUG
  TRACE(c);
  #endif
  assert(!"Cannot convert color to player");
  throw std::logic_error("Cannot convert color to player");
}

const std::string ribi::Chess::ColorVersion::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::Chess::ColorVersion::GetVersionHistory()
{
  return {
    "2012-01-25: version 1.0: initial version",
    "2012-02-07: version 1.1: added colors red, green and blue for selection"
  };
}

std::ostream& ribi::Chess::operator<<(std::ostream& os, const Color c)
{
  os << ColorToStr(c);
  return os;
}

bool ribi::Chess::operator==(const Color color, const Player player)
{
  switch (player)
  {
    case Player::black: return color == Color::black;
    case Player::white: return color == Color::white;
  }
  return false;
}

bool ribi::Chess::operator==(const Player player, const Color color)
{
  return color == player;
}

bool ribi::Chess::operator!=(const Color color, const Player player)
{
  return !(color == player);
}

bool ribi::Chess::operator!=(const Player player, const Color color)
{
  return !(color == player);
}
