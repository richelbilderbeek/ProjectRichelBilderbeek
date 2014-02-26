#ifndef TRIANGLEMESHPOINTFACTORY_H
#define TRIANGLEMESHPOINTFACTORY_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "constcoordinat2d.h"
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

struct PointFactory
{
  PointFactory();

  const boost::shared_ptr<Point> Create(
    const boost::shared_ptr<const ribi::ConstCoordinat2D> coordinat
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


  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHPOINTFACTORY_H
