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


ribi::cmap::CommandDeleteNode::CommandDeleteNode(
  const boost::shared_ptr<ConceptMap> conceptmap,
  const boost::shared_ptr<Node> node
) : m_node{node}, m_conceptmap{conceptmap}
{
  assert(m_node);
  assert(m_conceptmap);

  setText("delete node");

  if (!m_conceptmap->HasNode(m_node))
  {
    throw std::logic_error("Cannot delete Node that is not in ConceptMap");
  }
}

void ribi::cmap::CommandDeleteNode::redo()
{
  m_conceptmap->DeleteNode(m_node);
}

void ribi::cmap::CommandDeleteNode::undo()
{
  m_conceptmap->AddNode(m_node);
}
