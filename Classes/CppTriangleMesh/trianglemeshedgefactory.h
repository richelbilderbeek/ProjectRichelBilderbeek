#ifndef TRIANGLEMESHEDGEFACTORY_H
#define TRIANGLEMESHEDGEFACTORY_H

#include <array>
#include <iosfwd>
//#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "trianglemeshfaceorientation.h"
#include "trianglemeshfwd.h"
#include "trianglemeshwinding.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

struct EdgeFactory
{
  EdgeFactory();

  const boost::shared_ptr<Edge> Create(
    const std::array<boost::shared_ptr<Point>,2>& points
  ) const noexcept;

  ///Create the edges of a testing prism
  ///The indices are { top, bottom, a,b,c }
  /*

  Point indices:

      f
     /|\
    d---e
    | | |
    | c |
    |/ \|
    a---b


  Edge indices will become:

      f
     /|\
    6 | 5
   /  |  \
  d---4---e    d---4---e---5---f---6---d
  |   |   |    |      /|      /|      /|
  |   |   |    |     / |     / |     / |
  |   |   |    |    /  |    /  |    /  |
  |   c   |    7   8   9   A   B   C   7 <--- here, A,B,C denote 10,11,12
  |  / \  |    |  /    |  /    |  /    |
  | 3   2 |    | /     | /     | /     |
  |/     \|    |/      |/      |/      |
  a---1---b    a---1---b---2---c---3---a


  Folded out, with the bottom (marked #) at the center

          f
         /|\
        B | 5
       /  |  \
  f-B-c   A   e
  |  /|\  |  /
  6 C 3#2 | 9
  |/  |##\|/
  d-7-a-1-b
      |\  |
      7 8 9
      |  \|
      d-4-e

  */
  const std::vector<boost::shared_ptr<Edge>> CreateTestPrism() const noexcept;


  ///Creates a triangle with the requested winding (when viewed from above)
  /*

  Points are always the same:

    0 1 2
  0 +-+-+-X
    |
  1 + 0   where Z = 1.0 for all points
    | |\
  2 + 2-1
    |
    Y

  clockwise        : 0->1, 1->2, 2->0
  counter_clockwise: 0->2, 2->1, 1->0
  indeterminate    : 0->1, 2->1, 2->0

  */

  const std::vector<boost::shared_ptr<Edge>> CreateTestTriangle(const Winding winding) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi


#endif // TRIANGLEMESHEDGEFACTORY_H
