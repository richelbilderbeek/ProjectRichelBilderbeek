#ifndef TRIANGLEMESHEDGEFACTORY_H
#define TRIANGLEMESHEDGEFACTORY_H

#ifdef USE_TRIANGLEMESHEDGE

#include <array>
#include <iosfwd>
//#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "trianglemeshcreateverticalfacesstrategy.h"
#include "trianglemeshfaceorientation.h"
#include "trianglemeshfwd.h"
#include "trianglemeshwinding.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

struct EdgeFactory
{
  EdgeFactory();

  boost::shared_ptr<Edge> Create(
    const std::array<boost::shared_ptr<Point>,2>& points
  ) const noexcept;

  ///Create the edges of a testing prism
  /*

  For CreateVerticalFacesStrategy::one_face_per_square, edge indices are:

      +
     /|\
    5 | 4
   /  |  \
  +---3---+    +---3---+---4---+---5---+
  |   |   |    |      /|      /|      /|
  |   A   |    |     / |     / |     / |
  |   |   |    |    /  |    /  |    /  |
  6   +   8    6   7   8   9   A   B   6 <--- here, A and B denote 10,11 respectively
  |  / \  |    |  /    |  /    |  /    |
  | 2   1 |    | /     | /     | /     |
  |/     \|    |/      |/      |/      |
  +---0---+    +---0---+---1---+---2---+

  Folded out, with the bottom (marked #) at the center

          f-5-d
         /|\  |
        A | 4 3
    1  /  |  \|
  f-0-c   9   e
  |  /|\  |  /
  5 B 2#1 | 8
  |/  |##\|/
  d-6-a-0-b
      |\  |
      6 7 8
      |  \|
      d-3-e

  The front plane exists of the edges 0,3,6,8

  Face indices:

          +---+
         /|\ 1|
        / | \ |
       /  |  \|
  +---+ 4 | 5 +
  |7 /|\  |  /
  | / | \ | /
  |/ 6|0 \|/
  +---+---+
      |\ 2|
      | \ |
      |3 \|
      +---+

  For CreateVerticalFacesStrategy::two_faces_per_square, edge indices are:

      +
     /|\
    5 | 4
   /  |  \
  +---3---+    +---3---+---4---+---5---+
  |   |   |    |       |       |       |
  |   8   |    |       |       |       |
  |   |   |    |       |       |       |
  6   +   7    6       7       8       6
  |  / \  |    |       |       |       |
  | 2   1 |    |       |       |       |
  |/     \|    |       |       |       |
  +---0---+    +---0---+---1---+---2---+

  Folded out, with the bottom (marked #) at the center

          +-5-+
         / \  |
        8   4 3
       /     \|
  +-8-+       +
  |   |\     /
  5   2#1   7
  |   |##\ /
  +-6-+-0-+
      |   |
      6   7
      |   |
      +-3-+

  The front plane exists of the edges 0,3,6,7

  Face indices:

          +---+
         / \ 1|
        /   \ |
       /     \|
  +---+   3   +
  |   |\     /
  | 4 | \   /
  |   |0 \ /
  +---+---+
      |   |
      | 2 |
      |   |
      +---+

  */
  std::vector<boost::shared_ptr<Edge>> CreateTestPrism(const CreateVerticalFacesStrategy strategy) const noexcept;


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

  std::vector<boost::shared_ptr<Edge>> CreateTestTriangle(const Winding winding) const noexcept;

  private:
  std::vector<boost::shared_ptr<Edge>> CreateTestPrismOneFacePerVerticalSquare() const noexcept;
  std::vector<boost::shared_ptr<Edge>> CreateTestPrismTwoFacesPerVerticalSquare() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi


#endif

#endif // TRIANGLEMESHEDGEFACTORY_H
