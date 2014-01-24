#ifndef MAZIAKHELPER_H
#define MAZIAKHELPER_H

#include <cassert>
#include <vector>

#include "maziakmazesquare.h"

namespace ribi {
namespace maziak {

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


//From http://www.richelbilderbeek.nl/CppGetMazeDistances.htm
std::vector<std::vector<int> > GetMazeDistances(
    const std::vector<std::vector<int> >& maze,
    const int x,
    const int y);

//const std::vector<std::pair<int,int> > GetShuffledDeadEnds(
//    const std::vector<std::vector<int> >& intMaze);


} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKHELPER_H
