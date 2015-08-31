#include "conceptmapcommandunselectrandom.h"

#include "conceptmapcommandsetfocusrandom.h"

#include <cassert>

#include "conceptmap.h"

#include "conceptmaphelper.h"
#include "trace.h"

ribi::cmap::CommandUnselectRandom::CommandUnselectRandom(
  const boost::shared_ptr<ConceptMap> concept_map
) : m_old_selected{},
    m_concept_map{concept_map}
{
  this->setText("unselect random");
}

bool ribi::cmap::CommandUnselectRandom::CanDoCommandSpecific(const ConceptMap * const concept_map) const noexcept
{
  assert(concept_map);
  const bool verbose{false};
  if (concept_map->GetSelectedEdges().empty() && concept_map->GetSelectedNodes().empty())
  {
    if (verbose) TRACE("Unselect needs nodes to unselect on");
    return false;
  }
  return true;
}

void ribi::cmap::CommandUnselectRandom::redo(ConceptMap * const widget) noexcept
{
  assert(widget);

  m_concept_map = widget;
  m_old_selected = const_cast<const ConceptMap*>(widget)->GetSelected();

  //Get a random selected edge or node
  auto all_selected = const_cast<const ConceptMap*>(widget)->GetSelected();
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
  m_concept_map->SetSelected(all_selected);

  //m_widget->m_signal_set_focus_node();
  //m_widget->m_signal_concept_map_changed();

  assert(m_concept_map);
  assert(widget);
}

void ribi::cmap::CommandUnselectRandom::undo() noexcept
{
  assert(m_concept_map);

  //Re-select the previously selected Node
  m_concept_map->SetSelected(m_old_selected);

}
