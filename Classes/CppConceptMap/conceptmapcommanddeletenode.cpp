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


ribi::cmap::CommandDeleteNode::CommandDeleteNode(const boost::shared_ptr<Node> node)
  : m_node{node}, m_concept_map{}
{
  assert(m_node);
}

bool ribi::cmap::CommandDeleteNode::CanDoCommandSpecific(const ConceptMap * const conceptmap) const noexcept
{

  assert(conceptmap);
  return conceptmap->HasNode(m_node);
}

void ribi::cmap::CommandDeleteNode::DoCommandSpecific(ConceptMap * const concept_map) noexcept
{
  assert(!m_concept_map);
  assert(m_node);
  assert(concept_map);

  m_concept_map = concept_map;
  m_concept_map->DeleteNode(m_node);

  assert(m_concept_map);
  assert(m_node);
}

void ribi::cmap::CommandDeleteNode::UndoSpecific() noexcept
{
  assert(m_concept_map);

  m_concept_map->AddNode(m_node);

  m_concept_map = nullptr;
}
