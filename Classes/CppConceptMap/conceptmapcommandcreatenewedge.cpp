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

ribi::cmap::CommandCreateNewEdge::CommandCreateNewEdge(
  const boost::shared_ptr<ConceptMap> conceptmap
)
 : m_edge{},
   m_selected_nodes{conceptmap->GetSelectedNodes()},
   m_prev_selected{},
   m_conceptmap{conceptmap},
   m_verbose{false}
{
  this->setText("create new edge");

  if (m_selected_nodes.size() != 2)
  {
    std::stringstream msg;
    msg << "Number of selected nodes (" << m_conceptmap->GetSelectedNodes().size() << " is not equal to two";
    throw std::logic_error(msg.str());
  }
  if (!m_conceptmap->HasNode(m_selected_nodes[0]))
  {
    throw std::logic_error("From node is member of an edge");
  }
  if (!m_conceptmap->HasNode(m_selected_nodes[1]))
  {
    throw std::logic_error("'To' node is member of an edge");
  }
}

void ribi::cmap::CommandCreateNewEdge::redo()
{
  m_conceptmap->SetSelected(m_selected_nodes);
  if (!m_edge)
  {
    m_edge = m_conceptmap->CreateNewEdge();
  }
  else
  {
    m_conceptmap->AddEdge(m_edge);
  }
}

void ribi::cmap::CommandCreateNewEdge::undo()
{
  m_conceptmap->DeleteEdge(m_edge);
  m_conceptmap->SetSelected(m_prev_selected);
}
