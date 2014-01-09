#include "conceptmapcommandcreatenewnode.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandCreateNewNode::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap().get();
}

void ribi::cmap::CommandCreateNewNode::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(!m_node);
  assert(widget);
  assert(widget->GetConceptMap().get());

  m_widget = widget;
  m_node = m_widget->CreateNewNode();

  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(m_node);
}

void ribi::cmap::CommandCreateNewNode::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  m_widget->DeleteNode(m_node);

  m_widget->m_signal_concept_map_changed();

  m_widget = nullptr;
  m_node = boost::shared_ptr<Node>();

}
