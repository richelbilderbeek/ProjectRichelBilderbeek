#include "conceptmapcommandunselectrandom.h"

#include "conceptmapcommandsetfocusrandom.h"

#include <cassert>

#include "conceptmap.h"
#include "conceptmapwidget.h"
#include "conceptmaphelper.h"
#include "trace.h"

bool ribi::cmap::CommandUnselectRandom::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  assert(widget->GetConceptMap() || !widget->GetConceptMap());
  const bool verbose{false};
  if (!widget->GetConceptMap())
  {
    if (verbose) TRACE("Unselect needs a concept map");
    return false;
  }
  if (widget->GetSelectedEdges().empty() && widget->GetSelectedNodes().empty())
  {
    if (verbose) TRACE("Unselect needs nodes to unselect on");
    return false;
  }
  return true;
}

void ribi::cmap::CommandUnselectRandom::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);

  m_widget = widget;
  m_old_selected = const_cast<const Widget*>(widget)->GetSelected();

  //Get a random selected edge or node
  auto all_selected = const_cast<const Widget*>(widget)->GetSelected();
  const int n_edges{static_cast<int>(all_selected.first.size())};
  const int n_nodes{static_cast<int>(all_selected.second.size())};
  assert(n_edges + n_nodes > 0);
  const int i{std::rand() % (n_edges + n_nodes)};
  if (i < n_edges)
  {
    //Unselect edge
    std::swap(all_selected.first[i],all_selected.first.back());
    all_selected.first.pop_back();
  }
  else
  {
    //Unselect node
    std::swap(all_selected.second[i - n_edges],all_selected.second.back());
    all_selected.second.pop_back();
  }
  m_widget->SetSelected(all_selected);

  //m_widget->m_signal_set_focus_node();
  //m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(widget);
}

void ribi::cmap::CommandUnselectRandom::UndoSpecific() noexcept
{
  assert(m_widget);

  //Re-select the previously selected Node
  m_widget->SetSelected(m_old_selected);

}
