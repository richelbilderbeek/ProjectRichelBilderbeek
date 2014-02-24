#include "conceptmapcommandlosefocus.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandLoseFocus::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return !widget->GetFocus().empty();
}

void ribi::cmap::CommandLoseFocus::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);
  assert(CanDoCommand(widget));

  //Transfer focus to this command
  m_widget = widget;
  m_old_focus = widget->m_focus.front();

  m_widget->m_signal_lose_focus_node(m_old_focus);
  m_widget->m_focus.pop_back();


  assert(m_widget);
  assert(m_old_focus);
}

void ribi::cmap::CommandLoseFocus::Undo() noexcept
{
  assert(m_widget);
  assert(m_old_focus);

  //Transfer focus to this command
  m_widget->m_focus.push_back(m_old_focus);
  m_old_focus = nullptr;
  m_widget->m_signal_concept_map_changed();
  m_widget = nullptr;


  assert(!m_widget);
  assert(!m_old_focus);
}
