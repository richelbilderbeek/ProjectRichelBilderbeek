#ifndef CONCEPTMAPCOMMANDFACTORY_H
#define CONCEPTMAPCOMMANDFACTORY_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///CommandFactory creates Commands
struct CommandFactory
{
  static const std::vector<boost::shared_ptr<Command> > CreateTestCommands() noexcept;
};

} //~namespace cmap
} //~namespace ribi


#endif // CONCEPTMAPCOMMANDFACTORY_H
