#include "conceptmapcommandfactory.h"

#include <cassert>

#include "conceptmapcommandaddfocusrandom.h"
#include "conceptmapcommandcreatenewconceptmap.h"
#include "conceptmapcommandcreatenewedge.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommanddeleteconceptmap.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandlosefocus.h"
#include "conceptmapcommanddeletefocusnode.h"
#include "conceptmapcommandsetfocusrandom.h"
#include "conceptmapcommandsetfocuswithcoordinat.h"

std::vector<boost::shared_ptr<ribi::cmap::Command> > ribi::cmap::CommandFactory::CreateTestCommands() noexcept
{
  std::vector<boost::shared_ptr<Command> > v;
  {
    const boost::shared_ptr<Command> p {
      new CommandAddFocusRandom
    };
    assert(p);
    v.push_back(p);
  }
  /*
  {
    const boost::shared_ptr<Command> p {
      new CommandCreateNewConceptMap
    };
    assert(p);
    v.push_back(p);
  }
  */
  {
    const boost::shared_ptr<Command> p {
      new CommandCreateNewEdge
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Command> p {
      new CommandCreateNewNode
    };
    assert(p);
    v.push_back(p);
  }
  /*
  {
    const boost::shared_ptr<Command> p {
      new CommandDeleteConceptMap
    };
    assert(p);
    v.push_back(p);
  }
  */
  {
    const boost::shared_ptr<Command> p {
      new CommandLoseFocus
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Command> p {
      new CommandSetFocusRandom
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Command> p {
      new CommandSetFocusWithCoordinat(0,0)
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Command> p {
      new CommandDeleteFocusNode
    };
    assert(p);
    v.push_back(p);
  }
  return v;
}
