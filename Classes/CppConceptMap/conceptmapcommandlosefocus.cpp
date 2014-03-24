#include "conceptmapcommandlosefocus.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandLoseFocus::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return !widget->GetFocus();
}

void ribi::cmap::CommandLoseFocus::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);
  assert(CanDoCommand(widget));

  //Transfer focus to this command
  m_widget = widget;
  m_old_focus = widget->m_focus;

  m_widget->m_signal_lose_focus_nodes(m_old_focus);
  m_widget->m_focus.clear();

  assert(m_widget);
}

void ribi::cmap::CommandLoseFocus::Undo() noexcept
{
  assert(m_widget);

  //Transfer focus to this command
  m_widget->m_focus = m_old_focus;
  m_old_focus.clear();
  m_widget->m_signal_concept_map_changed();
  m_widget = nullptr;


  assert(!m_widget);
}
