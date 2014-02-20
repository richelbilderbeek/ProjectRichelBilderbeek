#ifndef CONNECTTHREEMOVEFACTORY_H
#define CONNECTTHREEMOVEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "connectthreefwd.h"
#include "connectthreeplayer.h"

namespace ribi {
namespace con3 {

struct MoveFactory
{
  const boost::shared_ptr<Move> Create(const int x, const int y, const Player player) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace con3
} //~namespace ribi

#endif // CONNECTTHREEMOVEFACTORY_H
