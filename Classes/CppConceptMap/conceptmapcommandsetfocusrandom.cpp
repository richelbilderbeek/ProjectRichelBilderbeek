#include "conceptmapcommandsetfocusrandom.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"

bool ribi::cmap::CommandSetFocusRandom::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  assert(widget->GetConceptMap() || !widget->GetConceptMap());
  //The concept map must contain at least one node
  return
        widget->GetConceptMap()
    && !widget->GetConceptMap()->GetNodes().empty()
  ;
}

void ribi::cmap::CommandSetFocusRandom::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);
  assert(!widget->m_focus || widget->m_focus);

  //Transfer focus to this Node
  m_widget = widget;
  m_widget->m_focus = widget->GetRandomNode().get();
  assert(m_widget->m_focus);

  m_widget->m_signal_set_focus_node(m_widget->m_focus);
  //m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(widget);
  assert(widget->m_focus);
}

void ribi::cmap::CommandSetFocusRandom::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->m_focus);

  //Lose focus to this Node
  m_widget->m_focus = nullptr;

  m_widget->m_signal_set_focus_node(m_widget->m_focus);
  //m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(!m_widget->m_focus || m_widget->m_focus); //Might have restored previous focus

}
