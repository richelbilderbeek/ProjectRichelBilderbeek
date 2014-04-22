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
  const bool verbose = false;
  if (!widget->GetConceptMap())
  {
    if (verbose) TRACE("Unselect needs a concept map");
    return false;
  }
  if (widget->GetSelected().empty())
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

  //Get a random selected node
  auto all_selected = widget->GetSelected();
  assert(std::count(all_selected.begin(),all_selected.end(),nullptr) == 0);
  const int i = std::rand() % static_cast<int>(all_selected.size());
  m_old_selected = all_selected[i];

  //Unselect it
  std::swap(all_selected[i],all_selected[ all_selected.size() - 1]);
  all_selected.pop_back();
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
  m_widget->AddSelected( { m_old_selected} );

  m_widget->m_signal_set_selected(m_widget->m_selected);

  assert(m_widget);

}
