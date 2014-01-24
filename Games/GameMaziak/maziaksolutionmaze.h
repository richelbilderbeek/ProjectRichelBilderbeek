#ifndef MAZIAKSOLUTIONMAZE_H
#define MAZIAKSOLUTIONMAZE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

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
  SolutionMaze(
    const boost::shared_ptr<const DistancesMaze> maze,
    const int x,
    const int y
  );

  int Get(const int x, const int y) const noexcept;
  int GetSize() const noexcept;
  bool IsSquare() const noexcept;

  private:

  const boost::shared_ptr<const IntMaze> m_maze;

  static const boost::shared_ptr<const IntMaze> CreateSolution(
    const boost::shared_ptr<const DistancesMaze> maze,
    const int x,
    const int y
  ) noexcept;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSOLUTIONMAZE_H
