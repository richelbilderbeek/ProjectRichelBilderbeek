#ifndef CHESSMOVEFACTORY_H
#define CHESSMOVEFACTORY_H

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
  static const boost::shared_ptr<Move> Create(const std::string& s);

  static const boost::shared_ptr<Move> Create(
    const boost::shared_ptr<const Chess::Square> from,
    const boost::shared_ptr<const Chess::Square> to);

  static const boost::shared_ptr<Move> DeepCopy(const Move& move);
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSMOVEFACTORY_H
