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
  CommandFactory() {}

  Command* CreateTestCommand(
    const int index,
    boost::shared_ptr<ConceptMap> conceptmap
  ) const noexcept;

  ///The number of Commands
  int GetSize() const noexcept { return 3; }

  private:

  ///Create all Commands that can be done on the ConceptMap
  ///These are raw pointers! This is because QUndoStack takes up ownership of
  ///the pointer.
  std::vector<Command*> CreateTestCommands(
    boost::shared_ptr<ConceptMap> conceptmap
  ) const noexcept;
};

} //~namespace cmap
} //~namespace ribi


#endif // CONCEPTMAPCOMMANDFACTORY_H
