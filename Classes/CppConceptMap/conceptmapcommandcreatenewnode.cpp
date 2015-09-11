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
#include "conceptmapcommandcreatenewnode.h"

#include <cassert>


#include "conceptmap.h"
#include "conceptmapnode.h"

ribi::cmap::CommandCreateNewNode::CommandCreateNewNode(
  const boost::shared_ptr<ConceptMap> conceptmap
)
  : m_node{},
    m_conceptmap{conceptmap}
{
  this->setText("create new node");
}

void ribi::cmap::CommandCreateNewNode::redo()
{
  if (!m_node)
  {
    m_node = m_conceptmap->CreateNewNode(); //CreateNewNode adds it to the selected nodes
  }
  else
  {
    m_conceptmap->AddNode(m_node);
  }
  assert(m_node);
}

void ribi::cmap::CommandCreateNewNode::undo()
{
  assert(m_conceptmap);
  m_conceptmap->DeleteNode(m_node);
}
