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

#include "conceptmapwidget.h"

ribi::cmap::CommandDeleteNode::CommandDeleteNode(const boost::shared_ptr<Node> node)
  : m_node{node}, m_widget{}
{
  assert(m_node);
}

bool ribi::cmap::CommandDeleteNode::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap().get();
}

void ribi::cmap::CommandDeleteNode::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(m_node);
  assert(widget);
  assert(widget->GetConceptMap().get());

  m_widget = widget;
  m_widget->DeleteNode(m_node);

  assert(m_widget);
  assert(m_node);
}

void ribi::cmap::CommandDeleteNode::UndoSpecific() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  m_widget->AddNode(m_node);

  m_widget = nullptr;
}
