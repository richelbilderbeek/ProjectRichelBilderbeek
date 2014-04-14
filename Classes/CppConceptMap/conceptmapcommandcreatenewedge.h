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
struct CommandCreateNewEdge : public Command
{
  CommandCreateNewEdge() : m_edge{}, m_nodes{}, m_widget{} {}
  CommandCreateNewEdge(const CommandCreateNewEdge&) = delete;
  CommandCreateNewEdge& operator=(const CommandCreateNewEdge&) = delete;
  ~CommandCreateNewEdge() noexcept {}

  std::string ToStr() const noexcept final { return "create new edge"; }

  private:
  boost::shared_ptr<Edge> m_edge;
  std::vector<boost::shared_ptr<Node>> m_nodes;
  Widget * m_widget;

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept final;
  void DoCommandSpecific(Widget * const widget) noexcept final;
  void UndoSpecific() noexcept final;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDCREATENEWEDGE_H
