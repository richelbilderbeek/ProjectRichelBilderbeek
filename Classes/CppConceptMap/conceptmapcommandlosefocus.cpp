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
  assert(!m_widget);
  assert(!m_old_focus);
  assert(widget);
  assert(widget->m_focus);

  //Transfer focus to this command
  m_widget = widget;
  m_old_focus = widget->m_focus;

  m_widget->m_signal_lose_focus_node(m_widget->m_focus);
  m_widget->m_focus = nullptr;


  assert(m_widget);
  assert(m_old_focus);
  assert(!widget->m_focus);
}

void ribi::cmap::CommandLoseFocus::Undo() noexcept
{
  assert(m_widget);
  assert(m_old_focus);
  assert(!m_widget->m_focus);

  //Transfer focus to this command
  m_widget->m_focus = m_old_focus;
  m_old_focus = nullptr;
  m_widget->m_signal_concept_map_changed();
  m_widget = nullptr;


  assert(!m_widget);
  assert(!m_old_focus);
}
