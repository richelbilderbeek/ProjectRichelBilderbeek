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
  |   c   |    7   8   9   A   B   C   D <--- here, A,B,C,D denote 10,11,12,13
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

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi


#endif // TRIANGLEMESHEDGEFACTORY_H
