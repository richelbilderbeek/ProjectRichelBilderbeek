#include "conceptmapcommanddeletenode.h"

#include <cassert>

#include "conceptmapwidget.h"

ribi::cmap::CommandDeleteNode::CommandDeleteNode(const boost::shared_ptr<Node> node)
  : m_node{node}, m_widget{}
{
  assert(m_node);
}

bool ribi::cmap::CommandDeleteNode::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap().get();
}

void ribi::cmap::CommandDeleteNode::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(m_node);
  assert(widget);
  assert(widget->GetConceptMap().get());

  m_widget = widget;
  m_widget->DeleteNode(m_node);

  assert(m_widget);
  assert(m_node);
}

void ribi::cmap::CommandDeleteNode::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  m_widget->AddNode(m_node);

  m_widget = nullptr;
}
