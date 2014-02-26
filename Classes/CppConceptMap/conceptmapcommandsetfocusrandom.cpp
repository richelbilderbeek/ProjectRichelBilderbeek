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

  //Transfer focus to this Node
  m_widget = widget;
  m_old_focus = widget->GetFocus();
  assert(std::count(m_old_focus.begin(),m_old_focus.end(),nullptr) == 0);
  m_widget->SetFocus( { widget->GetRandomNode() } );
  //m_widget->m_signal_set_focus_node();
  //m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(widget);
}

void ribi::cmap::CommandSetFocusRandom::Undo() noexcept
{
  assert(m_widget);

  //Lose focus to this Node
  assert(std::count(m_old_focus.begin(),m_old_focus.end(),nullptr) == 0);
  m_widget->SetFocus(m_old_focus);

  m_widget->m_signal_set_focus_nodes(m_widget->m_focus);

  assert(m_widget);

}
