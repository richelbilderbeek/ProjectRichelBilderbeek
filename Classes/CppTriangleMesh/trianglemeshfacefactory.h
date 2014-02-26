#ifndef TRIANGLEMESHFACEFACTORY_H
#define TRIANGLEMESHFACEFACTORY_H

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
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

struct FaceFactory
{
  FaceFactory();

  const boost::shared_ptr<Face> Create(
    const std::vector<boost::shared_ptr<Edge>>& edges,
    const FaceOrientation any_orientation
  ) const noexcept;

  const boost::shared_ptr<Face> Create(
    const std::vector<boost::shared_ptr<Point>>& points,
    const FaceOrientation any_orientation
  ) const noexcept;

  ///Create the faces of a testing prism from edges
  /*
  Edge indices are:

      +
     /|\
    6 | 5
   /  |  \
  +---4---+    +---4---+---5---+---6---+
  |   |   |    |      /|      /|      /|
  |   B   |    |     / |     / |     / |
  |   |   |    |    /  |    /  |    /  |
  7   +   9    7   8   9   A   B   C   7 <--- here, A,B,C denote 10,11,12
  |  / \  |    |  /    |  /    |  /    |
  | 3   2 |    | /     | /     | /     |
  |/     \|    |/      |/      |/      |
  +---1---+    +---1---+---2---+---3---+

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

  The front plane exists of the edges 1,4,7,9

  */
  const std::vector<boost::shared_ptr<Face>> CreateTestPrism() const noexcept;

  ///Create the faces of a testing prism from points
  ///The indices are { top, bottom, a,b,c }
  /*
           top
            v

            F
           /|\
          D---E
          | | |
    c ->  | C | <- b
          |/ \|
          A---B

            ^
           bottom

  Folder out, with the bottom (marked #) at the center

          +
         /|\
        / | \
       /  |  \
  +---C c | d +
  |f /|\  |  /
  | / |#\ | /
  |/ e|##\|/
  +---A---B
      |\ a|
      | \ |
      |b \|
      +---+

  The front planes are 'a' and 'b', where 'a' has two nodes at the base

  */
  const std::vector<boost::shared_ptr<Face>> CreateTestPrismFromPoints() const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHFACEFACTORY_H
