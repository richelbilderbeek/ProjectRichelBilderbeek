#include "maziakintmaze.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>

#include "maziakdistancesmaze.h"
#include "maziakhelper.h"
#include "testtimer.h"
#include "trace.h"

ribi::maziak::IntMaze::IntMaze()
  : m_dead_ends{}, m_int_grid{}, m_rng_engine(0)
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::maziak::IntMaze::IntMaze(const int sz, const int rng_seed)
  : m_dead_ends{}, m_int_grid{}, m_rng_engine(rng_seed)
{
  #ifndef NDEBUG
  Test();
  #endif
  m_int_grid = CreateIntGrid(sz);
  m_dead_ends = CreateDeadEnds(m_int_grid);
}

ribi::maziak::IntMaze::IntMaze(
  const IntGrid& int_grid,
  const int rng_seed
)
  : m_dead_ends{}, m_int_grid{int_grid}, m_rng_engine(rng_seed)
{
  #ifndef NDEBUG
  Test();
  #endif
  m_dead_ends = CreateDeadEnds(m_int_grid);
}

bool ribi::maziak::IntMaze::CanGet(const int x, const int y) const noexcept
{
  return x >= 0 && x < GetSize()
      && y >= 0 && y < GetSize();
}

std::vector<std::pair<int,int>> ribi::maziak::IntMaze::CreateDeadEnds(
  const std::vector<std::vector<int> >& maze) noexcept
{
  const int size = maze.size();

  std::vector<std::pair<int,int> > dead_ends;

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
      if (nWalls == 3) dead_ends.push_back(std::make_pair(x,y));

    }
  }

  //Shuffle them
  std::shuffle(dead_ends.begin(), dead_ends.end(),m_rng_engine);
  return dead_ends;
}

ribi::maziak::IntMaze::IntGrid
  ribi::maziak::IntMaze::CreateIntGrid(const int sz
) noexcept
{
  //Assume correct size dimensions
  assert( sz > 4 && sz % 4 == 3
    && "Size must be 3 + (n * 4) for n > 0");

  //Start with a wall-only maze
  std::vector<std::vector<int> > maze(sz, std::vector<int>(sz,1));

  //Prepare maze, remove paths
  // XXXXXXX    1111111
  // X X X X    1212121
  // XXXXXXX    1111111
  // X XOX X -> 1210121
  // XXXXXXX    1111111
  // X X X X    1212121
  // XXXXXXX    1111111

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

int ribi::maziak::IntMaze::Get(const int x, const int y) const noexcept
{
  assert(CanGet(x,y));
  return m_int_grid[y][x];
}

ribi::maziak::DistancesMaze ribi::maziak::IntMaze::GetDistancesMaze(
  const int x,
  const int y
  ) const noexcept
{
  DistancesMaze maze(*this,x,y);
  return maze;
}



bool ribi::maziak::IntMaze::IsSquare() const noexcept
{
  assert(!m_int_grid.empty());
  for(std::vector<int> row: m_int_grid)
  {
    if (row.size()!=m_int_grid.size()) return false;
  }
  return true;
}

#ifndef NDEBUG
void ribi::maziak::IntMaze::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
