#include "daswahreschlagerfesttile.h"

#include <cassert>
#include <stdexcept>

char ribi::dws::ToChar(const Tile& tile)
{
  switch (tile)
  {
    case Tile::beer     : return 'V';
    case Tile::bratwurst: return 'U';
    case Tile::empty    : return '.';
    case Tile::richel   : return 'R';
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::dws::ToChar: Unknown Tile");
}
