#ifndef MAZIAKHELPER_H
#define MAZIAKHELPER_H

#include <cassert>
#include <vector>

#include "maziakmazesquare.h"

namespace ribi {
namespace maziak {

template <class Source, class Target>
    const std::vector<std::vector<Target> > ConvertMatrix(
        const std::vector<std::vector<Source> >& v)
{
  const int maxy = static_cast<int>(v.size());
  assert(maxy>0);
  const int maxx = static_cast<int>(v[0].size());
  std::vector<std::vector<Target> > t(maxy,std::vector<Target>(maxx));
  for (int y=0; y!=maxy; ++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      t[y][x] = static_cast<Target>(v[y][x]);
    }
  }
  return t;
}

const std::vector<std::pair<int,int> > GetShuffledDeadEnds(
    const std::vector<std::vector<int> >& intMaze);

const std::vector<std::pair<int,int> > GetShuffledNonDeadEnds(
    const std::vector<std::vector<int> >& intMaze);

bool CanMoveTo(
    const std::vector<std::vector<MazeSquare> >& maze,
    const int x, const int y,
    const bool hasSword,
    const bool showSolution);

//From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
std::vector<std::pair<int,int> > GetDeadEnds(const std::vector<std::vector<int> >& maze);

//From http://www.richelbilderbeek.nl/GetDistancesPath.htm
std::vector<std::vector<int> > GetDistancesPath(
  const std::vector<std::vector<int> >& distances,
  const int playerX,
  const int playerY);

//From http://www.richelbilderbeek.nl/CppGetMazeDistances.htm
std::vector<std::vector<int> > GetMazeDistances(
    const std::vector<std::vector<int> >& maze,
    const int x,
    const int y);

const std::vector<std::pair<int,int> > GetShuffledDeadEnds(
    const std::vector<std::vector<int> >& intMaze);

bool IsSquare(const std::vector<std::vector<MazeSquare> >& v);
bool IsSquare(const std::vector<std::vector<int> >& v);

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKHELPER_H
