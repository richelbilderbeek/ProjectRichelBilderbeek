#ifndef MAZIAKSOLUTIONMAZE_H
#define MAZIAKSOLUTIONMAZE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

#include "maziakintmaze.h"
#include "maziakfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace maziak {

///SolutionMaze displays the solution from a goal (as obtained
///from a DistanceMaze) and a current position
/*

* : solution
. : other corridors

 ***...
 *
 ***.. .
 . . . .
 . .....

*/

struct SolutionMaze
{
  SolutionMaze();
  SolutionMaze(
    const DistancesMaze& maze,
    const int x,
    const int y
  );

  int Get(const int x, const int y) const noexcept;
  int GetSize() const noexcept;
  bool IsSquare() const noexcept;

  private:
  IntMaze m_maze;

  static IntMaze CreateSolution(
    const DistancesMaze& maze,
    const int x,
    const int y
  ) noexcept;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSOLUTIONMAZE_H
