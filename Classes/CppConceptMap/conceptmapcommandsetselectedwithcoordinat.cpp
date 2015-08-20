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
#include "conceptmapcommandsetselectedwithcoordinat.h"

#include <cassert>


#include "conceptmap.h"
#include "conceptmapnode.h"

bool ribi::cmap::CommandSetSelectedWithCoordinat::CanDoCommandSpecific(const ConceptMap * const widget) const noexcept
{
  assert(widget);
  return
    widget->FindNodeAt(m_x,m_y).get();
}

void ribi::cmap::CommandSetSelectedWithCoordinat::DoCommandSpecific(ConceptMap * const widget) noexcept
{
  assert(CanDoCommandSpecific(widget));
  assert(widget);

  m_old_focus = const_cast<const ConceptMap*>(widget)->GetSelected();
  m_widget = widget;

  const boost::shared_ptr<Node> node {
    widget->FindNodeAt(m_x,m_y)
  };

  widget->m_focus = node;
  //widget->m_signal_set_focus(node);

  assert(m_widget);
  assert(widget);
}

void ribi::cmap::CommandSetSelectedWithCoordinat::UndoSpecific() noexcept
{
  assert(m_widget);
  assert(m_widget->m_focus);

  //Give back previous selection
  m_widget->SetSelected(m_old_focus);

  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
}
