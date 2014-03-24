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

  assert(!m_old_focus);
  assert(widget->m_focus);

  std::swap(m_old_focus,widget->m_focus);
  m_widget->m_signal_lose_focus(m_old_focus);

  assert(m_widget);
  assert( m_old_focus);
  assert(!widget->m_focus);
}

void ribi::cmap::CommandLoseFocus::Undo() noexcept
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
