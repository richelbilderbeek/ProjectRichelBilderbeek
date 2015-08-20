#include "conceptmapcommandaddselectedrandom.h"

#include "conceptmapcommandsetfocusrandom.h"

#include <cassert>

#include "conceptmap.h"

#include "conceptmaphelper.h"
#include "trace.h"

bool ribi::cmap::CommandAddSelectedRandom::CanDoCommandSpecific(const ConceptMap * const concept_map) const noexcept
{
  assert(concept_map);
  const bool verbose{false};
  if (concept_map->GetNodes().empty())
  {
    if (verbose) TRACE("AddSelected needs nodes to focus on");
    return false;
  }
  if (const_cast<ConceptMap*>(concept_map)->GetRandomNodes(AddConst(concept_map->GetSelectedNodes())).empty())
  {
    if (verbose)
    {
      TRACE("AddSelected needs non-focused nodes to focus on");
      TRACE(concept_map->GetSelectedNodes().size());
    }
    return false;
  }
  return true;
}

void ribi::cmap::CommandAddSelectedRandom::DoCommandSpecific(ConceptMap * const widget) noexcept
{
  assert(widget);

  //Transfer focus to this Node
  m_widget = widget;
  m_old_selected = const_cast<const ConceptMap*>(widget)->GetSelected();
  const auto selected_edges(widget->GetRandomEdges(AddConst(m_old_selected.first)));
  const auto selected_nodes(widget->GetRandomNodes(AddConst(m_old_selected.second)));
  m_widget->AddSelected(selected_edges,selected_nodes);
  //m_widget->m_signal_set_focus_node();
  //m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(widget);
}

void ribi::cmap::CommandAddSelectedRandom::UndoSpecific() noexcept
{
  assert(m_widget);

  //Lose focus to this Node
  m_widget->SetSelected(m_old_selected);
}
