#ifndef MAZIAKMAZESQUARE_H
#define MAZIAKMAZESQUARE_H

namespace ribi {
namespace maziak {

enum class MazeSquare
{
  msEmpty,
  msWall,
  msEnemy1,
  msEnemy2,
  msPrisoner1,
  msPrisoner2,
  msSword,
  msExit,
  msStart //Initial starting position
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKMAZESQUARE_H
