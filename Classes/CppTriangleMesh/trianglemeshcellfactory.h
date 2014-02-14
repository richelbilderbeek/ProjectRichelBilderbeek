#ifndef TRIANGLEMESHCELLFACTORY_H
#define TRIANGLEMESHCELLFACTORY_H

#include <iosfwd>
//#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///The only class to use Cell its constructor
struct CellFactory
{
  const boost::shared_ptr<Cell> Create(
    const std::vector<boost::shared_ptr<Face>>& faces
  );

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHCELLFACTORY_H
