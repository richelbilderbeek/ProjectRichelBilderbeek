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
#ifdef USE_FOCUS_COMMANDS_201506712

#include "conceptmapcommandsetfocusrandom.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"

bool ribi::cmap::CommandSetFocusRandom::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  assert(widget->GetConceptMap() || !widget->GetConceptMap());
  std::vector<boost::shared_ptr<const Node>> nodes_to_exclude;
  if (widget->GetFocus()) { nodes_to_exclude.push_back(widget->GetFocus()); }
  //The concept map must contain at least one node
  return
        widget->GetConceptMap()
    && !widget->GetConceptMap()->GetNodes().empty()
    && !const_cast<Widget*>(widget)->GetRandomNodes(nodes_to_exclude).empty()
  ;
}

void ribi::cmap::CommandSetFocusRandom::DoCommandSpecific(Widget * const widget) noexcept
{
  assert( widget);
  assert(!m_widget);

  //Transfer focus to this Node
  m_widget = widget;
  m_old_focus = widget->GetFocus();

  std::vector<boost::shared_ptr<const Node>> nodes_to_exclude;
  if (widget->GetFocus()) { nodes_to_exclude.push_back(widget->GetFocus()); }

  const auto new_focus(widget->GetRandomNode(nodes_to_exclude));
  m_widget->SetFocus(new_focus);
  m_widget->m_signal_set_focus(new_focus);
  //m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(  widget);
}

void ribi::cmap::CommandSetFocusRandom::UndoSpecific() noexcept
{
  assert(m_widget);
  //Put back the old focus, or lose the focus
  if (m_old_focus)
  {
    m_widget->SetFocus(m_old_focus);
  }
  else
  {
    m_widget->LoseFocus();
  }
  m_widget->m_signal_set_focus(m_widget->m_focus);
  m_old_focus = boost::shared_ptr<Node>();
  m_widget = nullptr;
  assert(!m_widget);
}

#endif // USE_FOCUS_COMMANDS_201506712
