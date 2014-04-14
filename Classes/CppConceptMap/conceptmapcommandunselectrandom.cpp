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
  std::random_shuffle(all_selected.begin(),all_selected.end());
  all_selected.resize(1);
  m_old_selected = all_selected[0];

  //Unselect it
  m_widget->Unselect(m_old_selected);
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
