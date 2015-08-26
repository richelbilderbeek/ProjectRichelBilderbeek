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
#include <sstream>

#include "conceptmap.h"

#include "conceptmapedgefactory.h"
#include "trace.h"

bool ribi::cmap::CommandCreateNewEdge::CanDoCommandSpecific(const ConceptMap * const conceptmap) const noexcept
{
  assert(conceptmap);
  if (!conceptmap)
  {
    if (m_verbose) { TRACE("No concept map"); }
    return false;
  }
  if (conceptmap->GetSelectedNodes().size() != 2)
  {
    if (m_verbose)
    {
      std::stringstream msg;
      msg << "Number of selected nodes (" << conceptmap->GetSelectedNodes().size() << " is not equal to two";
      TRACE(msg.str());
    }
    return false;
  }
  return true;
}

void ribi::cmap::CommandCreateNewEdge::DoCommandSpecific(ConceptMap * const concept_map) noexcept
{
  assert(!m_concept_map);
  assert(concept_map);
  assert(CanDoCommand(concept_map));

  m_concept_map = concept_map;
  assert(m_concept_map->GetSelectedNodes().size() == 2);
  m_nodes.push_back(m_concept_map->GetSelectedNodes()[0]);
  m_nodes.push_back(m_concept_map->GetSelectedNodes()[1]);

  assert(m_nodes.size() == 2);
  assert(m_nodes[0]);
  assert(m_nodes[1]);
  assert(m_nodes[0] != m_nodes[1]
    && "An edge must be created from two different nodes");
  assert(m_concept_map->HasNode(m_nodes[0])
    && "An edge must be created from two existing nodes");
  assert(m_concept_map->HasNode(m_nodes[1])
    && "An edge must be created from two existing nodes");

  m_prev_selected = m_concept_map->GetSelectedNodes();

  m_edge = m_concept_map->CreateNewEdge();

  assert(m_concept_map);
  assert(m_edge);
}

void ribi::cmap::CommandCreateNewEdge::UndoSpecific() noexcept
{
  assert(m_concept_map);

  m_concept_map->DeleteEdge(m_edge);

  m_concept_map->SetSelected(m_prev_selected);


  m_concept_map = nullptr;
  m_nodes.clear();
  m_edge = boost::shared_ptr<Edge>();

}
