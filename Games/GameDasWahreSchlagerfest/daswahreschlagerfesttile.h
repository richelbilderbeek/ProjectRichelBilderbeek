#ifndef DASWAHRESCHLAGERFESTTILE_H
#define DASWAHRESCHLAGERFESTTILE_H

namespace ribi {
namespace dws {

enum class Tile
{
  empty,
  beer,
  bratwurst,
  richel
};

char ToChar(const Tile& tile);

} //~namespace dws
} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTTILE_H
