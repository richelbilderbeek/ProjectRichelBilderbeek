#ifndef CHESSMOVEFACTORY_H
#define CHESSMOVEFACTORY_H

#include <boost/shared_ptr.hpp>

#include "chessfwd.h"

namespace ribi {
namespace Chess {

struct MoveFactory
{

  static boost::shared_ptr<Move> Create(const std::string& s);

  static boost::shared_ptr<Move> DeepCopy(const Move& move);
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSMOVEFACTORY_H
