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
#include "conceptmapcommandcreatenewedge.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"
#include "conceptmapedgefactory.h"

bool ribi::cmap::CommandCreateNewEdge::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap() && widget->GetSelectedNodes().size() == 2;
}

void ribi::cmap::CommandCreateNewEdge::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(widget);
  assert(widget->GetConceptMap().get());
  assert(CanDoCommand(widget));

  m_widget = widget;
  m_nodes.push_back(m_widget->GetSelectedNodes()[0]);
  m_nodes.push_back(m_widget->GetSelectedNodes()[1]);

  assert(m_nodes.size() == 2);
  assert(m_nodes[0]);
  assert(m_nodes[1]);
  assert(m_nodes[0] != m_nodes[1]
    && "An edge must be created from two different nodes");
  assert(m_widget->GetConceptMap()->HasNode(m_nodes[0])
    && "An edge must be created from two existing nodes");
  assert(m_widget->GetConceptMap()->HasNode(m_nodes[1])
    && "An edge must be created from two existing nodes");

  m_prev_selected = m_widget->GetSelectedNodes();

  m_edge = m_widget->CreateNewEdge();

  assert(m_widget);
  assert(m_edge);
}

void ribi::cmap::CommandCreateNewEdge::UndoSpecific() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());


  m_widget->DeleteEdge(m_edge);

  m_widget->SetSelected(m_prev_selected);


  m_widget = nullptr;
  m_nodes.clear();
  m_edge = boost::shared_ptr<Edge>();

}
