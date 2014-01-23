#include "maziakintmaze.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>

#include "maziakhelper.h"

ribi::maziak::IntMaze::IntMaze(const std::vector<std::vector<int>>& maze)
  : m_dead_ends{CreateDeadEnds(maze)},
    m_maze{maze}
{

}

//From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
std::vector<std::pair<int,int> > ribi::maziak::CreateDeadEnds(const std::vector<std::vector<int> >& maze)
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

const std::vector<std::vector<int> > ribi::maziak::IntMaze::CreateMaze(const int sz) noexcept
{
  //Assume correct size dimensions
  assert( sz > 4 && sz % 4 == 3
    && "Size must be 3 + (n * 4) for n > 0");

  //Start with a wall-only maze
  std::vector<std::vector<int> > maze(sz, std::vector<int>(sz,1));

  //Prepare maze, remove paths
  // XXXXXXX 1111111
  // X X X X 1212121
  // XXXXXXX 1111111
  // X XOX X -> 1210121
  // XXXXXXX 1111111
  // X X X X 1212121
  // XXXXXXX 1111111

  //Draw open spaces
  for (int y=1; y<sz; y+=2)
  {
    for (int x=1; x<sz; x+=2)
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
    if (x > 0 + 2 && maze[y][x-2] == 2) next.push_back(std::make_pair(x-2,y));
    if (y > 0 + 2 && maze[y-2][x] == 2) next.push_back(std::make_pair(x,y-2));
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


const std::vector<std::pair<int,int> > ribi::maziak::GetShuffledDeadEnds(
    const std::vector<std::vector<int> >& intMaze)
{
  std::vector<std::pair<int,int> > deadEnds = GetDeadEnds();
  std::random_shuffle(deadEnds.begin(), deadEnds.end());
  return deadEnds;
}

