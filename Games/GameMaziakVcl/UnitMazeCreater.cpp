/*
  Maziak, a simple maze game
  Copyright (C) 2007  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#pragma hdrstop

#include <algorithm>
#include <cassert>

#include "UnitMazeCreater.h"
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GetMazeDistances
const std::vector<std::vector<int> > GetMazeDistances(
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GetMazeDistances
std::vector<std::vector<int> > GetMazeDistancesSlow(
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
    bool newDistanceFound = true;

    while(newDistanceFound == true)
    {
      ++distance;
      newDistanceFound = false;
      for (int y=0; y!=size; ++y)
      {
        for (int x=0; x!=size; ++x)
        {
          //Check if this spot can be assigned a distance value
          if (maze[y][x] != 0) continue; //Continue if here is a wall
          if (distances[y][x] != maxDistance) continue; //Continue if already in solution
          if ( x!=0      && distances[y][x-1] == distance - 1 )
          { distances[y][x] = distance; newDistanceFound = true; continue; }
          if ( x!=size-1 && distances[y][x+1] == distance - 1 )
          { distances[y][x] = distance; newDistanceFound = true; continue; }
          if ( y!=0      && distances[y-1][x] == distance - 1 )
          { distances[y][x] = distance; newDistanceFound = true; continue; }
          if ( y!=size-1 && distances[y+1][x] == distance - 1 )
          { distances[y][x] = distance; newDistanceFound = true; continue; }
        }
      }

    }
  }
  return distances;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GetDistancesPath.htm
const std::vector<std::vector<int> > GetDistancesPath(
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppSolveMaze.htm
const std::vector<std::vector<int> > SolveMaze(
  const std::vector<std::vector<int> >& maze,
  const int x1,
  const int y1,
  const int x2,
  const int y2)
{
  //Assume maze is square
  assert(maze[0].size() == maze.size());
  assert(maze[y1][x1] == 0); //Assume starting point is no wall
  assert(maze[y2][x2] == 0); //Assume end point is no wall

  const std::vector<std::vector<int> > distances(GetMazeDistances(maze,x2,y2));
  return GetDistancesPath(distances,x1,y1);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCountDeadEnds.htm
const int CountDeadEnds(const std::vector<std::vector<int> >& maze)
{
  const int size = maze.size();

  int nDeadEnds = 0;

  for (int y=1; y!=size-1; ++y)
  {
    for (int x=1; x!=size-1; ++x)
    {
      if (maze[y][x] != 0) continue; //Continue if here is a wall
      const int nWalls
        = (maze[y+1][x  ] == 1 ? 1 : 0)
        + (maze[y-1][x  ] == 1 ? 1 : 0)
        + (maze[y  ][x+1] == 1 ? 1 : 0)
        + (maze[y  ][x-1] == 1 ? 1 : 0);
      if (nWalls == 3) ++nDeadEnds;

    }
  }
  return nDeadEnds;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
const std::vector<std::pair<int,int> > GetDeadEnds(const std::vector<std::vector<int> >& maze)
{
  const int size = maze.size();

  std::vector<std::pair<int,int> > deadEnds;

  for (int y=1; y!=size-1; ++y)
  {
    for (int x=1; x!=size-1; ++x)
    {
      if (maze[y][x] != 0) continue; //Continue if here is a wall
      const int nWalls
        = (maze[y+1][x  ] == 1 ? 1 : 0)
        + (maze[y-1][x  ] == 1 ? 1 : 0)
        + (maze[y  ][x+1] == 1 ? 1 : 0)
        + (maze[y  ][x-1] == 1 ? 1 : 0);
      if (nWalls == 3) deadEnds.push_back(std::make_pair(x,y));

    }
  }
  return deadEnds;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetNonDeadEnds.htm
const std::vector<std::pair<int,int> > GetNonDeadEnds(const std::vector<std::vector<int> >& maze)
{
  const int size = maze.size();

  std::vector<std::pair<int,int> > nonDeadEnds;

  for (int y=1; y!=size-1; ++y)
  {
    assert( y < static_cast<int>(maze.size()) && "y must be in range");
    assert( maze.size() == maze[y].size() && "Maze must be square");
    for (int x=1; x!=size-1; ++x)
    {
      assert( x < static_cast<int>(maze[y].size()) && "x must be in range");
      if (maze[y][x] != 0) continue; //Continue if here is a wall
      assert(maze[y][x] == 0);
      const int nWalls
        = (maze[y+1][x  ] == 1 ? 1 : 0)
        + (maze[y-1][x  ] == 1 ? 1 : 0)
        + (maze[y  ][x+1] == 1 ? 1 : 0)
        + (maze[y  ][x-1] == 1 ? 1 : 0);
      if (nWalls < 3) nonDeadEnds.push_back(std::make_pair(x,y));

    }
  }
  return nonDeadEnds;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCreateSloppyMaze.htm
const std::vector<std::vector<int> > CreateSloppyMazeOld(const int size, const double fractionPerfect)
{
  //Size must be odd
  assert( size % 2 == 1);
  assert( fractionPerfect >= 0.0 && fractionPerfect <= 1.0);

  std::vector<std::vector<int> > maze(size, std::vector<int>(size,0));

  //Draw outer walls
  for (int i=0; i!=size; ++i)
  {
    maze[0]     [i     ] = 1;
    maze[size-1][i     ] = 1;
    maze[i]     [0     ] = 1;
    maze[i]     [size-1] = 1;
  }

  //Draw pillars
  for (int y=2; y!=size-1; y+=2)
  {
    for (int x=2; x!=size-1; x+=2)
    {
      maze[y][x] = 1;
    }
  }

  //Check around pillars
  const int nWallsToAdd
    = static_cast<int>(fractionPerfect
      * static_cast<double>(((size / 2) - 1) * ((size / 2) - 1)));
  assert(nWallsToAdd <=(((size / 2) - 1) * ((size / 2) - 1)));

  for (int i=0; i < nWallsToAdd; ) //'<' as there might be 2 walls added
  {

    for (int y=2; y!=size-1; y+=2)
    {
      for (int x=2; x!=size-1; x+=2)
      {
        const int nWalls
          = (maze[y-1][x] == 0 ? 0 : 1)
          + (maze[y+1][x] == 0 ? 0 : 1)
          + (maze[y][x+1] == 0 ? 0 : 1)
          + (maze[y][x-1] == 0 ? 0 : 1);
        if ( nWalls == 0)
        {
          switch(std::rand() % 4)
          {
            case 0: maze[y-1][x] = 1; break;
            case 1: maze[y+1][x] = 1; break;
            case 2: maze[y][x+1] = 1; break;
            case 3: maze[y][x-1] = 1; break;
          }
          ++i;
        }
        else if (nWalls == 1)
        {
          switch(std::rand() % 6)
          {
            case 0: std::swap(maze[y-1][x], maze[y+1][x]); break;
            case 1: std::swap(maze[y-1][x], maze[y][x+1]); break;
            case 2: std::swap(maze[y-1][x], maze[y][x-1]); break;
            case 3: std::swap(maze[y+1][x], maze[y][x+1]); break;
            case 4: std::swap(maze[y+1][x], maze[y][x-1]); break;
            case 5: std::swap(maze[y][x+1], maze[y][x-1]); break;
          }
        }
      }
    }
  }
  return maze;
}
//---------------------------------------------------------------------------
//Creates a maze
// 0 : path
// 1 : wall
//From http://www.richelbilderbeek.nl/CppCreateMaze.htm
const std::vector<std::vector<int> > CreateMaze(const int sz)
{
  //Size must be odd
  assert( sz % 2 == 1);

  //Start with a wall-only maze
  std::vector<std::vector<int> > maze(sz, std::vector<int>(sz,1));

  //Prepare maze, remove paths
  // XXXXXXX
  // X X X X
  // XXXXXXX
  // X XOX X
  // XXXXXXX
  // X X X X
  // XXXXXXX

  //Draw open spaces
  for (int y=1; y!=sz-2; y+=2)
  {
    for (int x=1; x!=sz-2; x+=2)
    {
      maze[y][x] = 2; //2: unexplored
    }
  }
  const int mid = sz/2;

  maze[mid][mid] = 0;

  std::vector<std::pair<int,int> > v;
  v.push_back(std::make_pair(mid,mid));
  while (!v.empty())
  {
    //Set a random explorer square at the back
    std::swap(v.back(),v[ std::rand() % static_cast<int>(v.size())]);
    //Check possible adjacent squares
    const int x = v.back().first;
    const int y = v.back().second;
    std::vector<std::pair<int,int> > next;
    if (x >  0 + 2 && maze[y][x-2] == 2) next.push_back(std::make_pair(x-2,y));
    if (y >  0 + 2 && maze[y-2][x] == 2) next.push_back(std::make_pair(x,y-2));
    if (x < sz - 2 && maze[y][x+2] == 2) next.push_back(std::make_pair(x+2,y));
    if (y < sz - 2 && maze[y+2][x] == 2) next.push_back(std::make_pair(x,y+2));
    //Dead end?
    if (next.empty())
    {
      v.pop_back();
      continue;
    }
    //Select a random next adjacent square
    const int nextIndex = (std::rand() >> 4) % static_cast<int>(next.size());
    const int nextX = next[nextIndex].first;
    const int nextY = next[nextIndex].second;
    //Clear next square
    maze[nextY][nextX] = 0;
    //Clear path towards next square
    maze[(y + nextY)/2][(x + nextX)/2] = 0;
    //Add next square to stack
    v.push_back(std::make_pair(nextX,nextY));
  }
  return maze;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCreateMaze.htm
const std::vector<std::vector<int> > CreateMazeOld(const int size)
{
  //Size must be odd
  assert( size % 2 == 1);

  std::vector<std::vector<int> > maze(size, std::vector<int>(size,0));

  //Draw outer walls
  for (int i=0; i!=size; ++i)
  {
    maze[0]     [i     ] = 1;
    maze[size-1][i     ] = 1;
    maze[i]     [0     ] = 1;
    maze[i]     [size-1] = 1;
  }

  //Draw pillars
  for (int y=2; y!=size-1; y+=2)
  {
    for (int x=2; x!=size-1; x+=2)
    {
      maze[y][x] = 1;
    }
  }

  //Check around pillars
  const int nWallsToAdd = ((size / 2) - 1) * ((size / 2) - 1);
  for (int i=0; i != nWallsToAdd; )
  {

    for (int y=2; y!=size-1; y+=2)
    {
      for (int x=2; x!=size-1; x+=2)
      {
        const int nWalls
          = (maze[y-1][x] == 0 ? 0 : 1)
          + (maze[y+1][x] == 0 ? 0 : 1)
          + (maze[y][x+1] == 0 ? 0 : 1)
          + (maze[y][x-1] == 0 ? 0 : 1);
        if ( nWalls == 0)
        {
          switch(std::rand() % 4)
          {
            case 0: maze[y-1][x] = 1; break;
            case 1: maze[y+1][x] = 1; break;
            case 2: maze[y][x+1] = 1; break;
            case 3: maze[y][x-1] = 1; break;
          }
          ++i;
        }
        else if (nWalls == 1)
        {
          switch(std::rand() % 6)
          {
            case 0: std::swap(maze[y-1][x], maze[y+1][x]); break;
            case 1: std::swap(maze[y-1][x], maze[y][x+1]); break;
            case 2: std::swap(maze[y-1][x], maze[y][x-1]); break;
            case 3: std::swap(maze[y+1][x], maze[y][x+1]); break;
            case 4: std::swap(maze[y+1][x], maze[y][x-1]); break;
            case 5: std::swap(maze[y][x+1], maze[y][x-1]); break;
          }
        }
      }
    }
  }
  return maze;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)


