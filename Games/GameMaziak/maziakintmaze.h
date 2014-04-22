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
  IntMaze(const int sz) : IntMaze(CreateMaze(sz)) {}
  IntMaze(const std::vector<std::vector<int> >& maze);

  bool CanGet(const int x, const int y) const noexcept;

  int Get(const int x, const int y) const noexcept;

  const std::vector<std::vector<int>> GetMaze() const noexcept { return m_maze; }

  int GetSize() const noexcept { return static_cast<int>(m_maze.size()); }

  ///Already shuffled, m_dead_ends[0] is the suggested initial coordinat for the player
  const std::vector<std::pair<int,int> > GetDeadEnds() const noexcept { return m_dead_ends; }

  ///Find the distances to (x,y) in walking squared
  const boost::shared_ptr<DistancesMaze> GetDistancesMaze(
    const int x,
    const int y
    ) const noexcept;

  ///Adapted from http://www.richelbilderbeek.nl/CppIsSquare.htm
  bool IsSquare() const noexcept;

  private:

  const std::vector<std::pair<int,int> > m_dead_ends;
  const std::vector<std::vector<int>> m_maze;

  ///From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
  static const std::vector<std::pair<int,int> > CreateDeadEnds(
    const std::vector<std::vector<int> >& maze) noexcept;

  //Creates a maze
  // 0 : path
  // 1 : wall
  ///From http://www.richelbilderbeek.nl/CppCreateMaze.htm
  static const std::vector<std::vector<int> > CreateMaze(const int sz) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKINTMAZE_H
