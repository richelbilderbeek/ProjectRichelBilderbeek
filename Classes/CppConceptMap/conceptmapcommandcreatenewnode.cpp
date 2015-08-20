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

bool ribi::cmap::CommandCreateNewNode::CanDoCommandSpecific(const ConceptMap * const /* conceptmap */) const noexcept
{
  return true;
}

void ribi::cmap::CommandCreateNewNode::DoCommandSpecific(ConceptMap * const widget) noexcept
{
  assert(!m_conceptmap && "Cannot do a command twice");
  assert(!m_node);
  assert(widget);

  m_conceptmap = widget;
  m_node = m_conceptmap->CreateNewNode(); //CreateNewNode adds it to the selected nodes

  assert(m_conceptmap);
  assert(m_node);
}

void ribi::cmap::CommandCreateNewNode::UndoSpecific() noexcept
{
  assert(m_conceptmap);

  //unselect it
  //m_widget->m_signal_delete_node(m_node); //Done by DeleteNodeS

  m_conceptmap->DeleteNode(m_node);

  m_conceptmap = nullptr;
  m_node = boost::shared_ptr<Node>();

}
