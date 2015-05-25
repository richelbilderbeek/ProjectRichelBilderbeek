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
#include "conceptmapcommandlosefocus.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandLoseFocus::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetFocus().get();
}

void ribi::cmap::CommandLoseFocus::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);
  assert(CanDoCommand(widget));
  assert(!m_widget);
  assert(!m_old_focus);

  //Transfer focus to this command
  m_widget = widget;

  assert(widget->m_focus);

  std::swap(m_old_focus,widget->m_focus);
  m_widget->m_signal_lose_focus(m_old_focus);

  assert( m_widget);
  assert( m_old_focus);
  assert(!widget->m_focus);
}

void ribi::cmap::CommandLoseFocus::UndoSpecific() noexcept
{
  assert( m_widget);
  assert( m_old_focus);
  assert(!m_widget->m_focus);

  //Transfer focus to this command
  std::swap(m_old_focus,m_widget->m_focus);
  m_widget->m_signal_concept_map_changed();

  assert(!m_old_focus);
  assert( m_widget->m_focus);

  m_widget = nullptr;

  assert(!m_widget);
  assert(!m_old_focus);
}
