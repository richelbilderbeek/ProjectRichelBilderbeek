#ifndef TRIANGLEMESHPOINTFACTORY_H
#define TRIANGLEMESHPOINTFACTORY_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
//#include "constcoordinat2d.h"
#include "trianglemeshfwd.h"
#include "trianglemeshwinding.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

struct PointFactory
{
  PointFactory();

  #ifndef NDEBUG
  /*
  ///Create a Point with an undetermined Z coordinat
  const boost::shared_ptr<Point> CreateFromXy(
    const double x, const double y
  ) const noexcept;
  */
  #endif

  ///This way is used in mesh creation: every 3D point shares the same
  ///ConstCoordinat2D
  ///Create a Point with an undetermined Z coordinat
  const boost::shared_ptr<Point> Create(
    const boost::shared_ptr<const ribi::ConstCoordinat2D> coordinat
  ) const noexcept;

  const boost::shared_ptr<Point> CreateFrom3D(
    const boost::shared_ptr<const ribi::Coordinat3D> coordinat
  ) const noexcept;

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
  const std::vector<boost::shared_ptr<Point>> CreateTestPrism() const noexcept;

  ///Creates a triangle for a certain winding (when viewed from above)
  /*

    Clockwise:

    0 1 2
  0 +-+-+-X
    |
  1 + 0   where Z = 1.0 for all points
    | |\
  2 + 2-1
    |
    Y

    Counter-clockwise:

    0 1 2
  0 +-+-+-X
    |
  1 + 0   where Z = 1.0 for all points
    | |\
  2 + 1-2
    |
    Y

  */
  const std::vector<boost::shared_ptr<Point>> CreateTestTriangle(const Winding winding) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHPOINTFACTORY_H
