#include "maziakhelper.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>

#include "maziakmazesquare.h"

//Adapted from http://www.richelbilderbeek.nl/CppIsSquare.htm
bool ribi::maziak::IsSquare(const std::vector<std::vector<ribi::maziak::MazeSquare> >& v)
{
  assert(!v.empty());
  for(std::vector<MazeSquare> row: v)
  {
    if (row.size()!=v.size()) return false;
  }
  return true;
}

//Adapted from http://www.richelbilderbeek.nl/CppIsSquare.htm
bool ribi::maziak::IsSquare(const std::vector<std::vector<int> >& v)
{
  assert(!v.empty());
  for(std::vector<int> row: v)
  {
    if (row.size()!=v.size()) return false;
  }
  return true;
}



std::vector<std::vector<int> > ribi::maziak::GetMazeDistances(
  const std::vector<std::vector<int> >& maze,
  const int x,
  const int y)
{
  //Assume maze is square
  assert(maze[0].size() == maze.size());
  assert(maze[y][x] == 0); //Assume starting point is no wall

  const int size = maze.size();
  const int area = size * size;
  const int maxDistance = area;
  std::vector<std::vector<int> > distances(size, std::vector<int>(size,maxDistance));
  {
    //Calculate the distances
    int distance = 0;
    distances[y][x] = 0; //Set final point
    std::vector< std::pair<int,int> > found;
    found.push_back(std::make_pair(x,y));

    while(found.empty() == false)
    {
      ++distance;
      std::vector< std::pair<int,int> > newFound;

      const std::vector< std::pair<int,int> >::iterator j = found.end();
      for (std::vector< std::pair<int,int> >::iterator i = found.begin(); i!=j; ++i)
      {
        const int x = (*i).first;
        const int y = (*i).second;

        if ( maze[y-1][x] == 0                 //No wall
          && distances[y-1][x] == maxDistance) //Not already in solution
        {
          distances[y-1][x] = distance;
          newFound.push_back(std::make_pair(x,y-1));
        }
        if ( maze[y+1][x] == 0                 //No wall
          && distances[y+1][x] == maxDistance) //Not already in solution
        {
          distances[y+1][x] = distance;
          newFound.push_back(std::make_pair(x,y+1));
        }

        if ( maze[y][x+1] == 0                 //No wall
          && distances[y][x+1] == maxDistance) //Not already in solution
        {
          distances[y][x+1] = distance;
          newFound.push_back(std::make_pair(x+1,y));
        }

        if ( maze[y][x-1] == 0                 //No wall
          && distances[y][x-1] == maxDistance) //Not already in solution
        {
          distances[y][x-1] = distance;
          newFound.push_back(std::make_pair(x-1,y));
        }

      }
      found = newFound;
    }
  }
  return distances;
}


#include <vector>



//From http://www.richelbilderbeek.nl/GetDistancesPath.htm
std::vector<std::vector<int> > ribi::maziak::GetDistancesPath(
  const std::vector<std::vector<int> >& distances,
  const int playerX,
  const int playerY)
{
  const int size = distances.size();

  std::vector<std::vector<int> > solution(size, std::vector<int>(size,0));
  {
    int x = playerX;
    int y = playerY;
    int distance = distances[y][x] - 1;
    while (distance >= 0)
    {
      //We must be where we are now
      solution[y][x] = 1;
      if ( x!=0      && distances[y][x-1] == distance ) { --x; --distance; continue; }
      if ( x!=size-1 && distances[y][x+1] == distance ) { ++x; --distance; continue; }
      if ( y!=0      && distances[y-1][x] == distance ) { --y; --distance; continue; }
      if ( y!=size-1 && distances[y+1][x] == distance ) { ++y; --distance; continue; }
    }
  }
  return solution;
}

bool ribi::maziak::CanMoveTo(
  const std::vector<std::vector<ribi::maziak::MazeSquare> >& maze,
  const int x, const int y,
  const bool hasSword,
  const bool showSolution)
{
  //Bump into edge
  if (x < 0) return false;
  if (y < 0) return false;
  const int maxy = static_cast<int>(maze.size());
  if (y >= maxy) return false;
  if (x >= static_cast<int>(maze[y].size())) return false;
  const MazeSquare s = maze[y][x];
  //Bump into wall
  if (s == MazeSquare::msWall) return false;
  //Bump into sword
  if (s == MazeSquare::msSword && hasSword) return false;
  //Bump into prisoner
  if (showSolution
    && (s == MazeSquare::msPrisoner1
     || s == MazeSquare::msPrisoner2) ) return false;
  //Bump into empty/enemy/exit, so player can move there
  return true;
}
