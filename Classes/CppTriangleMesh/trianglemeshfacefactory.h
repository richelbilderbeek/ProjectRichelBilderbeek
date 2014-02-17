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
    const std::vector<boost::shared_ptr<Point>>& points,
    const FaceOrientation any_orientation
  ) const noexcept;

  ///Create the faces of a testing prism
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
  const std::vector<boost::shared_ptr<Face>> CreateTestPrism() const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHFACEFACTORY_H
