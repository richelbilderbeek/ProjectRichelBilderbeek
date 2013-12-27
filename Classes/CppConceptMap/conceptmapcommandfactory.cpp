#include "conceptmapcommandfactory.h"

#include <cassert>

#include "conceptmapcommand.h"

const std::vector<boost::shared_ptr<ribi::cmap::Command> > ribi::cmap::CommandFactory::CreateTestCommands() noexcept
{
  std::vector<boost::shared_ptr<ribi::cmap::Command> > v;
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandDeleteConceptMap
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandStartConceptMap
    };
    assert(p);
    v.push_back(p);
  }
  return v;
}
