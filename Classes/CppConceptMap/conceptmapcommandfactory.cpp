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


ribi::cmap::Command* ribi::cmap::CommandFactory::CreateTestCommand(
  const int index,
  boost::shared_ptr<ConceptMap> conceptmap
) const noexcept
{
  try
  {
    switch (index)
    {
      case 0:
      {
        Command * const p {
          new CommandAddSelectedRandom(conceptmap)
        };
        assert(p);
        return p;
      }
      case 1:
      {
        Command * const p {
          new CommandCreateNewEdge(conceptmap)
        };
        assert(p);
        return p;
      }
      case 2:
      {
        Command * const p {
          new CommandCreateNewNode(conceptmap)
        };
        assert(p);
        return p;
      }
      default:
        assert(index >= GetSize());
    }
  }
  catch (std::logic_error& )
  {
    //Cannot do command, no problem, just return nullptr
  }
  return nullptr;
}


std::vector<ribi::cmap::Command*>
ribi::cmap::CommandFactory::CreateTestCommands(
  boost::shared_ptr<ConceptMap> conceptmap
) const noexcept
{
  std::vector<Command*> v;
  const int n{GetSize()};
  for (int i=0; i!=n; ++i)
  {

    Command * const p {
      CreateTestCommand(i,conceptmap)
    };
    if (p) v.push_back(p);
  }
  return v;
}
