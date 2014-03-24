#ifdef SUPPORT_NONSENSE

#include "conceptmapcommandaddfocusrandom.h"

#include "conceptmapcommandsetfocusrandom.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"
#include "conceptmaphelper.h"
#include "trace.h"
bool ribi::cmap::CommandAddFocusRandom::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  assert(widget->GetConceptMap() || !widget->GetConceptMap());
  const bool verbose = false;
  if (!widget->GetConceptMap())
  {
    if (verbose) TRACE("AddFocus needs a concept map");
    return false;
  }
  if (widget->GetConceptMap()->GetNodes().empty())
  {
    if (verbose) TRACE("AddFocus needs nodes to focus on");
    return false;
  }

  if (const_cast<Widget*>(widget)->GetRandomNodes(AddConst(widget->GetFocus())).empty())
  {
    if (verbose)
    {
      TRACE("AddFocus needs non-focused nodes to focus on");
      TRACE(widget->GetFocus().size());
      TRACE(widget->GetConceptMap()->GetNodes().size());
    }
    return false;
  }
  return true;
}

void ribi::cmap::CommandAddFocusRandom::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);

  //Transfer focus to this Node
  m_widget = widget;
  m_old_focus = widget->GetFocus();
  assert(std::count(m_old_focus.begin(),m_old_focus.end(),nullptr) == 0);
  const auto focus_to_add(widget->GetRandomNodes(AddConst(m_old_focus)));
  m_widget->AddSelected(focus_to_add);
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
  m_widget->SetFocus(m_old_focus);

  m_widget->m_signal_set_selected_nodes(m_widget->m_focus);

  assert(m_widget);

}

#endif //#ifdef SUPPORT_NONSENSE
