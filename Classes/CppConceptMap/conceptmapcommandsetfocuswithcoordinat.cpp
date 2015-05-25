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
#include "conceptmapcommandsetfocuswithcoordinat.h"

#include <cassert>

#include "conceptmapwidget.h"
#include "conceptmapnode.h"

bool ribi::cmap::CommandSetFocusWithCoordinat::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return
    widget->FindNodeAt(m_x,m_y).get();
}

void ribi::cmap::CommandSetFocusWithCoordinat::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(CanDoCommandSpecific(widget));
  assert(widget);

  m_old_focus = widget->GetFocus();
  m_widget = widget;

  const boost::shared_ptr<Node> node {
    widget->FindNodeAt(m_x,m_y)
  };

  widget->m_focus = node;
  widget->m_signal_set_focus(node);

  assert(m_widget);
  assert(widget);
}

void ribi::cmap::CommandSetFocusWithCoordinat::UndoSpecific() noexcept
{
  assert(m_widget);
  assert(m_widget->m_focus);

  //Give back previous focus, or lose it
  if (m_old_focus)
  {
    m_widget->SetFocus(m_old_focus);
  }
  else
  {
    m_widget->LoseFocus();
  }

  m_old_focus = boost::shared_ptr<Node>();
  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
}
