#ifndef TRIANGLEMESHFACEFACTORY_H
#define TRIANGLEMESHFACEFACTORY_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>
#include "trianglemeshfaceorientation.h"
#include "trianglemeshfwd.h"
#include "trianglemeshwinding.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

struct FaceFactory
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  FaceFactory();

  boost::shared_ptr<Face> Create(
    const std::vector<boost::shared_ptr<Edge>>& edges,
    const FaceOrientation any_orientation
  ) const noexcept;

  boost::shared_ptr<Face> Create(
    std::vector<boost::shared_ptr<Point>> points,
    const FaceOrientation any_orientation
  ) const noexcept;


  ///Create the faces of a testing prism from edges
  /*
  Edge indices are:

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

  The front plane exists of the edges 0,3,6,8

  All windings are clockwise, when seen from the inside of the prism

  */
  std::vector<boost::shared_ptr<Face>> CreateTestPrism() const noexcept;

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
  std::vector<boost::shared_ptr<Face>> CreateTestPrismFromPoints() const noexcept;

  boost::shared_ptr<Face> CreateTestSquare(const Winding winding) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHFACEFACTORY_H
