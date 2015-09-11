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
#ifndef CONCEPTMAPCOMMANDDELETENODE_H
#define CONCEPTMAPCOMMANDDELETENODE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Delete an existing node
struct CommandDeleteNode final : public Command
{
  CommandDeleteNode(
    const boost::shared_ptr<ConceptMap> conceptmap,
    const boost::shared_ptr<Node> node
  );
  CommandDeleteNode(const CommandDeleteNode&) = delete;
  CommandDeleteNode& operator=(const CommandDeleteNode&) = delete;
  ~CommandDeleteNode() noexcept {}

  void undo() override;
  void redo() override;

  private:
  boost::shared_ptr<Node> m_node;
  const boost::shared_ptr<ConceptMap> m_conceptmap;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDDELETENODE_H
