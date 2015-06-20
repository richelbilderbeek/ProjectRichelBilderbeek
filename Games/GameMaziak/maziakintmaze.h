#ifndef MAZIAKINTMAZE_H
#define MAZIAKINTMAZE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

#include "maziakfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

///A maze using integers
/// 0 : path
/// 1 : wall
struct IntMaze
{
  using IntGrid = std::vector<std::vector<int>>;

  explicit IntMaze();
  explicit IntMaze(const int sz, const int rng_seed = 42);
  explicit IntMaze(const IntGrid& int_grid, const int rng_seed = 42);

  bool CanGet(const int x, const int y) const noexcept;

  int Get(const int x, const int y) const noexcept;

  const IntGrid& GetMaze() const noexcept { return m_int_grid; }

  int GetSize() const noexcept { return static_cast<int>(m_int_grid.size()); }

  ///Already shuffled, m_dead_ends[0] is the suggested initial coordinat for the player
  const std::vector<std::pair<int,int> > GetDeadEnds() const noexcept { return m_dead_ends; }

  ///Find the distances to (x,y) in walking squared
  DistancesMaze GetDistancesMaze(
    const int x,
    const int y
  ) const noexcept;

  ///Adapted from http://www.richelbilderbeek.nl/CppIsSquare.htm
  bool IsSquare() const noexcept;

  private:

  std::vector<std::pair<int,int> > m_dead_ends;
  IntGrid m_int_grid;
  std::mt19937 m_rng_engine;

  ///From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
  std::vector<std::pair<int,int> > CreateDeadEnds(
    const IntGrid& maze) noexcept;

  //Creates a maze
  // 0 : path
  // 1 : wall
  ///From http://www.richelbilderbeek.nl/CppCreateMaze.htm
  IntGrid CreateIntGrid(const int sz) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKINTMAZE_H
