#ifndef DASWAHRESCHLAGERFESTCURSOR_H
#define DASWAHRESCHLAGERFESTCURSOR_H

#include "daswahreschlagerfesttile.h"

namespace ribi {
namespace dws {

struct Cursor
{
  Cursor(const int any_x, const int any_y, const Tile any_tile)
    : x(any_x), y(any_y), tile(any_tile) {}
  int x;
  int y;
  Tile tile;
};

} //~namespace dws
} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTCURSOR_H
