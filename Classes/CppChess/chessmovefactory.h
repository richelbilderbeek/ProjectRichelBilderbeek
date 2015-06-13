#ifndef RIBI_CHESSMOVEFACTORY_H
#define RIBI_CHESSMOVEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

struct MoveFactory
{
  MoveFactory();

  const boost::shared_ptr<Move> Create(const std::string& s) const;

  const boost::shared_ptr<Move> Create(
    const boost::shared_ptr<const Chess::Square> from,
    const boost::shared_ptr<const Chess::Square> to
  ) const;

  const boost::shared_ptr<Move> DeepCopy(const Move& move) const;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace Chess
} //~namespace ribi

#endif // RIBI_CHESSMOVEFACTORY_H
