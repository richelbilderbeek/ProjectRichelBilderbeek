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
#include "conceptmapcommanddeletenode.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapedge.h"
#include "conceptmapnode.h"
#include "conceptmapconcept.h"

ribi::cmap::CommandDeleteNode::CommandDeleteNode(
  const boost::shared_ptr<ConceptMap> conceptmap,
  const boost::shared_ptr<Node> node
) :
    m_conceptmap{conceptmap},
    m_deleted_edges{conceptmap && node ? conceptmap->GetEdgesConnectedTo(node) : Edges()},
    m_node{node},
    m_old_selected{conceptmap->GetSelected()},
    m_verbose{false}
{
  if (!m_conceptmap)
  {
    throw std::logic_error("Cannot delete Node from an empty concept map");
  }
  if (!m_node)
  {
    throw std::logic_error("Cannot delete empty Node");
  }
  if (!m_conceptmap->HasNode(m_node))
  {
    throw std::logic_error("Cannot delete Node that is not in ConceptMap");
  }
  setText("delete node");
}

void ribi::cmap::CommandDeleteNode::redo()
{
  if (m_verbose)
  {
    std::clog
      << "Deleting " << m_deleted_edges.size() << " edges" << std::endl
    ;
  }

  for (const auto edge: m_deleted_edges)
  {
    if (m_verbose)
    {
      std::clog
        << "Deleting edge with text '"
        << edge->GetNode()->GetConcept()->GetName() << "'" << std::endl
      ;
    }
    m_conceptmap->DeleteEdge(edge);
  }
  if (m_verbose)
  {
    std::clog
      << "Deleting node with text '"
      << m_node->GetConcept()->GetName() << "'" << std::endl
    ;
  }
  m_conceptmap->DeleteNode(m_node);
}

void ribi::cmap::CommandDeleteNode::undo()
{
  if (m_verbose)
  {
    std::clog
      << "Adding " << m_deleted_edges.size() << " edges" << std::endl
    ;
  }

  if (m_verbose)
  {
    std::clog
      << "Adding node with text '"
      << m_node->GetConcept()->GetName() << "'" << std::endl
    ;
  }
  m_conceptmap->AddNode(m_node);

  for (const auto edge: m_deleted_edges)
  {
    if (m_verbose)
    {
      std::clog
        << "Adding edge with text '"
        << edge->GetNode()->GetConcept()->GetName() << "'" << std::endl
      ;
    }
    m_conceptmap->AddEdge(edge);
  }
  m_conceptmap->SetSelected(m_old_selected);
}
