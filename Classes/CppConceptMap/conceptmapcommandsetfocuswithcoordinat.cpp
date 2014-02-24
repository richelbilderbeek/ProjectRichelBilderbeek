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

  //Set focus to this Node
  m_widget = widget;
  const boost::shared_ptr<Node> node {
    widget->FindNodeAt(m_x,m_y)
  };

  m_widget->m_focus.clear();
  m_widget->m_focus.push_back(node);

  m_widget->m_signal_set_focus_nodes({ node);

  assert(m_widget);
  assert(widget);
  assert(widget->m_focus);
}

void ribi::cmap::CommandSetFocusWithCoordinat::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->m_focus);

  //Lose focus to this Node
  m_widget->m_focus = nullptr;
  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(!m_widget->m_focus || m_widget->m_focus); //Widget might have had focus
}
