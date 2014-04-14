//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#include "conceptmapcommandfactory.h"

#include <cassert>

#include "conceptmapcommandaddselectedrandom.h"
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
      new CommandAddSelectedRandom
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
