#include "maziakdistancesmaze.h"

#include <cassert>

#include "maziakintmaze.h"
#include "testtimer.h"
#include "trace.h"

ribi::maziak::DistancesMaze::DistancesMaze()
  : m_distances{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::maziak::DistancesMaze::DistancesMaze(
  const IntMaze& maze,
  const int x,
  const int y
  )
  : m_distances(CalculateDistances(maze,x,y))
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<std::vector<int>> ribi::maziak::DistancesMaze::CalculateDistances(
  const IntMaze& maze,
  const int x, const int y) noexcept
{
  //Assume maze is square
  assert(maze.IsSquare());
  assert(maze.Get(x,y) == 0); //Assume starting point is no wall

  const int size = maze.GetSize();
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

        if (maze.Get(x,y-1) == 0                //No wall
          && distances[y-1][x] == maxDistance) //Not already in solution
        {
          distances[y-1][x] = distance;
          newFound.push_back(std::make_pair(x,y-1));
        }
        if (maze.Get(x,y+1) == 0                //No wall
          && distances[y+1][x] == maxDistance) //Not already in solution
        {
          distances[y+1][x] = distance;
          newFound.push_back(std::make_pair(x,y+1));
        }

        if (maze.Get(x+1,y) == 0                //No wall
          && distances[y][x+1] == maxDistance) //Not already in solution
        {
          distances[y][x+1] = distance;
          newFound.push_back(std::make_pair(x+1,y));
        }

        if (maze.Get(x-1,y) == 0                //No wall
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

bool ribi::maziak::DistancesMaze::CanGet(const int x, const int y) const noexcept
{
  return x >= 0 && x < GetSize()
      && y >= 0 && y < GetSize();
}

int ribi::maziak::DistancesMaze::Get(const int x, const int y) const noexcept
{
  assert(CanGet(x,y));
  return m_distances[y][x];
}

#ifndef NDEBUG
void ribi::maziak::DistancesMaze::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
