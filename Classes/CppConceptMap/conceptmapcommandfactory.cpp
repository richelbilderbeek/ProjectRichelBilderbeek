//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
#include "conceptmapcommandcreatenewedge.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandsetselectedwithcoordinat.h"

std::vector<boost::shared_ptr<ribi::cmap::Command> >
ribi::cmap::CommandFactory::CreateTestCommands(
  boost::shared_ptr<ConceptMap> concept_map

) noexcept
{
  std::vector<boost::shared_ptr<Command> > v;

  {
    const boost::shared_ptr<Command> p {
      new CommandAddSelectedRandom(concept_map)
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Command> p {
      new CommandCreateNewEdge(concept_map)
    };
    assert(p);
    v.push_back(p);
  }
  {
    const boost::shared_ptr<Command> p {
      new CommandCreateNewNode(concept_map)
    };
    assert(p);
    v.push_back(p);
  }
  return v;
}
