#include "conceptmapcommandaddfocusrandom.h"

#include "conceptmapcommandsetfocusrandom.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"
#include "conceptmaphelper.h"
bool ribi::cmap::CommandAddFocusRandom::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  assert(widget->GetConceptMap() || !widget->GetConceptMap());
  return
        widget->GetConceptMap()
    && !widget->GetConceptMap()->GetNodes().empty()
    && !const_cast<Widget*>(widget)->GetRandomNodes(AddConst(widget->GetFocus())).empty()
  ;

}

void ribi::cmap::CommandAddFocusRandom::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);

  //Transfer focus to this Node
  m_widget = widget;
  m_old_focus = widget->GetFocus();
  assert(std::count(m_old_focus.begin(),m_old_focus.end(),nullptr) == 0);
  const auto focus_to_add(widget->GetRandomNodes(AddConst(m_old_focus)));
  m_widget->AddFocus(focus_to_add);
  //m_widget->m_signal_set_focus_node();
  //m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(widget);
}

void ribi::cmap::CommandAddFocusRandom::Undo() noexcept
{
  assert(m_widget);

  //Lose focus to this Node
  assert(std::count(m_old_focus.begin(),m_old_focus.end(),nullptr) == 0);
  m_widget->AddFocus(m_old_focus);

  m_widget->m_signal_set_focus_nodes(m_widget->m_focus);

  assert(m_widget);

}
