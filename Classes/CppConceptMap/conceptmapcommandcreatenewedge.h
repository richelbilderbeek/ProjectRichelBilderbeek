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
#ifndef CONCEPTMAPCOMMANDCREATENEWEDGE_H
#define CONCEPTMAPCOMMANDCREATENEWEDGE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Start a new node
///-Can be used only when there is an existing concept map
class CommandCreateNewEdge final : public Command
{
  public:

  CommandCreateNewEdge(const boost::shared_ptr<ConceptMap> conceptmap);
  CommandCreateNewEdge(const CommandCreateNewEdge&) = delete;
  CommandCreateNewEdge& operator=(const CommandCreateNewEdge&) = delete;
  ~CommandCreateNewEdge() noexcept {}

  void redo() override;
  void undo() override;

  void SetVerbosity(const bool verbose) noexcept { m_verbose = verbose; }


  private:
  boost::shared_ptr<Edge> m_edge;
  std::vector<boost::shared_ptr<Node>> m_selected_nodes;
  std::vector<boost::shared_ptr<ribi::cmap::Node>> m_prev_selected; //Selected before Edge was added

  const boost::shared_ptr<ConceptMap> m_conceptmap;

  bool m_verbose;

};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDCREATENEWEDGE_H
