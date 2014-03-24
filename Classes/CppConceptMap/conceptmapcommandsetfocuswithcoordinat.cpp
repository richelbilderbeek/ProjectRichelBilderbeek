#include "conceptmapcommandsetfocuswithcoordinat.h"

#include <cassert>

#include "conceptmapwidget.h"
#include "conceptmapnode.h"

bool ribi::cmap::CommandSetFocusWithCoordinat::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return
    widget->FindNodeAt(m_x,m_y).get();
}

void ribi::cmap::CommandSetFocusWithCoordinat::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(CanDoCommandSpecific(widget));
  assert(widget);

  m_old_focus = widget->GetFocus();
  m_widget = widget;

  const boost::shared_ptr<Node> node {
    widget->FindNodeAt(m_x,m_y)
  };


  widget->m_focus.clear();
  widget->m_focus.push_back(node);

  widget->m_signal_set_selected_nodes(widget->GetFocus());

  assert(m_widget);
  assert(widget);
}

void ribi::cmap::CommandSetFocusWithCoordinat::Undo() noexcept
{
  assert(m_widget);
  assert(!m_widget->m_focus.empty());

  //Lose focus to this Node
  m_widget->SetFocus(m_old_focus);

  m_old_focus.clear();
  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
}
