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
#include "trianglemeshcreateverticalfacesstrategy.h"
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

  #ifdef USE_TRIANGLEMESHEDGE
  boost::shared_ptr<Face> Create(
    const std::vector<boost::shared_ptr<Edge>>& edges,
    const FaceOrientation any_orientation
  ) const noexcept;
  #endif

  boost::shared_ptr<Face> Create(
    std::vector<boost::shared_ptr<Point>> points,
    const FaceOrientation any_orientation
  ) const noexcept;


  #ifdef USE_TRIANGLEMESHEDGE
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
  #endif
  ///Create the faces of a testing prism from points
  ///The indices are { top, bottom, a,b,c }
  /*

            5
           /|\
          3---4
          | | |
          | 2 |
          |/ \|
          0---1

  Folder out, with the bottom (marked #) at the center

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


  The front planes are 'a' and 'b', where 'a' has two nodes at the base

  */
  std::vector<boost::shared_ptr<Face>> CreateTestPrism(const CreateVerticalFacesStrategy strategy) const noexcept;

  boost::shared_ptr<Face> CreateTestSquare(const Winding winding) const noexcept;

  private:

  std::vector<boost::shared_ptr<Face>> CreateTestPrismOneFacePerVerticalFace() const noexcept;
  std::vector<boost::shared_ptr<Face>> CreateTestPrismTwoFacesPerVerticalFace() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHFACEFACTORY_H
