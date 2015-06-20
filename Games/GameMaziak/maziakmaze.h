#ifndef MAZIAKMAZE_H
#define MAZIAKMAZE_H

#include <vector>

#include "maziakfwd.h"
#include "maziakmazesquare.h"
#include "maziakintmaze.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

struct Maze
{
  Maze(const int size,const int rng_seed = 42);

  ///Animate the enemies and prisoners in sight
  ///(all others are just standing still)
  void AnimateEnemiesAndPrisoners(
    const int x,
    const int y,
    const int view_width,
    const int view_height
    ) noexcept;

  bool CanGet(const int x, const int y) const noexcept;
  bool CanSet(const int x, const int y, const MazeSquare s) const noexcept;

  ///Can a player move to coordinat (x,y) ?
  bool CanMoveTo(
    const int x, const int y,
    const bool hasSword,
    const bool showSolution) const noexcept;

  const std::pair<int,int> FindExit() const noexcept;
  const std::pair<int,int> FindStart() const noexcept;

  MazeSquare Get(const int x, const int y) const noexcept;

  const IntMaze& GetIntMaze() const noexcept { return m_int_maze; }

  int GetSize() const noexcept { return static_cast<int>(m_maze.size()); }

  ///Adapted from http://www.richelbilderbeek.nl/CppIsSquare.htm
  bool IsSquare() const noexcept;

  void Set(const int x, const int y, const MazeSquare s) noexcept;

  private:

  const IntMaze m_int_maze;
  std::vector<std::vector<MazeSquare>> m_maze;
  std::mt19937 m_rng_engine;

  static IntMaze CreateIntMaze(const int size) noexcept;

  std::vector<std::vector<MazeSquare>> CreateMaze(
    const IntMaze& int_maze
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKMAZE_H
