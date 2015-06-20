#ifndef MAZIAKDISTANCESMAZE_H
#define MAZIAKDISTANCESMAZE_H

#include <vector>

#include "maziakfwd.h"
#include "maziakmazesquare.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

///DistancesMaze displays the distances from a goal
/*

 456789
 3
 21012 8
   1 3 7
 4323456

*/

struct DistancesMaze
{
  DistancesMaze();

  DistancesMaze(
    const IntMaze& maze,
    const int goal_x,
    const int goal_y
  );

  bool CanGet(const int x, const int y) const noexcept;
  int Get(const int x, const int y) const noexcept;
  int GetSize() const noexcept { return static_cast<int>(m_distances.size()); }

  private:
  std::vector<std::vector<int>> m_distances;

  static std::vector<std::vector<int>> CalculateDistances(
    const IntMaze& maze,
    const int x,
    const int y
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKDISTANCESMAZE_H
