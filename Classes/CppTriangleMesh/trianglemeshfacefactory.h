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

  boost::shared_ptr<Face> Create(
    std::vector<boost::shared_ptr<Point>> points,
    const FaceOrientation any_orientation
  ) const noexcept;

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
