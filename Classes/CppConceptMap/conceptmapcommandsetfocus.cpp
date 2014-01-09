#include "conceptmapcommandsetfocus.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandSetFocus::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->FindNodeAt(m_x,m_y).get();
}

void ribi::cmap::CommandSetFocus::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);
  assert(!widget->m_focus);

  //Transfer focus to this Node
  m_widget = widget;
  m_widget->m_focus = widget->FindNodeAt(m_x,m_y).get();

  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(widget);
  assert(widget->m_focus);
}

void ribi::cmap::CommandSetFocus::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->m_focus);

  //Lose focus to this Node
  m_widget->m_focus = nullptr;
  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(!m_widget->m_focus);

}
