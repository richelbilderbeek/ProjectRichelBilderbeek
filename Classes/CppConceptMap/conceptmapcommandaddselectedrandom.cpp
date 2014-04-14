#include "conceptmapcommandaddselectedrandom.h"

#include "conceptmapcommandsetfocusrandom.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"
#include "conceptmaphelper.h"
#include "trace.h"

bool ribi::cmap::CommandAddSelectedRandom::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  assert(widget->GetConceptMap() || !widget->GetConceptMap());
  const bool verbose = false;
  if (!widget->GetConceptMap())
  {
    if (verbose) TRACE("AddSelected needs a concept map");
    return false;
  }
  if (widget->GetConceptMap()->GetNodes().empty())
  {
    if (verbose) TRACE("AddSelected needs nodes to focus on");
    return false;
  }

  if (const_cast<Widget*>(widget)->GetRandomNodes(AddConst(widget->GetSelected())).empty())
  {
    if (verbose)
    {
      TRACE("AddSelected needs non-focused nodes to focus on");
      TRACE(widget->GetSelected().size());
      TRACE(widget->GetConceptMap()->GetNodes().size());
    }
    return false;
  }
  return true;
}

void ribi::cmap::CommandAddSelectedRandom::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);

  //Transfer focus to this Node
  m_widget = widget;
  m_old_selected = widget->GetSelected();
  assert(std::count(m_old_selected.begin(),m_old_selected.end(),nullptr) == 0);
  const auto selected_to_add(widget->GetRandomNodes(AddConst(m_old_selected)));
  m_widget->AddSelected(selected_to_add);
  //m_widget->m_signal_set_focus_node();
  //m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(widget);
}

void ribi::cmap::CommandAddSelectedRandom::UndoSpecific() noexcept
{
  assert(m_widget);

  //Lose focus to this Node
  assert(std::count(m_old_selected.begin(),m_old_selected.end(),nullptr) == 0);
  m_widget->SetSelected(m_old_selected);

  m_widget->m_signal_set_selected(m_widget->m_selected);

  assert(m_widget);

}
