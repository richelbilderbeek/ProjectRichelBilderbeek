#include "conceptmapcommandfactory.h"

#include <cassert>

#include "conceptmapcommandcreatenewconceptmap.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommanddeleteconceptmap.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandlosefocus.h"
#include "conceptmapcommanddeletefocusnode.h"
#include "conceptmapcommandsetfocusrandom.h"
#include "conceptmapcommandsetfocuswithcoordinat.h"

const std::vector<boost::shared_ptr<ribi::cmap::Command> > ribi::cmap::CommandFactory::CreateTestCommands() noexcept
{
  std::vector<boost::shared_ptr<ribi::cmap::Command> > v;
  /*
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandCreateNewConceptMap
    };
    assert(p);
    v.push_back(p);
  }
  */
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandCreateNewNode
    };
    assert(p);
    v.push_back(p);
  }
  /*
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandDeleteConceptMap
    };
    assert(p);
    v.push_back(p);
  }
  */
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandLoseFocus
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandSetFocusRandom
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandSetFocusWithCoordinat(0,0)
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<ribi::cmap::Command> p {
      new CommandDeleteFocusNode
    };
    assert(p);
    v.push_back(p);
  }
  return v;
}
