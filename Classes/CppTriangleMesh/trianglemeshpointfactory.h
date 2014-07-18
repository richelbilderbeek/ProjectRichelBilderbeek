#ifndef RIBI_TRIANGLEMESHPOINTFACTORY_H
#define RIBI_TRIANGLEMESHPOINTFACTORY_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>
#include "trianglemeshfwd.h"
#include "trianglemeshwinding.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

class PointFactory
{
  friend class CellsCreator;
  friend class Face;
  friend class FaceFactory;
  friend class Helper;
  friend class Template;
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  PointFactory();

  ///This way is used in mesh creation: every 3D point shares the same
  ///ConstCoordinat2D
  ///Create a Point with an undetermined Z coordinat
  boost::shared_ptr<Point> Create(
    const boost::shared_ptr<const Coordinat2D> coordinat
  ) const noexcept;

  ///This way is used in mesh creation: every 3D point shares the same
  ///ConstCoordinat2D
  boost::shared_ptr<Point> Create(
    const boost::shared_ptr<const Coordinat2D> coordinat,
    const boost::units::quantity<boost::units::si::length> z
  ) const noexcept;

  ///Create the points of a testing cube
  /*
      |
    +-+-+
    | | |
   -+-O-+-  View from above, for Z = -1 and Z = 1
    | | |
    +-+-+
      |

  [0]: -1,-1,-1
  [1]: -1,-1, 1
  [2]: -1, 1,-1
  [3]: -1, 1, 1
  [4]:  1,-1,-1
  [5]:  1,-1, 1
  [6]:  1, 1,-1
  [7]:  1, 1, 1

  */
  std::vector<boost::shared_ptr<Point>> CreateTestCube() const noexcept;

  //Create points that should fail to construct a Face from
  std::vector<boost::shared_ptr<Point>> CreateTestInvalid() const noexcept;

  ///Create the points of a testing prism
  /*
      F
     /|\
    D---E
    | | |
    | C |
    |/ \|
    A---B

  */
  std::vector<boost::shared_ptr<Point>> CreateTestPrism() const noexcept;

  ///Creates a square for a certain winding (when viewed from above)
  /*

    Clockwise:

      Y
  2.5 |
    2 + 1-2
  1.5 | | |
    1 + 0-3 where Z = 1.0 for all points
  0.5 |
    0 +-+-+-X
      0 1 2

    Counter-clockwise:

     Y
 2.5 |
   2 + 3-2
 1.5 | | |
   1 + 0-1  where Z = 1.0 for all points
 0.5 |
   0 +-+-+-X
     0 1 2

    Indeterminate:

      Y
  2.3 |
    2 +  2--1
  1.7 |   \/
  1.3 |   /\
    1 +  0--3 where Z = 1.0 for all points
  0.7 |
  0.3 |
    0 +--+--+-X
      0  1  2

  */
  std::vector<boost::shared_ptr<Point>> CreateTestSquare(const Winding winding) const noexcept;

  ///Creates a triangle for a certain winding (when viewed from above)
  /*

    Clockwise:

      Y
  2.5 |
    2 + 1-2
  1.5 | |/
    1 + 0   where Z = 1.0 for all points
  0.5 |
    0 +-+-+-X
      0 1 2

    Counter-clockwise:

      Y
  2.5 |
    2 + 2-1
  1.5 | |/
    1 + 0   where Z = 1.0 for all points
  0.5 |
    0 +-+-+-X
      0 1 2

  */
  std::vector<boost::shared_ptr<Point>> CreateTestTriangle(const Winding winding) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHPOINTFACTORY_H
